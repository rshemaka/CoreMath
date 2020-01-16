// Richard Shemaka - 2020
// https://github.com/rshemaka/CoreMath
//
// Sources:
// https://www.mathworks.com/help/robotics/ref/quaternion.rotmat.html

#pragma once
#include "Pose.h"
#include "Transform.h"

// disabling 'loss of precision' warnings as literals will be typed w/ double precision
#pragma warning(push)
#pragma warning(disable : 4244)

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

    inline t_mat4<T>& operator*=(const t_mat4<T>& m);

    // [row][column] format
    T data[4][4];
};

#pragma region Global_Operators
template <class T>
inline t_vec3<T> operator*(const t_mat4<T>& m, const t_vec3<T>& v)
{
    t_vec3<T> out;
    out.x = (m.data[0][0] * v.x) + (m.data[0][1] * v.y) + (m.data[0][2] * v.z) + m.data[0][3];
    out.y = (m.data[1][0] * v.x) + (m.data[1][1] * v.y) + (m.data[1][2] * v.z) + m.data[1][3];
    out.z = (m.data[2][0] * v.x) + (m.data[2][1] * v.y) + (m.data[2][2] * v.z) + m.data[2][3];
    return out;
}
template <class T>
inline t_mat4<T> operator*(const t_mat4<T>& m1, const t_mat4<T>& m2)
{
    t_mat4<T> out;
    for (int row = 0; row != 4; ++row)
    {
        for (int column = 0; column != 4; ++column)
        {
            T& t = out.data[row][column];
            t = static_cast<T>(0.0);
            for (int n = 0; n != 4; ++n)
            {
                t += (m1.data[row][n] * m2.data[n][column]);
            }
        }
    }
    return out;
}
template <class T>
inline std::ostream& operator<<(std::ostream& os, const t_mat4<T>& m)
{
    return os << "\n"
              << m.data[0][0] << ", " << m.data[0][1] << ", " << m.data[0][2] << ", " << m.data[0][3] << "\n"
              << m.data[1][0] << ", " << m.data[1][1] << ", " << m.data[1][2] << ", " << m.data[1][3] << "\n"
              << m.data[2][0] << ", " << m.data[2][1] << ", " << m.data[2][2] << ", " << m.data[2][3] << "\n"
              << m.data[3][0] << ", " << m.data[3][1] << ", " << m.data[3][2] << ", " << m.data[3][3];
}
template <class T>
inline std::wostream& operator<<(std::wostream& os, const t_mat4<T>& m)
{
    return os << "\n"
              << m.data[0][0] << ", " << m.data[0][1] << ", " << m.data[0][2] << ", " << m.data[0][3] << "\n"
              << m.data[1][0] << ", " << m.data[1][1] << ", " << m.data[1][2] << ", " << m.data[1][3] << "\n"
              << m.data[2][0] << ", " << m.data[2][1] << ", " << m.data[2][2] << ", " << m.data[2][3] << "\n"
              << m.data[3][0] << ", " << m.data[3][1] << ", " << m.data[3][2] << ", " << m.data[3][3];
}
#pragma endregion

template <class T>
inline t_mat4<T>::t_mat4()
{
    memset(data, 0.0, sizeof(data));
    data[0][0] = data[1][1] = data[2][2] = data[3][3] = 1.0;
}

template <class T>
inline t_mat4<T>::t_mat4(const t_quat<T>& q) : t_mat4<T>()
{
    // https://www.mathworks.com/help/robotics/ref/quaternion.rotmat.html
    //  a = w  |  b = x  |  c = y  |  d = z

    data[0][0] = (2.0 * q.w * q.w) - 1.0 + (2.0 * q.x * q.x);
    data[0][1] = (2.0 * q.x * q.y) - (2.0 * q.w * q.z);
    data[0][2] = (2.0 * q.x * q.z) + (2.0 * q.w * q.y);

    data[1][0] = (2.0 * q.x * q.y) + (2.0 * q.w * q.z);
    data[1][1] = (2.0 * q.w * q.w) - 1.0 + (2.0 * q.y * q.y);
    data[1][2] = (2.0 * q.y * q.z) - (2.0 * q.w * q.x);

    data[2][0] = (2.0 * q.x * q.z) - (2.0 * q.w * q.y);
    data[2][1] = (2.0 * q.y * q.z) + (2.0 * q.w * q.x);
    data[2][2] = (2.0 * q.w * q.w) - 1.0 + (2.0 * q.z * q.z);
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
inline t_mat4<T>& t_mat4<T>::operator*=(const t_mat4<T>& m)
{
    this = this * m;
}

typedef t_mat4<float> mat4_32;
typedef t_mat4<double> mat4_64;

// 4x4 matrix
typedef mat4_32 mat4;

#pragma warning(pop)
