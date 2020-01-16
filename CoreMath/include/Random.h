// Richard Shemaka - 2020
// https://github.com/rshemaka/CoreMath
//
// Sources:
// https://math.stackexchange.com/questions/131336/uniform-random-quaternion-in-a-restricted-angle-range

#pragma once
#include "MathHelpers.h"
#include "Quaternion.h"
#include "Vector2.h"
#include "Vector3.h"
#include <random>

// disabling 'loss of precision' warnings as literals will be typed w/ double precision
#pragma warning(push)
#pragma warning(disable : 4244)

// random stream abstract base
// float & double precision currently supported.
// mersenne twister engine, uniform distribution.
template <class T, class VEC2, class VEC3, class QUAT>
class t_randomStream
{
  public:
    virtual ~t_randomStream() {}

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

        T t = randRange(0, static_cast<T>(size) - MathT::epsilon<T>());
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
        T normalizeCoeff = 1.0 / MathT::sqrt<T>(lengthSquared);
        return VEC3(x, y, z) * normalizeCoeff;
    }

    // returns a random point inside the unit sphere
    VEC3 randomPointInUnitSphere()
    {
        VEC3 pointOnUnitSphere = randomPointOnUnitSphere();
        return pointOnUnitSphere * (MathT::epsilon<T>() + rand01());
    }

    // returns a random rotation
    QUAT randomRotation()
    {
        // https://math.stackexchange.com/questions/131336/uniform-random-quaternion-in-a-restricted-angle-range
        const T s = rand01();
        const T a1 = MathT::sqrt<T>(1.0 - s);
        const T a2 = MathT::sqrt<T>(s);
        const T t1 = MathT::twoPi<T>() * rand01();
        const T t2 = MathT::twoPi<T>() * rand01();
        const T w = MathT::cos<T>(t2) * a2;
        const T x = MathT::sin<T>(t1) * a1;
        const T y = MathT::cos<T>(t1) * a1;
        const T z = MathT::sin<T>(t2) * a2;
        return QUAT(w, x, y, z);
    }

  protected:
    t_randomStream()
    {
        distribution = std::uniform_real_distribution<T>(0.0, 1.0);
    }

    std::uniform_real_distribution<T> distribution;
};

// 32-bit random stream
class randomStream_32 : public t_randomStream<float, vec2, vec3, quat>
{
  public:
    randomStream_32() : t_randomStream<float, vec2, vec3, quat>()
    {
        std::random_device rd{};
        rng = std::mt19937{rd()};
    }

    randomStream_32(unsigned int seed) : t_randomStream<float, vec2, vec3, quat>()
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
class randomStream_64 : public t_randomStream<double, vec2_64, vec3_64, quat_64>
{
  public:
    randomStream_64() : t_randomStream<double, vec2_64, vec3_64, quat_64>()
    {
        std::random_device rd{};
        rng = std::mt19937_64{rd()};
    }

    randomStream_64(unsigned int seed) : t_randomStream<double, vec2_64, vec3_64, quat_64>()
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

// random stream, mersenne twister engine, uniform distribution
typedef randomStream_32 randomStream;

// global random stream (32-bit)
static randomStream gRandom;

// returns a random number in the range of [0.0, 1.0)
inline float rand01()
{
    return gRandom.rand01();
}

// returns a random number in the specified range of [min, max)
inline float randRange(float min, float max)
{
    return gRandom.randRange(min, max);
}

// returns a random true or false
inline bool coinFlip()
{
    return gRandom.coinFlip();
}

// returns a random index given a container size
inline uint32_t randIndex(size_t size)
{
    return gRandom.randIndex(size);
}

// returns a random direction of length 1
inline vec2 randomPointOnUnitCircle()
{
    return gRandom.randomPointOnUnitCircle();
}

// returns a random point inside the unit circle
inline vec2 randomPointInUnitCircle()
{
    return gRandom.randomPointInUnitCircle();
}

// returns a random direction of length 1
inline vec3 randomPointOnUnitSphere()
{
    return gRandom.randomPointOnUnitSphere();
}

// returns a random point inside the unit sphere
inline vec3 randomPointInUnitSphere()
{
    return gRandom.randomPointInUnitSphere();
}

// returns a random rotation
inline quat randomRotation()
{
    return gRandom.randomRotation();
}

#pragma warning(pop)
