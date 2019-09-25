// Richard Shemaka - 2019
// https://github.com/rshemaka/CoreMath

#include "CppUnitTest.h"
#include "stdafx.h"

#include "Vector2.h"
#include "Vector3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreMathUnitTest
{
    TEST_CLASS (Vector2Tests)
    {
      public:
        TEST_METHOD (Size)
        {
            vec2 xVec(1.f, 0.f);
            Assert::AreEqual(xVec.getLength(), 1.f);

            vec2 yVec(0.f, 2.f);
            Assert::AreEqual(yVec.getLength(), 2.f);
        }

        TEST_METHOD (Normalize)
        {
            vec2 vecA(5.f, 2.f);
            vecA.normalize();
            Assert::IsTrue(MathHelpers::isNearlyEqual(vecA.getLength(), 1.f));
        }

        TEST_METHOD (GetUnit)
        {
            vec2 vecA(5.f, 2.f);
            vec2 vecAUnit = vecA.getUnit();
            Assert::IsTrue(MathHelpers::isNearlyEqual(vecAUnit.getLength(), 1.f));

            vecA.normalize();
            Assert::IsTrue(vecAUnit.isEqual(vecA));
        }

        TEST_METHOD (IsUnit)
        {
            vec2 vecA(5.f, 2.f);
            vec2 vecAUnit = vecA.getUnit();
            Assert::IsTrue(!vecA.isUnit());
            Assert::IsTrue(vecAUnit.isUnit());

            vecA.normalize();
            Assert::IsTrue(vecA.isUnit());
        }

        TEST_METHOD (Equality)
        {
            vec2 vecA(5.f, 2.f);
            vec2 vecB(5.f, 2.f);
            Assert::IsTrue(vecA.isEqual(vecB));

            vecA += vec2(1.f, 0.f);
            Assert::IsTrue(!vecA.isEqual(vecB));
        }

        TEST_METHOD (Addition)
        {
            vec2 vecA(2.f, 3.f);
            vec2 vecB(3.f, 2.f);
            vec2 vecC = vecA + vecB;
            Assert::IsTrue(vecC.isEqual(vec2(5.f)));

            vecA += vecB;
            Assert::IsTrue(vecA.isEqual(vecC));
        }

        TEST_METHOD (Subtraction)
        {
            vec2 vecA(5.f, 4.f);
            vec2 vecB(2.f, 1.f);
            vec2 vecC = vecA - vecB;
            Assert::IsTrue(vecC.isEqual(vec2(3.f)));

            vecA -= vecB;
            Assert::IsTrue(vecA.isEqual(vecC));
        }

        TEST_METHOD (StreamOutput)
        {
            vec2 vec(1.f, 1.f);
            std::ostringstream outputStream;
            outputStream << vec;
            std::string outputString = outputStream.str();
            Assert::IsTrue(outputString.size() > 0);

            std::wstringstream wideOutputStream;
            wideOutputStream << vec;
            std::wstring wideOutputString = wideOutputStream.str();
            Assert::IsTrue(wideOutputString.size() > 0);
        }
    };

    TEST_CLASS (Vector3Tests)
    {
      public:
        TEST_METHOD (Size)
        {
            vec3 xVec(1.f, 0.f, 0.f);
            Assert::AreEqual(xVec.getLength(), 1.f);

            vec3 yVec(0.f, 2.f, 0.f);
            Assert::AreEqual(yVec.getLength(), 2.f);

            vec3 zVec(0.f, 0.f, 3.f);
            Assert::AreEqual(zVec.getLength(), 3.f);
        }

        TEST_METHOD (Normalize)
        {
            vec3 vecA(5.f, 2.f, 1.f);
            vecA.normalize();
            Assert::IsTrue(MathHelpers::isNearlyEqual(vecA.getLength(), 1.f));
        }

        TEST_METHOD (GetUnit)
        {
            vec3 vecA(5.f, 2.f, 1.f);
            vec3 vecAUnit = vecA.getUnit();
            Assert::IsTrue(MathHelpers::isNearlyEqual(vecAUnit.getLength(), 1.f));

            vecA.normalize();
            Assert::IsTrue(vecAUnit.isEqual(vecA));
        }

        TEST_METHOD (IsUnit)
        {
            vec3 vecA(5.f, 2.f, 1.f);
            vec3 vecAUnit = vecA.getUnit();
            Assert::IsTrue(!vecA.isUnit());
            Assert::IsTrue(vecAUnit.isUnit());

            vecA.normalize();
            Assert::IsTrue(vecA.isUnit());
        }

        TEST_METHOD (Equality)
        {
            vec3 vecA(5.f, 2.f, 1.f);
            vec3 vecB(5.f, 2.f, 1.f);
            Assert::IsTrue(vecA.isEqual(vecB));

            vecA += vec3(1.f, 0.f, 0.f);
            Assert::IsTrue(!vecA.isEqual(vecB));
        }

        TEST_METHOD (Addition)
        {
            vec3 vecA(2.f, 3.f, 4.f);
            vec3 vecB(3.f, 2.f, 1.f);
            vec3 vecC = vecA + vecB;
            Assert::IsTrue(vecC.isEqual(vec3(5.f)));

            vecA += vecB;
            Assert::IsTrue(vecA.isEqual(vecC));
        }

        TEST_METHOD (Subtraction)
        {
            vec3 vecA(5.f, 4.f, 3.f);
            vec3 vecB(2.f, 1.f, 0.f);
            vec3 vecC = vecA - vecB;
            Assert::IsTrue(vecC.isEqual(vec3(3.f)));

            vecA -= vecB;
            Assert::IsTrue(vecA.isEqual(vecC));
        }

        TEST_METHOD (StreamOutput)
        {
            vec3 vec(1.f, 1.f, 1.f);
            std::ostringstream outputStream;
            outputStream << vec;
            std::string outputString = outputStream.str();
            Assert::IsTrue(outputString.size() > 0);

            std::wstringstream wideOutputStream;
            wideOutputStream << vec;
            std::wstring wideOutputString = wideOutputStream.str();
            Assert::IsTrue(wideOutputString.size() > 0);
        }
    };
} // namespace CoreMathUnitTest
