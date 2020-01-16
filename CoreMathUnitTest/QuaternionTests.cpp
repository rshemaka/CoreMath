// Richard Shemaka - 2020
// https://github.com/rshemaka/CoreMath

#include "CppUnitTest.h"
#include "stdafx.h"

#include "MathHelpers.h"
#include "Quaternion.h"
#include "Random.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreMathUnitTest
{
    TEST_CLASS (QuaternionTests)
    {
      public:
        TEST_METHOD (Identity)
        {
            for (int i = 0, n = 128; i != n; ++i)
            {
                const vec3 randomPoint = randomPointInUnitSphere();
                const quat& identity = quat::getIdentity();
                const vec3 outRandomPoint = identity.rotateVector(randomPoint);

                std::wstringstream outputStream;
                outputStream << "\n"
                             << "randomPoint: " << randomPoint << "\n"
                             << "outRandomPoint: " << outRandomPoint << "\n";
                Assert::IsTrue(randomPoint.isEqual(outRandomPoint), outputStream.str().c_str());
            }
        }
        TEST_METHOD (RotateVector)
        {
            for (int i = 0, n = 128; i != n; ++i)
            {
                const vec3 point = randomPointInUnitSphere();
                const float angleShift = randRange(FLT_EPSILON, TwoPi);
                quat rotation = quat(angleShift, 0.f, 0.f);
                const vec3 outPoint = rotation.rotateVector(point);

                std::wstringstream outputStream;
                outputStream << "\n"
                             << "point: " << point << "\n"
                             << "outPoint: " << outPoint << "\n";

                Assert::AreEqual(point.getLengthSquared(), outPoint.getLengthSquared(), outputStream.str().c_str());
                Assert::AreEqual(point.angle(outPoint), angleShift, outputStream.str().c_str());
            }
        }
        TEST_METHOD (EulerConversions)
        {
            auto isEqualOrOffByPi = [](float a, float b) { return MathHelpers::isNearlyEqual(a, b) || MathHelpers::isNearlyEqual(std::fabsf(a - b), Pi); };

            for (int i = 0, n = 128; i != n; ++i)
            {
                const float inRoll = randRange(0.f, TwoPi / 3.f);
                const float inPitch = randRange(0.f, TwoPi / 3.f);
                const float inYaw = randRange(0.f, TwoPi / 3.f);
                quat a(inRoll, inPitch, inYaw);
                Assert::IsTrue(a.isUnit());
                float outRoll, outPitch, outYaw;
                a.getEulerAngles(outRoll, outPitch, outYaw);

                std::wstringstream outputStream;
                outputStream << "\n"
                             << "iteration #: " << i << "\n";
                Assert::AreEqual(inRoll, outRoll, 0.00001f, outputStream.str().c_str());
                Assert::AreEqual(inPitch, outPitch, 0.00001f, outputStream.str().c_str());
                Assert::AreEqual(inYaw, outYaw, 0.00001f, outputStream.str().c_str());
                // Assert::IsTrue(isEqualOrOffByPi(inRoll, outRoll));
                // Assert::IsTrue(isEqualOrOffByPi(inPitch, outPitch));
                // Assert::IsTrue(isEqualOrOffByPi(inYaw, outYaw));
            }
        }
    };
} // namespace CoreMathUnitTest
