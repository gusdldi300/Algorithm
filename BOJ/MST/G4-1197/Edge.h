#pragma once

class Edge
{
public:
    Edge(unsigned int firstNode, unsigned int secondNode, int weight);
    unsigned int GetFirstNode() const;
    unsigned int GetSecondNode() const;
    unsigned int GetWeight() const;

    bool operator<(const Edge& other) const;

private:
    unsigned int mFirstNode;
    unsigned int mSecondNode;

    int mWeight;
};