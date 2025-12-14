
#include "Edge.h"

Edge::Edge(unsigned int firstNode, unsigned int secondNode, int weight)
    : mFirstNode(firstNode)
    , mSecondNode(secondNode)
    , mWeight(weight)
{
}

unsigned int Edge::GetFirstNode() const
{
    return mFirstNode;
}

unsigned int Edge::GetSecondNode() const
{
    return mSecondNode;
}

unsigned int Edge::GetWeight() const
{
    return mWeight;
}

bool Edge::operator<(const Edge& other) const
{
    return mWeight < other.mWeight;
}
