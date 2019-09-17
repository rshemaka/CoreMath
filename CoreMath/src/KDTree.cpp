// written by Richard Shemaka on 7/11/15 in a programming test for Turtle Rock Studios
// rshemaka@gmail.com

#include "KDTree.h"

#include <algorithm>

namespace
{
	// comparisons
	typedef bool(*fCompareFunc)(const Vector* l, const Vector* r);

	bool compareX(const Vector* l, const Vector* r) { return (l->x < r->x); }
	bool compareY(const Vector* l, const Vector* r) { return (l->y < r->y); }
	bool compareZ(const Vector* l, const Vector* r) { return (l->z < r->z); }

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
			return NULL;
		}
	}

	// deltas
	typedef float(*fDeltaFunc)(const Vector* l, const Vector* r);

	float deltaX(const Vector* l, const Vector* r) { return (l->x - r->x); }
	float deltaY(const Vector* l, const Vector* r) { return (l->y - r->y); }
	float deltaZ(const Vector* l, const Vector* r) { return (l->z - r->z); }

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
			return NULL;
		}
	}
}


//
// KDTree
//
KDTree::KDTree(const tPoints& inPoints)
{
	// make a vector of point pointers to handle vector subdivision
	tConstPointRefs pointRefs;
	pointRefs.reserve(inPoints.size());
	for (tPoints::const_iterator it = inPoints.begin(), itEnd = inPoints.end(); it != itEnd; ++it)
	{
		const Vector* pVec = &*it;
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
	pData = NULL;
	pLeftChild = NULL;
	pRightChild = NULL;

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
	int medianIndex = inPoints.size() / 2;
	pData = inPoints[medianIndex];

	// subdivide remaining points
	tConstPointRefs leftPoints = tConstPointRefs(inPoints.begin(), inPoints.begin() + medianIndex);
	tConstPointRefs rightPoints = tConstPointRefs(inPoints.begin() + medianIndex + 1, inPoints.end());

	// recurse
	pLeftChild = leftPoints.empty() ? NULL : new KDTree(leftPoints, depth + 1);
	pRightChild = rightPoints.empty() ? NULL : new KDTree(rightPoints, depth + 1);
}

const Vector* KDTree::findNearestNeighbor(const Vector& inVec)
{
	// uninitialized?
	if (pData == NULL)
		return NULL;

	const Vector* pResult = NULL;
	float minDistanceSqr = FLT_MAX;
	searchNearestNeighbor(inVec, 0, pResult, minDistanceSqr);
	return pResult;
}

void KDTree::searchNearestNeighbor(const Vector& inVec, int depth, const Vector*& pResult, float& flMinDistSqr)
{
	Vector deltaPos = (*pData) - inVec;
	float distanceSqr = deltaPos.magnitudeSqr();

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
			if ( pRightChild )
				pRightChild->searchNearestNeighbor(inVec, depth + 1, pResult, flMinDistSqr);
			break;
		case eRight:
			if ( pLeftChild )
				pLeftChild->searchNearestNeighbor(inVec, depth + 1, pResult, flMinDistSqr);
			break;
		default:
			break;
		}
	}
}