// Richard Shemaka - 2019
// https://github.com/rshemaka/CoreMath

#pragma once
#include "MathHelpers.h"
#include <iostream>
#include <stdexcept>

// 2d arithmetic vector
//
// float & double precision currently supported.
// ints somewhat supported, not yet fully tested.
//
// see the end of the file for ease-of-use typedefs.
// in general, use 'vec2' as the type around your code.
//
template <class T>
class t_vec2
{
  public:
    t_vec2() {}
    t_vec2(T inT) : x(inT), y(inT) {}
    t_vec2(T inX, T inY) : x(inX), y(inY) {}

    T x = 0;
    T y = 0;

    inline T getLength() const;
    inline T getLengthSquared() const;

    inline void normalize();
    inline bool isUnit(T epsilon = 0.0001) const;
    inline t_vec2<T> getUnit() const;

    inline bool isEqual(const t_vec2<T>& v2, T epsilon = 0.0001) const;

    static inline T dot(const t_vec2<T>& v1, const t_vec2<T>& v2);
    inline T dot(const t_vec2<T>& v2);

    // anti-clockwise, radians
    static inline t_vec2<T> rotate(const t_vec2<T>& v1, T rad);
    // anti-clockwise, radians
    inline void rotate(T rad);

    // anti-clockwise
    inline t_vec2<T> getPerpendicular() const;

    inline std::ostream& operator<<(std::ostream& os);

    inline t_vec2<T>& operator+=(const t_vec2<T>& v2);
    inline t_vec2<T>& operator-=(const t_vec2<T>& v2);
    inline t_vec2<T>& operator*=(const t_vec2<T>& v2);
    inline t_vec2<T>& operator/=(const t_vec2<T>& v2);
    inline t_vec2<T>& operator*=(T t);
    inline t_vec2<T>& operator/=(T t);
};

#pragma region Global_Operators
template <class T>
inline t_vec2<T> operator+(const t_vec2<T>& v1, const t_vec2<T>& v2)
{
    return t_vec2<T>(v1.x + v2.x, v1.y + v2.y);
}
template <class T>
inline t_vec2<T> operator-(const t_vec2<T>& v1, const t_vec2<T>& v2)
{
    return t_vec2<T>(v1.x - v2.x, v1.y - v2.y);
}
template <class T>
inline t_vec2<T> operator*(const t_vec2<T>& v, float t)
{
    return t_vec2<T>(v.x * t, v.y * t);
}
template <class T>
inline t_vec2<T> operator*(float t, const t_vec2<T>& v)
{
    return v * t;
}
template <class T>
inline t_vec2<T> operator/(const t_vec2<T>& v, float t)
{
    return t_vec2<T>(v.x / t, v.y / t);
}
template <class T>
inline float operator|(const t_vec2<T>& v1, const t_vec2<T>& v2)
{
    return v1.dot(v2);
}
#pragma endregion

#pragma region Member_Functions
template <class T>
inline T t_vec2<T>::getLength() const
{
    return sqrt(x * x + y * y);
}
template <class T>
inline T t_vec2<T>::getLengthSquared() const
{
    return (x * x + y * y);
}

template <class T>
inline void t_vec2<T>::normalize()
{
    T length = getLength();
    x /= length;
    y /= length;
}

template <class T>
inline bool t_vec2<T>::isUnit(T epsilon) const
{
    return (MathT::abs<T>(getLengthSquared() - 1) < epsilon);
}

template <class T>
inline t_vec2<T> t_vec2<T>::getUnit() const
{
    t_vec2 outNorm = *this;
    outNorm.normalize();
    return outNorm;
}

template <class T>
inline bool t_vec2<T>::isEqual(const t_vec2<T>& v2, T epsilon) const
{
    return (MathT::abs<T>((v2 - *this).getLengthSquared()) < epsilon);
}

template <class T>
inline T t_vec2<T>::dot(const t_vec2<T>& v1, const t_vec2<T>& v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}
template <class T>
inline T t_vec2<T>::dot(const t_vec2<T>& v2)
{
    return (x * v2.x) + (y * v2.y);
}
template <class T>
inline t_vec2<T> t_vec2<T>::rotate(const t_vec2<T>& v1, T rad)
{
    T cos = MathT::cos<T>(rad);
    T sin = MathT::sin<T>(rad);
    return t_vec2<T>((cos * v1.x) - (sin * v1.y), (sin * v1.x) - (cos * v1.y));
}
template <class T>
inline void t_vec2<T>::rotate(T rad)
{
    T cos = MathT::cos<T>(rad);
    T sin = MathT::sin<T>(rad);
    T oldX = x;
    T oldY = y;
    x = (cos * oldX) - (sin * oldY);
    y = (sin * oldX) - (cos * oldY);
}
template <class T>
inline t_vec2<T> t_vec2<T>::getPerpendicular() const
{
    return t_vec2<T>(-y, x);
}
#pragma endregion

#pragma region Member_Operators
template <class T>
inline std::ostream& t_vec2<T>::operator<<(std::ostream& os)
{
    os << "<" << x << ", " << y << ">";
    return os;
}

template <class T>
inline t_vec2<T>& t_vec2<T>::operator+=(const t_vec2<T>& v2)
{
    x += v2.x;
    y += v2.y;
    return *this;
}

template <class T>
inline t_vec2<T>& t_vec2<T>::operator-=(const t_vec2<T>& v2)
{
    x -= v2.x;
    y -= v2.y;
    return *this;
}

template <class T>
inline t_vec2<T>& t_vec2<T>::operator*=(const t_vec2<T>& v2)
{
    x *= v2.x;
    y *= v2.y;
    return *this;
}

template <class T>
inline t_vec2<T>& t_vec2<T>::operator/=(const t_vec2<T>& v2)
{
    x /= v2.x;
    y /= v2.y;
    return *this;
}

template <class T>
inline t_vec2<T>& t_vec2<T>::operator*=(T t)
{
    x *= t;
    y *= t;
    return *this;
}

template <class T>
inline t_vec2<T>& t_vec2<T>::operator/=(T t)
{
    x /= t;
    y /= t;
    return *this;
}
#pragma endregion

typedef t_vec2<float> vec2_32;
typedef t_vec2<double> vec2_64;

typedef vec2_32 vec2;
