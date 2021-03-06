// Richard Shemaka - 2020
// https://github.com/rshemaka/CoreMath

// Sources:
// https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
// http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/transforms/index.htm
// https://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion

#pragma once
#include "MathHelpers.h"
#include "Vector3.h"

// disabling 'loss of precision' warnings as literals will be typed w/ double precision
#pragma warning(push)
#pragma warning(disable : 4244)

// quaternion representation of 3D rotation
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
    t_quat(T inRoll, T inPitch, T inYaw); // input in radians
    t_quat(T inW, T inX, T inY, T inZ) : w(inW), x(inX), y(inY), z(inZ) {}

    static const t_quat<T>& getIdentity();

    inline T getLength() const;
    inline T getLengthSquared() const;

    inline void normalize();
    inline bool isUnit(T epsilon = 0.0001) const;
    inline t_quat<T> getUnit() const;

    inline t_vec3<T> getForward() const;
    inline t_vec3<T> getRight() const;
    inline t_vec3<T> getUp() const;

    t_vec3<T> rotateVector(const t_vec3<T>& v) const;

    // output in radians
    void getEulerAngles(T& outRoll, T& outPitch, T& outYaw) const;

    T w;
    T x;
    T y;
    T z;
};

template <class T>
t_quat<T>::t_quat(T inRoll, T inPitch, T inYaw)
{
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
inline const t_quat<T>& t_quat<T>::getIdentity()
{
    const static t_quat<T> identity(1.0, 0.0, 0.0, 0.0);
    return identity;
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
inline t_vec3<T> t_quat<T>::getForward() const
{
    return rotateVector(t_vec3<T>::getForward());
}

template <class T>
inline t_vec3<T> t_quat<T>::getRight() const
{
    return rotateVector(t_vec3<T>::getRight());
}

template <class T>
inline t_vec3<T> t_quat<T>::getUp() const
{
    return rotateVector(t_vec3<T>::getUp());
}

template <class T>
inline t_vec3<T> t_quat<T>::rotateVector(const t_vec3<T>& v) const
{
    const t_vec3<T> u(x, y, z);
    return 2.0 * t_vec3<T>::dot(u, v) * u + (w * w - t_vec3<T>::dot(u, u)) * v + 2.0 * w * t_vec3<T>::cross(u, v);
}

// output in radians
template <class T>
inline void t_quat<T>::getEulerAngles(T& outRoll, T& outPitch, T& outYaw) const
{
    // roll (x-axis rotation)
    T sinr_cosp = 2.0 * (w * x + y * z);
    T cosr_cosp = 1.0 - 2.0 * (x * x + y * y);
    outRoll = MathT::atan2<T>(sinr_cosp, cosr_cosp);
    outRoll = MathT::clampAngle<T>(outRoll);

    // pitch (y-axis rotation)
    T sinp = 2.0 * (w * y - z * x);
    if (MathT::abs<T>(sinp) >= 1)
        outPitch = MathT::copysign<T>(Pi / 2, sinp); // use 90 degrees if out of range
    else
        outPitch = MathT::asin<T>(sinp);
    outPitch = MathT::clampAngle<T>(outPitch);

    // yaw (z-axis rotation)
    double siny_cosp = 2.0 * (w * z + x * y);
    double cosy_cosp = 1.0 - 2.0 * (y * y + z * z);
    outYaw = MathT::atan2<T>(siny_cosp, cosy_cosp);
    outYaw = MathT::clampAngle<T>(outYaw);
}

typedef t_quat<float> quat_32;
typedef t_quat<double> quat_64;

// quaternion representation of 3D rotation
typedef quat_32 quat;

#pragma warning(pop)
