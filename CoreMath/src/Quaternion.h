// Richard Shemaka - 2019
// https://github.com/rshemaka/CoreMath

// Sources:
// https://en.wikipedia.org/wiki/Quaternion
// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

#pragma once
#include "MathHelpers.h"

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

    // arguments in degrees
    static t_quat<T> makeFromEuler(T roll, T pitch, T yaw);

    // output in degrees
    void getEulerAngles(T& outRoll, T& outPitch, T& outYaw) const;

  private:
    T w;
    T x;
    T y;
    T z;
};

// arguments in degrees
template <class T>
inline t_quat<T> t_quat<T>::makeFromEuler(T roll, T pitch, T yaw)
{
    roll *= DegToRads;
    pitch *= DegToRads;
    yaw *= DegToRads;

    T cr = MathT::cos<T>(roll * 0.5);
    T sr = MathT::sin<T>(roll * 0.5);
    T cp = MathT::cos<T>(pitch * 0.5);
    T sp = MathT::sin<T>(pitch * 0.5);
    T cy = MathT::cos<T>(yaw * 0.5);
    T sy = MathT::sin<T>(yaw * 0.5);

    t_quat<T> ret;

    ret.w = cy * cp * cr + sy * sp * sr;
    ret.x = cy * cp * sr - sy * sp * cr;
    ret.y = sy * cp * sr + cy * sp * cr;
    ret.z = sy * cp * cr - cy * sp * sr;

    return ret;
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
