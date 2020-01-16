// Richard Shemaka - 2020
// https://github.com/rshemaka/CoreMath

#pragma once
#include <cfloat>
#include <cmath>

constexpr float Pi = 3.141592f;
constexpr double Pi_64 = 3.141592653589793;
constexpr float TwoPi = 6.2831853f;
constexpr double TwoPi_64 = 6.283185307179586;

constexpr float DegToRads = Pi / 180.f;
constexpr float RadsToDeg = 180.f / Pi;

namespace MathHelpers
{
    inline bool isNearlyEqual(float x, float y, float epsilon = 0.0001f)
    {
        return (fabs(x - y) < epsilon);
    }

    inline bool isNearlyEqual(double x, double y, double epsilon = 0.0001)
    {
        return (abs(x - y) < epsilon);
    }

    inline bool isNearlyEqual(float x, double y, float epsilon = 0.0001f)
    {
        return isNearlyEqual(x, float(y), epsilon);
    }

    inline bool isNearlyEqual(double x, float y, float epsilon = 0.0001f)
    {
        return isNearlyEqual(float(x), y, epsilon);
    }
} // namespace MathHelpers

// templatized versions of std math functions to aid w/ templatized precision types
namespace MathT
{
    // templated absolute
    template <class T>
    inline T abs(T x)
    {
        throw std::logic_error("Templated abs should be specialized for all template types.");
    }
    template <>
    inline float abs(float x)
    {
        return std::fabs(x);
    }
    template <>
    inline double abs(double x)
    {
        return std::abs(x);
    }

    // templated floor
    template <class T>
    inline T floor(T number)
    {
        throw std::logic_error("Templated floor should be specialized for all template types.");
    }
    template <>
    inline float floor(float number)
    {
        return std::floorf(number);
    }
    template <>
    inline double floor(double number)
    {
        return std::floor(number);
    }

    template <class T>
    inline T sqrt(T x)
    {
        throw std::logic_error("Templated sqrt should be specialized for all template types.");
    }
    template <>
    inline float sqrt(float number)
    {
        return std::sqrtf(number);
    }
    template <>
    inline double sqrt(double number)
    {
        return std::sqrt(number);
    }

    // templated cosine
    template <class T>
    inline T cos(T x)
    {
        throw std::logic_error("Templated cos should be specialized for all template types.");
    }
    template <>
    inline float cos(float x)
    {
        return std::cosf(x);
    }
    template <>
    inline double cos(double x)
    {
        return std::cos(x);
    }

    // templated acos
    template <class T>
    inline T acos(T x)
    {
        throw std::logic_error("Templated acos should be specialized for all template types.");
    }
    template <>
    inline float acos(float x)
    {
        return std::acosf(x);
    }
    template <>
    inline double acos(double x)
    {
        return std::acos(x);
    }

    // templated sine
    template <class T>
    inline T sin(T x)
    {
        throw std::logic_error("Templated sin should be specialized for all template types.");
    }
    template <>
    inline float sin(float x)
    {
        return std::sinf(x);
    }
    template <>
    inline double sin(double x)
    {
        return std::sin(x);
    }

    // templated asin
    template <class T>
    inline T asin(T x)
    {
        throw std::logic_error("Templated asin should be specialized for all template types.");
    }
    template <>
    inline float asin(float x)
    {
        return std::asinf(x);
    }
    template <>
    inline double asin(double x)
    {
        return std::asin(x);
    }

    // templated atan2
    template <class T>
    inline T atan2(T y, T x)
    {
        throw std::logic_error("Templated atan2 should be specialized for all template types.");
    }
    template <>
    inline float atan2(float y, float x)
    {
        return std::atan2f(y, x);
    }
    template <>
    inline double atan2(double y, double x)
    {
        return std::atan2(y, x);
    }

    // templated copysign
    template <class T>
    inline T copysign(T number, T sign)
    {
        throw std::logic_error("Templated copysign should be specialized for all template types.");
    }
    template <>
    inline float copysign(float number, float sign)
    {
        return std::copysignf(number, sign);
    }
    template <>
    inline double copysign(double number, double sign)
    {
        return std::copysign(number, sign);
    }

    // templated mod
    template <class T>
    inline T mod(T numer, T denom)
    {
        throw std::logic_error("Templated mod should be specialized for all template types.");
    }
    template <>
    inline float mod(float numer, float denom)
    {
        return std::fmodf(numer, denom);
    }
    template <>
    inline double mod(double numer, double denom)
    {
        return std::fmod(numer, denom);
    }

    // templated pi
    template <class T>
    constexpr T pi()
    {
        throw std::logic_error("Templated pi should be specialized for all template types.");
    }
    template <>
    constexpr float pi()
    {
        return Pi;
    }
    template <>
    constexpr double pi()
    {
        return Pi_64;
    }

    // templated twoPi
    template <class T>
    constexpr T twoPi()
    {
        throw std::logic_error("Templated twoPi should be specialized for all template types.");
    }
    template <>
    constexpr float twoPi()
    {
        return TwoPi;
    }
    template <>
    constexpr double twoPi()
    {
        return TwoPi_64;
    }

    // templated epsilon
    template <class T>
    constexpr T epsilon()
    {
        throw std::logic_error("Templated epsilon should be specialized for all template types.");
    }
    template <>
    constexpr float epsilon()
    {
        return FLT_EPSILON;
    }
    template <>
    constexpr double epsilon()
    {
        return DBL_EPSILON;
    }

    template <class T>
    T clampAngle(T theta)
    {
        theta = MathT::mod<T>(theta, MathT::twoPi<T>());
        if (theta < 0.0)
            theta += MathT::twoPi<T>();
        return theta;
    }
} // namespace MathT
