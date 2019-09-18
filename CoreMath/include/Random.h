// Richard Shemaka - 2019
// https://github.com/rshemaka/CoreMath

#pragma once
#include "MathHelpers.h"
#include "Vector2.h"
#include "Vector3.h"
#include <random>

// disabling 'loss of precision' warnings as literals will be typed w/ double precision
#pragma warning(push)
#pragma warning(disable : 4244)

// random stream abstract base
// float & double precision currently supported.
// mersenne twister engine, uniform distribution.
template <class T, class VEC2, class VEC3>
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

        T t = randRange(0, T(size - MathT::epsilon<T>()));
        return uint32_t(MathT::floor<T>(t));
    }

    // returns a random direction of length 1
    VEC2 randomPointOnUnitCircle()
    {
        VEC2 point(1.0, 0.0);
        point.rotate(randRange(0.0, TwoPi));
        return point;
    }

    // returns a random point inside the unit circle
    VEC2 randomPointInUnitCircle()
    {
        VEC2 point(randRange(-1.0, 1.0), 0.0);
        point.rotate(randRange(0.0, Pi));
        return point;
    }

    // returns a random direction of length 1
    VEC3 randomPointOnUnitSphere()
    {
        // Muller (1959) method, has problem w/ poles in uniform distribution?
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
        T normalizeCoeff = (T)1.0 / MathT::sqrt<T>(lengthSquared);
        return VEC3(x, y, z) * normalizeCoeff;
    }

    // returns a random point inside the unit sphere
    VEC3 randomPointInUnitSphere()
    {
        VEC3 pointOnUnitSphere = randomPointOnUnitSphere();
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
class randomStream : public randomStreamBase<float, vec2, vec3>
{
  public:
    randomStream() : randomStreamBase<float, vec2, vec3>()
    {
        std::random_device rd{};
        rng = std::mt19937{rd()};
    }

    randomStream(unsigned int seed) : randomStreamBase<float, vec2, vec3>()
    {
        rng = std::mt19937{seed};
    }

    virtual float rand01() override
    {
        return distribution(rng);
    }

  private:
    std::mt19937 rng;
};

// 64-bit random stream
class randomStream_64 : public randomStreamBase<double, vec2_64, vec3_64>
{
  public:
    randomStream_64() : randomStreamBase<double, vec2_64, vec3_64>()
    {
        std::random_device rd{};
        rng = std::mt19937_64{rd()};
    }

    randomStream_64(unsigned int seed) : randomStreamBase<double, vec2_64, vec3_64>()
    {
        rng = std::mt19937_64{seed};
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
vec2 randomPointOnUnitCircle()
{
    return gRandom.randomPointOnUnitCircle();
}

// returns a random point inside the unit circle
vec2 randomPointInUnitCircle()
{
    return gRandom.randomPointInUnitCircle();
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
