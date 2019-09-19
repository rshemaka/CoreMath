// Richard Shemaka - 2019
// https://github.com/rshemaka/CoreMath

#include "CppUnitTest.h"
#include "stdafx.h"

#include "KDTree.h"
#include "Random.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreMathUnitTest
{
    TEST_CLASS (KDTreeTests)
    {
      public:
        TEST_METHOD (NearestNeighbor)
        {
            // init a point cloud
            constexpr int numPoints = 1000;
            std::vector<vec3> pointCloud(numPoints);
            for (int i = 0; i != numPoints; ++i)
            {
                pointCloud.push_back(vec3(rand01(), rand01(), rand01()));
            }

            // precompute spacial indexing
            KDTree kdTree(pointCloud);

            // generate a query vector
            vec3 queryPoint(rand01(), rand01(), rand01());

            // naive query
            vec3* bestNeighbor = nullptr;
            float smallestDistanceSqr = FLT_MAX;
            for (int i = 0; i != numPoints; ++i)
            {
                vec3& point = pointCloud[i];
                vec3 delta = point - queryPoint;
                float distanceSqr = delta.getLengthSquared();
                if (distanceSqr < smallestDistanceSqr)
                {
                    bestNeighbor = &point;
                    smallestDistanceSqr = distanceSqr;
                }
            }
            const vec3* pNearestNeighbor = bestNeighbor;

            // k-d tree query
            const vec3* pKDNearestNeighbor = kdTree.findNearestNeighbor(queryPoint);

            Assert::IsTrue(pNearestNeighbor == pKDNearestNeighbor);
        }
    };
} // namespace CoreMathUnitTest
