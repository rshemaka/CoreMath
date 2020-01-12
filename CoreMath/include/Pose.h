// Richard Shemaka - 2020
// https://github.com/rshemaka/CoreMath

#pragma once
#include "Quaternion.h"
#include "Vector3.h"

// 3d transform with uniform scaling
// piece-wise representation
// useful for places where transform size/stride is critical (sizeof pose<float> is 32 bytes)
//
// float & double precision currently supported. 32bit fixed point in the future, hopefully.
//
// see the end of the file for ease-of-use typedefs.
// in general, use 'pose' as the type around your code.
//
template <class T>
class t_pose
{
  public:
    t_pose() {}
    t_pose(const t_vec3<T>& inPosition, const t_quat<T>& inRotation, const t_vec3<T>& inScale) : position(inPosition), rotation(inRotation), scale(inScale) {}

    t_vec3<T> position;
    t_quat<T> rotation;
    T scale = 1.0;

    inline t_vec3<T> transformPoint(const t_vec3<T>& point) const;
    inline t_vec3<T> transformVector(const t_vec3<T>& vector) const;
};

template <class T>
inline t_vec3<T> t_pose<T>::transformPoint(const t_vec3<T>& point) const
{
    return t_vec3<T>();
}

template <class T>
inline t_vec3<T> t_pose<T>::transformVector(const t_vec3<T>& vector) const
{
    return t_vec3<T>();
}

typedef t_pose<float> pose_32;
typedef t_pose<double> pose_64;

// 3d transform with uniform scaling
typedef pose_32 pose;

// confirm size restriction
static_assert(sizeof(pose) == 32, "pose<float> should be 32 bytes");
