
#include <iostream>

class Node
{
public:
    Node(unsigned int key);

public:
    unsigned int Key;
    Node* LeftChild;
    Node* RightChild;
};

Node::Node(unsigned int key)
    : Key(key)
    , LeftChild(nullptr)
    , RightChild(nullptr)
{
}

class BinaryTree
{
public:
    BinaryTree(Node* rootNode);
    void AddNode(Node* newNode);
    void PrintAndDeleteTreePostOrdered();

private:
    Node* addNodeRecursive(Node* currentNodeOrNull, Node* newNode);
    void printAndDeleteTreePostOrderedRecursive(Node* currentNodeOrNull);

private:
    Node* mRootNodeOrNull;
};

BinaryTree::BinaryTree(Node* rootNode)
    : mRootNodeOrNull(rootNode)
{
}

void BinaryTree::AddNode(Node* newNode)
{
    mRootNodeOrNull = addNodeRecursive(mRootNodeOrNull, newNode);
}

void BinaryTree::PrintAndDeleteTreePostOrdered()
{
    if (mRootNodeOrNull == nullptr)
    {
        return;
    }

    printAndDeleteTreePostOrderedRecursive(mRootNodeOrNull);
}

Node* BinaryTree::addNodeRecursive(Node* currentNodeOrNull, Node* newNode)
{
    if (currentNodeOrNull == nullptr)
    {
        return newNode;
    }

    if (newNode->Key < currentNodeOrNull->Key)
    {
        currentNodeOrNull->LeftChild = addNodeRecursive(currentNodeOrNull->LeftChild, newNode);
    }
    else
    {
        currentNodeOrNull->RightChild = addNodeRecursive(currentNodeOrNull->RightChild, newNode);
    }

    return currentNodeOrNull;
}

void BinaryTree::printAndDeleteTreePostOrderedRecursive(Node* currentNodeOrNull)
{
    if (currentNodeOrNull == nullptr)
    {
        return;
    }

    printAndDeleteTreePostOrderedRecursive(currentNodeOrNull->LeftChild);
    printAndDeleteTreePostOrderedRecursive(currentNodeOrNull->RightChild);
    std::cout << currentNodeOrNull->Key << std::endl;
    delete currentNodeOrNull;
}

int main()
{
    unsigned int newKey = 0;
    std::cin >> newKey;
    if (std::cin.eof())
    {
        return 0;
    }

    Node* rootNode = new Node(newKey);
    BinaryTree binaryTree(rootNode);
    while (true)
    {
        std::cin >> newKey;
        if (std::cin.eof())
        {
            break;
        }

        Node* newNode = new Node(newKey);
        binaryTree.AddNode(newNode);
    }

    binaryTree.PrintAndDeleteTreePostOrdered();
    
    return 0;
}
