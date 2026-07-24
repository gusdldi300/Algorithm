#pragma once

#include <vector>

class Node
{
public:
    Node(char value);
    ~Node();

    const char GetValue() const;
    const std::vector<Node*>& GetNeighbors() const;

    void addNeighbor(Node* pNode);

private:
    char mChar;
    std::vector<Node*> mpNeighbors;
};

