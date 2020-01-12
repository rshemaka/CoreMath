// Richard Shemaka - 2020
// https://github.com/rshemaka/CoreMath

#pragma once
#include "Pose.h"
#include "Transform.h"

// 4x4 matrix
//
// float & double precision currently supported. 32bit fixed point in the future, hopefully.
//
// see the end of the file for ease-of-use typedefs.
// in general, use 'mat4' as the type around your code.
//
template <class T>
class t_mat4
{
  public:
    t_mat4() {}
    t_mat4(t_transform<T> inTransform);
    t_mat4(t_pose<T> inPose);

    T& getElement(int row, int column)
    {
        return data[row][column];
    }
    const T& getElement(int row, int column) const
    {
        return data[row][column];
    }

    inline t_mat4<T>& operator*=(const t_mat4<T>& m2);

  private:
    T data[4][4];
};

template <class T>
inline t_mat4<T>::t_mat4(t_transform<T> inTransform)
{}

template <class T>
inline t_mat4<T>::t_mat4(t_pose<T> inPose)
{}

template <class T>
inline t_mat4<T>& t_mat4<T>::operator*=(const t_mat4<T>& m2)
{
    // TODO: insert return statement here
}

typedef t_mat4<float> mat4_32;
typedef t_mat4<double> mat4_64;

// 4x4 matrix
typedef mat4_32 mat4;
