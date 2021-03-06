// Richard Shemaka - 2020
// https://github.com/rshemaka/cppmath

#pragma once
#include "Random.h"
#include "Vector2.h"
#include <algorithm>
#include <vector>

// blue noise via Poisson disk sampling.
// supported: 1d, 2d positions
// someday: 3d, rotations?
//
// Source:
// Fast Poisson Disk Sampling in Arbitrary Dimensions
// https://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf

// generates blue noise given a bounding range and minimum spacing
// amount of noise output is indeterminate
// returns: number of points generated
int generatePoissonDiskNoise1D(std::vector<float>& outNoise, float rangeMin, float rangeMax, float minDist)
{
    outNoise.empty();

    if (rangeMin > rangeMax)
        return 0;

    // not enough room to scatter two points? just toss a random sample in and return
    if ((rangeMax - rangeMin) < minDist)
    {
        outNoise.push_back(randRange(rangeMin, rangeMax));
        return 1;
    }

    // 1d blue noise can simply march from one end to the other
    float latestSample = randRange(rangeMin, rangeMin + minDist);
    outNoise.push_back(latestSample);
    while (rangeMax - latestSample > minDist)
    {
        float sampleMin = latestSample + minDist;
        float sampleMax = fmin(sampleMin + minDist, rangeMax);
        latestSample = randRange(sampleMin, sampleMax);
        outNoise.push_back(latestSample);
    }

    return static_cast<int>(outNoise.size());
}

// generates blue noise given a bounding range and minimum spacing
// amount of noise output is indeterminate
// returns: number of points generated
int generatePoissonDiskNoise2D(std::vector<vec2>& outNoise, vec2 rangeMin, vec2 rangeMax, float minDist, int sampleLimit = 30)
{
    outNoise.empty();

    if (rangeMin.x > rangeMax.x || rangeMin.y > rangeMax.y)
        return 0;

    const vec2 rangeSize = rangeMax - rangeMin;
    const float cellSize = minDist / sqrtf(2);
    const int xCells = int(ceilf(rangeSize.x / cellSize));
    const int yCells = int(ceilf(rangeSize.y / cellSize));
    outNoise.reserve(xCells * yCells);

    // 2d spatial grid
    std::vector<std::vector<uint32_t>> grid(xCells, std::vector<uint32_t>(yCells, UINT32_MAX));
    typedef t_vec2<uint16_t> index2;
    // function to compute grid x,y given a vec2
    auto calculateGridCell = [cellSize](const vec2& vec) {
        index2 outIndex;
        outIndex.x = uint16_t(floorf(vec.x / cellSize));
        outIndex.y = uint16_t(floorf(vec.y / cellSize));
        return outIndex;
    };
    // function to determine if an index is valid
    auto isValidIndex = [xCells, yCells](index2 index) { return index.x >= 0 && index.y >= 0 && index.x < xCells && index.y < yCells; };

    // add the first sample at random
    {
        const vec2 firstSample = vec2(randRange(rangeMin.x, rangeMax.x), randRange(rangeMin.y, rangeMin.y));
        outNoise.push_back(firstSample);
        const index2 firstIndex = calculateGridCell(firstSample);
        grid[firstIndex.x][firstIndex.y] = 0;
    }

    // search boundary, stores an index into the outNoise array
    std::vector<uint32_t> activeSamples;
    activeSamples.push_back(0);

    const float minDistSqr = minDist * minDist;
    do
    {
        // "while the active list is not empty, choose a random index from it (i)"
        const uint32_t currentNoiseIndex = randIndex(activeSamples.size());
        const vec2& currentSample = outNoise[currentNoiseIndex];

        bool neighborPlaced = false;
        // "generate up to k points ..."
        for (int sampleAttempt = 0, n = sampleLimit; sampleAttempt != n; ++sampleAttempt)
        {
            // "... uniformly from the spherical annulus between radius r and 2r around x[i]"
            const vec2 randomThrow = randomPointOnUnitCircle() * randRange(minDist, 2.f * minDist);
            const vec2 candidate = currentSample + randomThrow;
            const index2 candidateIndex = calculateGridCell(candidate);
            if (!isValidIndex(candidateIndex))
                continue;

            // "check if it is within distance r of existing samples (using the background grid to only test nearby samples)"
            bool nearbySampleFound = false;
            for (uint16_t testX = -1; testX != 2; ++testX) // -1 : 1
            {
                if (nearbySampleFound)
                    break;
                for (uint16_t testY = -1; testY != 2; ++testY) // -1 : 1
                {
                    const index2 testIndex = candidateIndex + index2(testX, testY);
                    if (!isValidIndex(testIndex))
                        continue;

                    const uint32_t testOutput = grid[testIndex.x][testIndex.y];
                    if (testOutput != UINT32_MAX)
                    {
                        float distSqr = (outNoise[testOutput] - candidate).getLengthSquared();
                        if (distSqr < minDistSqr)
                        {
                            nearbySampleFound = true;
                            break;
                        }
                    }
                }
            }
            if (nearbySampleFound)
                continue;

            // "if a point is adequately far from existing samples, emit it as the next sample and add it to the active list"
            uint32_t& outNoiseIndex = grid[candidateIndex.x][candidateIndex.y];
            outNoiseIndex = static_cast<uint32_t>(outNoise.size());
            outNoise.push_back(candidate);
            activeSamples.push_back(outNoiseIndex);
            neighborPlaced = true;
            break;
        }
        // "if after k attempts no such point is found, instead remove i from the active list."
        if (!neighborPlaced)
        {
            std::swap(activeSamples.back(), activeSamples[currentNoiseIndex]);
            activeSamples.pop_back();
        }
    } while (activeSamples.size() > 0);

    return static_cast<int>(outNoise.size());
}
