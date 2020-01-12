// Richard Shemaka - 2020
// https://github.com/rshemaka/CoreMath

#include "CppUnitTest.h"
#include "stdafx.h"

#include "KDTree.h"
#include "Random.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreMathUnitTest
{
    TEST_CLASS (KDTreeTests)
    {
      public:
        TEST_METHOD (NearestNeighbor)
        {
            // init a point cloud
            constexpr int numPoints = 256;
            std::vector<vec3> pointCloud;
            pointCloud.reserve(numPoints);
            for (int i = 0; i != numPoints; ++i)
            {
                pointCloud.push_back(vec3(rand01(), rand01(), rand01()));
            }

            // precompute spacial indexing
            KDTree kdTree(pointCloud);

            // run this test a number of rounds
            constexpr int testRounds = 256;
            for (int i = 0; i != testRounds; ++i)
            {
                // generate a query vector
                vec3 queryPoint(rand01(), rand01(), rand01());

                // naive query
                vec3* pNearestNeighbor = nullptr;
                float smallestDistanceSqr = FLT_MAX;
                for (int i = 0; i != numPoints; ++i)
                {
                    vec3& point = pointCloud.at(i);
                    vec3 delta = point - queryPoint;
                    float distanceSqr = delta.getLengthSquared();
                    if (distanceSqr < smallestDistanceSqr)
                    {
                        pNearestNeighbor = &point;
                        smallestDistanceSqr = distanceSqr;
                    }
                }

                // k-d tree query
                const vec3* pKDNearestNeighbor = kdTree.findNearestNeighbor(queryPoint);

                std::wstringstream outputStream;
                outputStream << "\n"
                             << "Query: " << queryPoint << "\n"
                             << "Nearest neighbor: " << *pNearestNeighbor << "\n"
                             << "K-D Tree Result: " << *pKDNearestNeighbor;

                Assert::IsTrue(pNearestNeighbor == pKDNearestNeighbor, outputStream.str().c_str());
            }
        }
    };
} // namespace CoreMathUnitTest
