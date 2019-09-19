// Richard Shemaka - 2019
// https://github.com/rshemaka/CoreMath

#pragma once
#include "Vector3.h"
#include <vector>

// k-d tree of 3D points
// nearest neighbor search: O(log n)
// maintains pointers to the contents of an input std::vector<vec3>
//
// Source:
// http://web.stanford.edu/class/cs106l/handouts/assignment-3-kdtree.pdf
// https://en.wikipedia.org/wiki/K-d_tree
//
class KDTree
{
  public:
    KDTree(const std::vector<vec3>& inPoints);
    virtual ~KDTree();

    const vec3* findNearestNeighbor(const vec3& inVec);

  protected:
    typedef std::vector<const vec3*> tConstPointRefs;

    // protected recursive constructor
    KDTree(tConstPointRefs& inPoints, int depth);
    void init(tConstPointRefs& inPoints, int depth);

    // tree node structure
    const vec3* pData;
    KDTree* pLeftChild;
    KDTree* pRightChild;

    // internal recursive function
    void searchNearestNeighbor(const vec3& inVec, int depth, const vec3*& pResult, float& flMinDistSqr);
};