// Richard Shemaka - 2020
// https://github.com/rshemaka/CoreMath

#pragma once
#include "Quaternion.h"
#include "Vector3.h"

// 3d transform with non-uniform scaling
// piece-wise representation
//
// float & double precision currently supported. 32bit fixed point in the future, hopefully.
//
// see the end of the file for ease-of-use typedefs.
// in general, use 'transform' as the type around your code.
//
template <class T>
class t_transform
{
  public:
    t_transform() {}
    t_transform(const t_vec3<T>& inPosition, const t_quat<T>& inRotation, const t_vec3<T>& inScale) : position(inPosition), rotation(inRotation), scale(inScale) {}

    t_vec3<T> position;
    t_quat<T> rotation;
    t_vec3<T> scale = t_vec3<T>(1.0);

    inline t_vec3<T> transformPoint(const t_vec3<T>& point) const;
    inline t_vec3<T> transformVector(const t_vec3<T>& vector) const;

    inline t_transform<T>& operator*=(const t_transform<T>& t2);
};

template <class T>
inline t_vec3<T> t_transform<T>::transformPoint(const t_vec3<T>& point) const
{
    t_vec3<T> outPoint;
    outPoint = position + point;
    outPoint = rotation.rotateVector(outPoint);
    outPoint *= scale;
    return outPoint;
}

template <class T>
inline t_vec3<T> t_transform<T>::transformVector(const t_vec3<T>& vector) const
{
    t_vec3<T> outVector;
    outVector = rotation.rotateVector(outVector);
    outVector *= scale;
    return outVector;
}

template <class T>
inline t_transform<T>& t_transform<T>::operator*=(const t_transform<T>& t2)
{
    return this;
}

typedef t_transform<float> transform_32;
typedef t_transform<double> transform_64;

// 3d transform with non-uniform scaling
typedef transform_32 transform;
