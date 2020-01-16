// Richard Shemaka - 2020
// https://github.com/rshemaka/CoreMath

#include "CppUnitTest.h"
#include "stdafx.h"

#include "Matrix4.h"
#include "Random.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreMathUnitTest
{
    TEST_CLASS (MatrixTests)
    {
      public:
        TEST_METHOD (TransformToMatrix)
        {
            const vec3 point = randomPointInUnitSphere();

            // transform shift = transform(randomPointInUnitSphere(), randomRotation(), randomPointInUnitSphere());
            transform shift = transform(vec3(1.f), quat::getIdentity(), vec3(2.f));
            vec3 pointA = shift.transformPoint(point);

            mat4 mat(shift);
            vec3 pointB = mat * point;
            std::wstringstream outputStream;
            outputStream << "\n"
                         << "PointA: " << pointA << "\n"
                         << "Shift: " << mat << "\n"
                         << "PointB: " << pointB << "\n";

            Assert::IsTrue(pointA.isEqual(pointB), outputStream.str().c_str());
        }
    };
} // namespace CoreMathUnitTest
