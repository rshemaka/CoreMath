// Richard Shemaka - 2019
// https://github.com/rshemaka/CoreMath

#pragma once
#include <cmath>
#include <cfloat>

constexpr float Pi = 3.141592f;
constexpr float TwoPi = 6.2831853f;

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

    // templated sine
    template <class T>
    inline T sin(T t)
    {
        throw std::logic_error("Templated sin should be specialized for all template types.");
    }
    template <>
    inline float sin(float t)
    {
        return std::sinf(t);
    }
    template <>
    inline double sin(double t)
    {
        return std::sin(t);
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
} // namespace MathT
