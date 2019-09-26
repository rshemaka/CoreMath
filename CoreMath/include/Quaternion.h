// Richard Shemaka - 2019
// https://github.com/rshemaka/CoreMath

// Sources:
// https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
// https://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion

#pragma once
#include "MathHelpers.h"
#include "Vector3.h"

// disabling 'loss of precision' warnings as literals will be typed w/ double precision
#pragma warning(push)
#pragma warning(disable : 4244)

// quaternion representation of 3d rotation
//
// float & double precision currently supported. 32bit fixed point in the future, hopefully.
//
// see the end of the file for ease-of-use typedefs.
// in general, use 'quat' as the type around your code.
//
template <class T>
class t_quat
{
  public:
    t_quat() {}
    t_quat(T inRoll, T inPitch, T inYaw); // input in degrees
    t_quat(T inW, T inX, T inY, T inZ) : w(inW), x(inX), y(inY), z(inZ) {}

    inline T getLength() const;
    inline T getLengthSquared() const;

    void normalize();
    inline bool isUnit(T epsilon = 0.0001) const;
    inline t_quat<T> getUnit() const;

    t_vec3<T> rotateVector(const t_vec3<T>& v);

    // output in degrees
    void getEulerAngles(T& outRoll, T& outPitch, T& outYaw) const;

  private:
    T w = 1.0;
    T x = 0.0;
    T y = 0.0;
    T z = 0.0;
};

template <class T>
t_quat<T>::t_quat(T inRoll, T inPitch, T inYaw)
{
    inRoll *= DegToRads;
    inPitch *= DegToRads;
    inYaw *= DegToRads;

    T cr = MathT::cos<T>(inRoll * 0.5);
    T sr = MathT::sin<T>(inRoll * 0.5);
    T cp = MathT::cos<T>(inPitch * 0.5);
    T sp = MathT::sin<T>(inPitch * 0.5);
    T cy = MathT::cos<T>(inYaw * 0.5);
    T sy = MathT::sin<T>(inYaw * 0.5);

    w = cy * cp * cr + sy * sp * sr;
    x = cy * cp * sr - sy * sp * cr;
    y = sy * cp * sr + cy * sp * cr;
    z = sy * cp * cr - cy * sp * sr;
}

template <class T>
inline T t_quat<T>::getLength() const
{
    return MathT::sqrt<T>(w * w + x * x + y * y + z * z);
}

template <class T>
inline T t_quat<T>::getLengthSquared() const
{
    return (w * w + x * x + y * y + z * z);
}

template <class T>
inline void t_quat<T>::normalize()
{
    const T length = getLength();
    w /= length;
    x /= length;
    y /= length;
    z /= length;
}

template <class T>
inline bool t_quat<T>::isUnit(T epsilon) const
{
    return (MathT::abs<T>(getLengthSquared() - 1) < epsilon);
}

template <class T>
inline t_quat<T> t_quat<T>::getUnit() const
{
    t_quat outNorm = *this;
    outNorm.normalize();
    return outNorm;
}

template <class T>
inline t_vec3<T> t_quat<T>::rotateVector(const t_vec3<T>& v)
{
    const t_vec3<T> u(x, y, z);
    const float s = w;
    return 2.0 * t_vec3<T>::dot(u, v) * u + (s * s - t_vec3<T>::dot(u, u)) * v + 2.0 * s * t_vec3<T>::cross(u, v);
}

// output in degrees
template <class T>
inline void t_quat<T>::getEulerAngles(T& outRoll, T& outPitch, T& outYaw) const
{
    // roll (x-axis rotation)
    T sinr_cosp = 2.0 * (w * x + y * z);
    T cosr_cosp = 1.0 - 2.0 * (x * x + y * y);
    outRoll = MathT::atan2<T>(sinr_cosp, cosr_cosp);
    outRoll *= RadsToDeg;

    // pitch (y-axis rotation)
    T sinp = 2.0 * (w * y - z * x);
    if (MathT::abs<T>(sinp) >= 1)
        outPitch = MathT::copysign<T>(Pi / 2, sinp); // use 90 degrees if out of range
    else
        outPitch = MathT::asin<T>(sinp);
    outPitch *= RadsToDeg;

    // yaw (z-axis rotation)
    double siny_cosp = 2.0 * (w * z + x * y);
    double cosy_cosp = 1.0 - 2.0 * (y * y + z * z);
    outYaw = MathT::atan2<T>(siny_cosp, cosy_cosp);
    outYaw *= RadsToDeg;
}

typedef t_quat<float> quat_32;
typedef t_quat<double> quat_64;

typedef quat_32 quat;

#pragma warning(pop)
