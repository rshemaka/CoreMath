// Richard Shemaka - 2019
// https://github.com/rshemaka/CoreMath

#include "CppUnitTest.h"
#include "stdafx.h"

#include "PoissonDiskNoise.h"
#include "Quaternion.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreMathUnitTest
{
    TEST_CLASS (QuaternionTests)
    {
      public:
        TEST_METHOD (EulerConversions)
        {
            quat a = quat::makeFromEuler(10.f, 20.f, 30.f);
            float roll, pitch, yaw;
            a.getEulerAngles(roll, pitch, yaw);
            Assert::AreEqual(10.f, roll, 0.0001f);
            Assert::AreEqual(20.f, pitch, 0.0001f);
            Assert::AreEqual(30.f, yaw, 0.0001f);
        }
    };
} // namespace CoreMathUnitTest
