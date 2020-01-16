// Richard Shemaka - 2020
// https://github.com/rshemaka/CoreMath

#include "CppUnitTest.h"
#include "stdafx.h"

#include "Pose.h"
#include "Random.h"
#include "Transform.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreMathUnitTest
{
    TEST_CLASS (TransformTests)
    {
      public:
        TEST_METHOD (Identity)
        {
            for (int i = 0, n = 128; i != n; ++i)
            {
                vec3 randomPoint = randomPointInUnitSphere();
                const transform& identity = transform::getIdentity();
                vec3 outRandomPoint = identity.transformPoint(randomPoint);

                std::wstringstream outputStream;
                outputStream << "\n"
                             << "randomPoint: " << randomPoint << "\n"
                             << "outRandomPoint: " << outRandomPoint << "\n";
                Assert::IsTrue(randomPoint.isEqual(outRandomPoint), outputStream.str().c_str());
            }
        }
        TEST_METHOD (TranslatePoint)
        {
            for (int i = 0, n = 128; i != n; ++i)
            {
                vec3 origin = vec3(0.f);
                const vec3 newOrigin = randomPointInUnitSphere();
                const transform shift = transform(newOrigin, quat::getIdentity(), vec3(1.f));
                origin = shift.transformPoint(origin);

                std::wstringstream outputStream;
                outputStream << "\n"
                             << "Origin: " << origin << "\n"
                             << "NewOrigin: " << newOrigin << "\n";
                Assert::IsTrue(origin.isEqual(newOrigin), outputStream.str().c_str());
            }
        }
        TEST_METHOD (TransformVector)
        {
            vec3 dir = vec3(1, 0, 0);
            transform shift = transform(vec3(0), quat(0, 0, Pi), vec3(2));
            dir = shift.transformVector(dir);

            std::wstringstream outputStream;
            outputStream << "\n"
                         << "Dir: " << dir << "\n";
            Assert::IsTrue(dir.isEqual(vec3(-2, 0, 0)), outputStream.str().c_str());
        }
    };
} // namespace CoreMathUnitTest
