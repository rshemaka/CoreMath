// Richard Shemaka - 2019
// https://github.com/rshemaka/CoreMath

#pragma once
#include "MathHelpers.h"
#include <iostream>
#include <stdexcept>

// 3d arithmetic vector
//
// float & double precision currently supported. 32bit fixed point in the
// future, hopefully.
//
// see the end of the file for ease-of-use typedefs.
// in general, use 'vec3' as the type around your code.
//
template <class T>
class t_vec3
{
  public:
    t_vec3() {}
    t_vec3(T inT) : x(inT), y(inT), z(inT) {}
    t_vec3(T inX, T inY, T inZ) : x(inX), y(inY), z(inZ) {}

    T x = 0.0;
    T y = 0.0;
    T z = 0.0;

    inline T getLength() const;
    inline T getLengthSquared() const;

    inline void normalize();
    inline bool isUnit(T epsilon = 0.0001) const;
    inline t_vec3<T> getUnit() const;

    inline bool isEqual(const t_vec3<T>& v2, T epsilon = 0.0001) const;

    static inline T dot(const t_vec3<T>& v1, const t_vec3<T>& v2);
    inline T dot(const t_vec3<T>& v2);

    static inline t_vec3<T> cross(const t_vec3<T>& v1, const t_vec3<T>& v2);
    inline t_vec3<T> cross(const t_vec3<T>& v2);

    inline std::ostream& operator<<(std::ostream& os);

    inline t_vec3<T>& operator+=(const t_vec3<T>& v2);
    inline t_vec3<T>& operator-=(const t_vec3<T>& v2);
    inline t_vec3<T>& operator*=(const t_vec3<T>& v2);
    inline t_vec3<T>& operator/=(const t_vec3<T>& v2);
    inline t_vec3<T>& operator*=(T t);
    inline t_vec3<T>& operator/=(T t);
};

#pragma region Global_Operators
template <class T>
inline t_vec3<T> operator+(const t_vec3<T>& v1, const t_vec3<T>& v2)
{
    return t_vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
template <class T>
inline t_vec3<T> operator-(const t_vec3<T>& v1, const t_vec3<T>& v2)
{
    return t_vec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
template <class T>
inline t_vec3<T> operator*(const t_vec3<T>& v, float t)
{
    return t_vec3<T>(v.x * t, v.y * t, v.z * t);
}
template <class T>
inline t_vec3<T> operator*(float t, const t_vec3<T>& v)
{
    return v * t;
}
template <class T>
inline t_vec3<T> operator/(const t_vec3<T>& v, float t)
{
    return t_vec3<T>(v.x / t, v.y / t, v.z / t);
}
#pragma endregion

#pragma region Member_Functions
template <class T>
inline T t_vec3<T>::getLength() const
{
    return sqrt(x * x + y * y + z * z);
}
template <class T>
inline T t_vec3<T>::getLengthSquared() const
{
    return (x * x + y * y + z * z);
}

template <class T>
inline void t_vec3<T>::normalize()
{
    T length = getLength();
    x /= length;
    y /= length;
    z /= length;
}

template <class T>
inline bool t_vec3<T>::isUnit(T epsilon) const
{
    return (MathT::abs<T>(getLengthSquared() - 1) < epsilon);
}

template <class T>
inline t_vec3<T> t_vec3<T>::getUnit() const
{
    t_vec3 outNorm = *this;
    outNorm.normalize();
    return outNorm;
}

template <class T>
inline bool t_vec3<T>::isEqual(const t_vec3<T>& v2, T epsilon) const
{
    return (MathT::abs<T>((v2 - *this).getLengthSquared()) < epsilon);
}

template <class T>
inline T t_vec3<T>::dot(const t_vec3<T>& v1, const t_vec3<T>& v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}
template <class T>
inline T t_vec3<T>::dot(const t_vec3<T>& v2)
{
    return (x * v2.x) + (y * v2.y) + (z * v2.z);
}

template <class T>
inline t_vec3<T> t_vec3<T>::cross(const t_vec3<T>& v1, const t_vec3<T>& v2)
{
    T x = (v1.y * v2.z) - (v1.z * v2.y);
    T y = (v1.x * v2.z) - (v1.z * v2.x);
    T z = (v1.x * v2.y) - (v1.y * v2.z);
    return t_vec3<T>(x, y, z);
}
template <class T>
inline t_vec3<T> t_vec3<T>::cross(const t_vec3<T>& v2)
{
    T x = (y * v2.z) - (z * v2.y);
    T y = (x * v2.z) - (z * v2.x);
    T z = (x * v2.y) - (y * v2.z);
    return t_vec3(x, y, z);
}
#pragma endregion

#pragma region Member_Operators
template <class T>
inline std::ostream& t_vec3<T>::operator<<(std::ostream& os)
{
    os << x << " " << y << " " << z;
    return os;
}

template <class T>
inline t_vec3<T>& t_vec3<T>::operator+=(const t_vec3<T>& v2)
{
    x += v2.x;
    y += v2.y;
    z += v2.z;
    return *this;
}

template <class T>
inline t_vec3<T>& t_vec3<T>::operator-=(const t_vec3<T>& v2)
{
    x -= v2.x;
    y -= v2.y;
    z -= v2.z;
    return *this;
}

template <class T>
inline t_vec3<T>& t_vec3<T>::operator*=(const t_vec3<T>& v2)
{
    x *= v2.x;
    y *= v2.y;
    z *= v2.z;
    return *this;
}

template <class T>
inline t_vec3<T>& t_vec3<T>::operator/=(const t_vec3<T>& v2)
{
    x /= v2.x;
    y /= v2.y;
    z /= v2.z;
    return *this;
}

template <class T>
inline t_vec3<T>& t_vec3<T>::operator*=(T t)
{
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

template <class T>
inline t_vec3<T>& t_vec3<T>::operator/=(T t)
{
    x /= t;
    y /= t;
    z /= t;
    return *this;
}
#pragma endregion

typedef t_vec3<float> vec3_32;
typedef t_vec3<double> vec3_64;

typedef vec3_32 vec3;
