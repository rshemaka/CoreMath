// Richard Shemaka - 2019
// https://github.com/rshemaka/CoreMath

#pragma once
#include "Vector3.h"
#include <random>

// random stream
//
// float & double precision currently supported.
// mersenne twister engine, uniform distribution.
template <class T>
class randomStream
{
  public:
    randomStream()
    {
        std::random_device rd{};
        rng = std::mt19937{rd()};
        distribution = std::uniform_real_distribution<T>(0.0, 1.0);
    }

    randomStream(unsigned int seed)
    {
        rng = std::mt19937{seed};
        distribution = std::uniform_real_distribution<T>(0.0, 1.0);
    }

    T rand01()
    {
        return distribution(rng);
    }

    T randRange(T min, T max)
    {
        return (rand01() * (max - min)) + min;
    }

    vec3 randomPointOnUnitSphere()
    {
        // Muller (1959) method
        // https://dl.acm.org/citation.cfm?id=377946
        T x = randRange(-1.0, 1.0);
        T y = randRange(-1.0, 1.0);
        T z = randRange(-1.0, 1.0);
        T lengthSquared = (x * x) + (y * y) + (z * z);
        if (lengthSquared == 0)
        {
            x = 1.0;
            lengthSquared = 1.0;
        }
        T normalizeCoeff = (T)1.0 / sqrt(lengthSquared);
        return vec3(x, y, z) * normalizeCoeff;
    }

    vec3 randomPointInUnitSphere()
    {
        vec3 pointOnUnitSphere = randomPointOnUnitSphere();
        return pointOnUnitSphere * rand01();
    }

  private:
    std::mt19937 rng;
    std::uniform_real_distribution<T> distribution;
};

randomStream<float> gRandom;

// returns a random number in the range of [0.0, 1.0)
float rand01()
{
    return gRandom.rand01();
}

// returns a random number in the specified range of [min, max)
float randRange(float min, float max)
{
    return gRandom.randRange(min, max);
}

// returns a random true or false
bool coinFlip()
{
	return rand01() < 0.5f;
}

// returns a random index given a container size
size_t randomIndex(size_t size)
{
	if (size == 0)
		return 0;

	float t = randRange(0, float(size));
	return size_t(floorf(t));
}

// returns a random direction of length 1
vec3 randomPointOnUnitSphere()
{
    return gRandom.randomPointOnUnitSphere();
}

// returns a random point inside the unit sphere
vec3 randomPointInUnitSphere()
{
    return gRandom.randomPointInUnitSphere();
}
