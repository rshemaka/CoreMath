// Richard Shemaka - 2019
// https://github.com/rshemaka/cppmath

#pragma once
#include <vector>
#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"

// blue noise via Poisson disk sampling.
// supported: 1d, 2d positions
// someday: 3d, rotations?
//
// Source:
// https://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf

// given a bounding range, generate an undetermined number of random samples w/ a minimum spacing using Poisson disks
void generatePoissonDiskSamples1D(std::vector<float>& outSamples, float rangeMin, float rangeMax, float minDist, int sampleLimit = 30)
{
	outSamples.empty();

	if (rangeMin > rangeMax)
		return;

	// not enough room to scatter two points? just toss a random sample in and return
	if ((rangeMax - rangeMin) < minDist)
	{
		outSamples.push_back(randRange(rangeMin, rangeMax));
		return;
	}

	// 1d blue noise can simply march from one end to the other
	float latestSample = randRange(rangeMin, rangeMin + minDist);
	outSamples.push_back(latestSample);
	while (rangeMax - latestSample > minDist)
	{
		float sampleMin = latestSample + minDist;
		float sampleMax = fmin(sampleMin + minDist, rangeMax);
		latestSample = randRange(sampleMin, sampleMax);
		outSamples.push_back(latestSample);
	}
}

// given a bounding range, generate an undetermined number of random points w/ a minimum spacing using Poisson disks
void calculatePoissonDiskSamples2D(std::vector<vec2>& outSamples, vec2 rangeMin, vec2 rangeMax, float minDist, int sampleLimit = 30)
{
	outSamples.empty();

	if (rangeMin.x > rangeMax.x || rangeMin.y > rangeMax.y)
		return;

	const vec2 rangeSize = rangeMax - rangeMin;
	const float cellSize = minDist / sqrtf(2);
	const int xCells = int(ceilf(rangeSize.x / cellSize));
	const int yCells = int(ceilf(rangeSize.y / cellSize));
	outSamples.reserve(xCells * yCells);

	// 2d spatial grid
	std::vector<std::vector<uint32_t>> grid(xCells, std::vector<uint32_t>(yCells, -1));
	// function to compute grid x,y given a vec2
	auto calculateGridCell = [cellSize](const vec2& vec)
	{
		index2 outIndex;
		outIndex.x = int(floorf(vec.x / cellSize));
		outIndex.y = int(floorf(vec.y / cellSize));
		return outIndex;
	};

	// add the first sample at random
	vec2 firstSample = vec2(randRange(rangeMin.x, rangeMax.x), randRange(rangeMin.y, rangeMin.y));
	outSamples.push_back(firstSample);
	index2 index = calculateGridCell(firstSample);
	grid[index.x][index.y] = 0;

	std::vector<uint32_t> activeSamples;
	activeSamples.push_back(0);

	std::vector<vec2> candidates(sampleLimit);
	do
	{
		uint32_t randomSampleIndex = randIndex(activeSamples.size());
		vec2 randomSample = outSamples[randomSampleIndex];
		for (int i = 0, n = sampleLimit; i != n; ++i)
		{
			float randomThrow = randRange(minDist, minDist * 2.f);
			randomThrow = coinFlip() ? randomThrow : -randomThrow;
			vec2 candidate = vec2(randomThrow, 0.f);
			float randomSpin = randRange(0, TwoPi);
			candidate.rotate(randomSpin);
			candidate = randomSample + candidate;
			//float candidate = coinFlip() ? randomSample + randomThrow : randomSample - randomThrow;

		}
	} while (activeSamples.size() > 0);
}

void calculatePoissonDiskSamples3D(std::vector<vec3>& outSamples, vec3 rangeMin, vec3 rangeMax, float minDist, int sampleLimit = 30)
{
	/*
	outSamples.empty();

	if (rangeMin > rangeMax)
		return;

	float rangeSize = rangeMax - rangeMin;
	int numCells = int(ceilf(rangeSize / minDist));
	if (numCells == 1)
	{
		outSamples.push_back(randRange(rangeMin, rangeMax));
		return;
	}

	std::vector<uint32_t> grid(numCells, -1);

	float firstSample = randRange(rangeMin, rangeMax);
	outSamples.push_back(firstSample);
	int firstSampleCell = int(floorf(firstSample / minDist));
	grid[firstSampleCell] = 0;

	std::vector<uint32_t> activeSamples;
	activeSamples.push_back(0);

	std::vector<float> candidates(sampleLimit);
	do
	{
		uint32_t randomSampleIndex = randomIndex(activeSamples.size());
		float randomSample = outSamples[randomSampleIndex];
		for (int i = 0, n = sampleLimit; i != n; ++i)
		{
			float randomThrow = randRange(minDist, minDist * 2.f);
			float candidate = coinFlip() ? randomSample + randomThrow : randomSample - randomThrow;

		}
	} while (activeSamples.size() > 0);
	*/
}