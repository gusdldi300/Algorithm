#pragma once

class SetNode
{
public:
    SetNode(unsigned int parentNode, int size);
    unsigned int GetParentNode() const;
    unsigned int GetSize() const;
    
    void SetParentNode(unsigned int node);
    void SetSize(unsigned int size);

private:
    unsigned int mParentNode;
    unsigned int mSize;
};