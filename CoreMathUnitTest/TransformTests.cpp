// Richard Shemaka - 2020
// https://github.com/rshemaka/CoreMath

#include "CppUnitTest.h"
#include "stdafx.h"

#include "Random.h"
#include "Transform.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreMathUnitTest
{
    TEST_CLASS (TransformTests)
    {
      public:
        TEST_METHOD (TranslatePoint)
        {
            vec3 origin = vec3(0, 0, 0);
            vec3 newOrigin = randomPointInUnitSphere();
            transform shift = transform(newOrigin, quat(), vec3(1));
            origin = shift.transformPoint(origin);
            Assert::IsTrue(origin.isEqual(newOrigin));
        }
        TEST_METHOD (RotatePoint)
        {
            vec3 dir = vec3(1, 0, 0);
            transform shift = transform(vec3(0), quat(0, 0, 180.f), vec3(2));
            dir = shift.transformPoint(dir);
            Assert::IsTrue(dir.isEqual(vec3(-2, 0, 0)));
        }
        TEST_METHOD (TransformVector)
        {
            vec3 dir = vec3(1, 0, 0);
            transform shift = transform(randomPointInUnitSphere(), quat(0, 0, 180.f), vec3(2));
            dir = shift.transformVector(dir);
            Assert::IsTrue(dir.isEqual(vec3(-2, 0, 0)));
        }
    };
} // namespace CoreMathUnitTest
