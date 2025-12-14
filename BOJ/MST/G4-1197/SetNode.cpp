
#include "SetNode.h"

SetNode::SetNode(unsigned int parentNode, int size)
    : mParentNode(parentNode)
    , mSize(size)
{
}

unsigned int SetNode::GetParentNode() const
{
    return mParentNode;
}

unsigned int SetNode::GetSize() const
{
    return mSize;
}

void SetNode::SetParentNode(unsigned int node)
{
    mParentNode = node;
}

void SetNode::SetSize(unsigned int size)
{
    mSize = size;
}
