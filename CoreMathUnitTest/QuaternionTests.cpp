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
        TEST_METHOD (RotateVector)
        {
            vec3 v(1.f);
            quat identity;
            v = identity.rotateVector(v);
            Assert::IsTrue(v.isEqual(vec3(1.f)));

            quat a(0.f, 0.f, -45.f);
            v = a.rotateVector(vec3(1.f, 0.f, 0.f));
            vec3 expectedOut(1.f, 1.f, 0.f);
            expectedOut.normalize();

            std::wstringstream outputStream;
            outputStream << "\n"
                         << "Rotated vector: " << v << "\n"
                         << "Expected result: " << expectedOut;

            Assert::IsTrue(v.isEqual(expectedOut), outputStream.str().c_str());
        }
        TEST_METHOD (EulerConversions)
        {
            quat a(10.f, 20.f, 30.f);
            Assert::IsTrue(a.isUnit());
            float roll, pitch, yaw;
            a.getEulerAngles(roll, pitch, yaw);
            Assert::AreEqual(10.f, roll, 0.0001f);
            Assert::AreEqual(20.f, pitch, 0.0001f);
            Assert::AreEqual(30.f, yaw, 0.0001f);
        }
    };
} // namespace CoreMathUnitTest
