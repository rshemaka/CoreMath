// Richard Shemaka - 2019
// https://github.com/rshemaka/CoreMath

#include "KDTree.h"
#include <algorithm>

namespace
{
    // comparisons
    typedef bool (*fCompareFunc)(const vec3* l, const vec3* r);

    bool compareX(const vec3* l, const vec3* r)
    {
        return (l->x < r->x);
    }
    bool compareY(const vec3* l, const vec3* r)
    {
        return (l->y < r->y);
    }
    bool compareZ(const vec3* l, const vec3* r)
    {
        return (l->z < r->z);
    }

    fCompareFunc getAxisComparison(int depth)
    {
        switch (depth % 3)
        {
        case 0:
            return compareX;
        case 1:
            return compareY;
        case 2:
            return compareZ;
        default:
            return nullptr;
        }
    }

    // deltas
    typedef float (*fDeltaFunc)(const vec3* l, const vec3* r);

    float deltaX(const vec3* l, const vec3* r)
    {
        return (l->x - r->x);
    }
    float deltaY(const vec3* l, const vec3* r)
    {
        return (l->y - r->y);
    }
    float deltaZ(const vec3* l, const vec3* r)
    {
        return (l->z - r->z);
    }

    fDeltaFunc getAxisDelta(int depth)
    {
        switch (depth % 3)
        {
        case 0:
            return deltaX;
        case 1:
            return deltaY;
        case 2:
            return deltaZ;
        default:
            return nullptr;
        }
    }
} // namespace

// KDTree
KDTree::KDTree(const std::vector<vec3>& inPoints)
{
    // make a vector of point pointers to handle vec3 subdivision
    tConstPointRefs pointRefs;
    pointRefs.reserve(inPoints.size());
    for (std::vector<vec3>::const_iterator it = inPoints.begin(), itEnd = inPoints.end(); it != itEnd; ++it)
    {
        const vec3* pVec = &*it;
        pointRefs.push_back(pVec);
    }
    // internal constructor
    init(pointRefs, 0);
}

KDTree::KDTree(tConstPointRefs& inPoints, int depth)
{
    init(inPoints, depth);
}

KDTree::~KDTree()
{
    if (pLeftChild)
        delete pLeftChild;
    if (pRightChild)
        delete pRightChild;
}

void KDTree::init(tConstPointRefs& inPoints, int depth)
{
    pData = nullptr;
    pLeftChild = nullptr;
    pRightChild = nullptr;

    if (inPoints.size() == 1)
    {
        pData = inPoints[0];
        return;
    }

    // select sort function
    fCompareFunc compare = getAxisComparison(depth);

    // sort input
    std::sort(inPoints.begin(), inPoints.end(), compare);

    // extract median
    uint32_t medianIndex = static_cast<uint32_t>(inPoints.size()) / 2;
    pData = inPoints[medianIndex];

    // subdivide remaining points
    tConstPointRefs leftPoints = tConstPointRefs(inPoints.begin(), inPoints.begin() + medianIndex);
    tConstPointRefs rightPoints = tConstPointRefs(inPoints.begin() + medianIndex + 1, inPoints.end());

    // recurse
    pLeftChild = leftPoints.empty() ? nullptr : new KDTree(leftPoints, depth + 1);
    pRightChild = rightPoints.empty() ? nullptr : new KDTree(rightPoints, depth + 1);
}

const vec3* KDTree::findNearestNeighbor(const vec3& inVec)
{
    // uninitialized?
    if (pData == nullptr)
        return nullptr;

    const vec3* pResult = nullptr;
    float minDistanceSqr = FLT_MAX;
    searchNearestNeighbor(inVec, 0, pResult, minDistanceSqr);
    return pResult;
}

void KDTree::searchNearestNeighbor(const vec3& inVec, int depth, const vec3*& pResult, float& flMinDistSqr)
{
    vec3 deltaPos = (*pData) - inVec;
    float distanceSqr = deltaPos.getLengthSquared();

    if (distanceSqr < flMinDistSqr)
    {
        // new winner!
        flMinDistSqr = distanceSqr;
        pResult = pData;
    }

    // get relevant functions
    fCompareFunc compare = getAxisComparison(depth);
    fDeltaFunc delta = getAxisDelta(depth);

    // pick a direction and recurse
    enum eAction
    {
        eNone = 0,
        eLeft,
        eRight
    };
    eAction action = eNone;
    if (compare(&inVec, pData))
    {
        if (pLeftChild)
            pLeftChild->searchNearestNeighbor(inVec, depth + 1, pResult, flMinDistSqr);
        action = eLeft;
    }
    else
    {
        if (pRightChild)
            pRightChild->searchNearestNeighbor(inVec, depth + 1, pResult, flMinDistSqr);
        action = eRight;
    }

    // candidate hypersphere (awesome name) crossing the separation plane?
    float distToSeperation = fabs(delta(pData, &inVec));
    float distToSeperationsSqr = distToSeperation * distToSeperation;
    if (distToSeperationsSqr < flMinDistSqr)
    {
        switch (action)
        {
        case eLeft:
            if (pRightChild)
                pRightChild->searchNearestNeighbor(inVec, depth + 1, pResult, flMinDistSqr);
            break;
        case eRight:
            if (pLeftChild)
                pLeftChild->searchNearestNeighbor(inVec, depth + 1, pResult, flMinDistSqr);
            break;
        default:
            break;
        }
    }
}