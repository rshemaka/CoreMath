// Richard Shemaka - 2019
// https://github.com/rshemaka/CoreMath

#pragma once
#include "MathHelpers.h"
#include "Vector3.h"
#include <random>

// disabling 'loss of precision' warnings as literals will be typed w/ double
// precision
#pragma warning(push)
#pragma warning(disable : 4244)

// random stream
//
// float & double precision currently supported.
// mersenne twister engine, uniform distribution.
template <class T, class U>
class randomStreamBase
{
  public:
	virtual ~randomStreamBase() {}

	// returns a random number in the range of [0.0, 1.0)
    virtual T rand01() = 0;

	// returns a random number in the specified range of [min, max)
    T randRange(T min, T max)
    {
        return (rand01() * (max - min)) + min;
    }

	// returns a random true or false
	bool coinFlip()
	{
		return rand01() < 0.5;
	}

	// returns a random index given a container size
	uint32_t randIndex(size_t size)
	{
		if (size == 0)
			return 0;

		T t = randRange(0, T(size));
		return uint32_t(MathT::floor<T>(t));
	}

	// returns a random direction of length 1
    U randomPointOnUnitSphere()
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
        return U(x, y, z) * normalizeCoeff;
    }

	// returns a random point inside the unit sphere
    U randomPointInUnitSphere()
    {
        U pointOnUnitSphere = randomPointOnUnitSphere();
        return pointOnUnitSphere * rand01();
    }

  protected:
    randomStreamBase()
    {
        distribution = std::uniform_real_distribution<T>(0.0, 1.0);
    }

    std::uniform_real_distribution<T> distribution;
};

// 32-bit random stream
class randomStream : public randomStreamBase<float, vec3>
{
  public:
    randomStream() : randomStreamBase<float, vec3>()
    {
        std::random_device rd{};
        rng = std::mt19937{rd()};
    }

	randomStream(unsigned int seed) : randomStreamBase<float, vec3>()
	{
		rng = std::mt19937{ seed };
	}

    virtual float rand01() override
    {
        return distribution(rng);
    }

  private:
    std::mt19937 rng;
};

// 64-bit random stream
class randomStream_64 : public randomStreamBase<double, vec3_64>
{
public:
	randomStream_64() : randomStreamBase<double, vec3_64>()
	{
		std::random_device rd{};
		rng = std::mt19937_64{ rd() };
	}

	randomStream_64(unsigned int seed) : randomStreamBase<double, vec3_64>()
	{
		rng = std::mt19937_64{ seed };
	}

	virtual double rand01() override
	{
		return distribution(rng);
	}

private:
	std::mt19937_64 rng;
};

// global random stream (32-bit)
randomStream gRandom;

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
    return gRandom.coinFlip();
}

// returns a random index given a container size
uint32_t randIndex(size_t size)
{
	return gRandom.randIndex(size);
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

#pragma warning(pop)
