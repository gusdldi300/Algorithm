#include "Node.h"

Node::Node(char value)
    : mChar(value)
{
}

Node::~Node()
{
    mpNeighbors.clear();
}

const char Node::GetValue() const
{
    return mChar;
}

const std::vector<Node*>& Node::GetNeighbors() const
{
    return mpNeighbors;
}

void Node::addNeighbor(Node* node)
{
    mpNeighbors.push_back(node);
}
