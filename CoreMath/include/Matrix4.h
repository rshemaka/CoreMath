// Richard Shemaka - 2020
// https://github.com/rshemaka/CoreMath
//
// Sources:
// https://www.mathworks.com/help/robotics/ref/quaternion.rotmat.html

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
    t_mat4();
    t_mat4(const t_quat<T>& inQuat);
    t_mat4(const t_transform<T>& inTransform);
    t_mat4(const t_pose<T>& inPose);

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
inline t_mat4<T>::t_mat4()
{
    data[0][0] = data[1][1] = data[2][2] = data[3][3] = 1.f;
}

template <class T>
inline t_mat4<T>::t_mat4(const t_quat<T>& q) : t_mat4<T>()
{
    // https://www.mathworks.com/help/robotics/ref/quaternion.rotmat.html
    //  a = w  |  b = x  |  c = y  |  d = z

    data[0][0] = (2.0 * q.w * q.w) - 1 + (2 * q.x * q.x);
    data[0][1] = (2.0 * q.x * q.y) - (2 * q.w * q.z);
    data[0][2] = (2.0 * q.x * q.z) + (2 * q.w * q.y);

    data[1][0] = (2 * q.x * q.y) + (2 * q.w * q.z);
    data[1][1] = (2.0 * q.w * q.w) - 1 + (2 * q.y * q.y);
    data[1][2] = (2.0 * q.y * q.z) - (2 * q.w * q.x);

    data[2][0] = (2.0 * q.x * q.z) - (2 * q.w * q.y);
    data[2][1] = (2.0 * q.y * q.z) + (2 * q.w * q.x);
    data[2][2] = (2.0 * q.w * q.w) - 1 + (2 * q.z * q.z);
}

template <class T>
inline t_mat4<T>::t_mat4(const t_transform<T>& inTransform) : t_mat4<T>(inTransform.rotation)
{
    data[0][3] = inTransform.position.x;
    data[1][3] = inTransform.position.y;
    data[2][3] = inTransform.position.z;

    data[0][0] *= inTransform.scale.x;
    data[1][1] *= inTransform.scale.y;
    data[2][2] *= inTransform.scale.z;
}

template <class T>
inline t_mat4<T>::t_mat4(const t_pose<T>& inPose) : t_mat4<T>(inTransform.rotation)
{
    data[0][3] = inPose.position.x;
    data[1][3] = inPose.position.y;
    data[2][3] = inPose.position.z;

    data[0][0] *= inPose.scale;
    data[1][1] *= inPose.scale;
    data[2][2] *= inPose.scale;
}

template <class T>
inline t_mat4<T>& t_mat4<T>::operator*=(const t_mat4<T>& m2)
{
    // TODO: insert return statement here
}

typedef t_mat4<float> mat4_32;
typedef t_mat4<double> mat4_64;

// 4x4 matrix
typedef mat4_32 mat4;
