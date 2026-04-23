
#include <iostream>

#define MAX_NODES_COUNT (27U)

struct Node
{
    char Value;

    Node* pLeftChildOrNull;
    Node* pRightChildOrNull;
};

inline static unsigned int NodeValueToNodesIndex(char nodeValue)
{
    return static_cast<unsigned int>(nodeValue - 'A');
}

static void PrintNodesPreOrder(Node* pNodeOrNull, Node nodes[])
{
    if (pNodeOrNull == nullptr)
    {
        return;
    }

    std::cout << pNodeOrNull->Value;
    PrintNodesPreOrder(pNodeOrNull->pLeftChildOrNull, nodes);
    PrintNodesPreOrder(pNodeOrNull->pRightChildOrNull, nodes);
}

static void PrintNodesInOrder(Node* pNodeOrNull, Node nodes[])
{
    if (pNodeOrNull == nullptr)
    {
        return;
    }

    PrintNodesInOrder(pNodeOrNull->pLeftChildOrNull, nodes);
    std::cout << pNodeOrNull->Value;
    PrintNodesInOrder(pNodeOrNull->pRightChildOrNull, nodes);
}

static void PrintNodesPostOrder(Node* pNodeOrNull, Node nodes[])
{
    if (pNodeOrNull == nullptr)
    {
        return;
    }

    PrintNodesPostOrder(pNodeOrNull->pLeftChildOrNull, nodes);
    PrintNodesPostOrder(pNodeOrNull->pRightChildOrNull, nodes);
    std::cout << pNodeOrNull->Value;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    Node nodes[MAX_NODES_COUNT];
 
    unsigned int nodesCount;
    std::cin >> nodesCount;

    for (unsigned int i = 0; i < nodesCount; ++i)
    {
        nodes[i].Value = 'A' + static_cast<char>(i);

        char nodeValue;
        char leftChildNodeValue;
        char rightChildNodeValue;

        std::cin >> nodeValue >> leftChildNodeValue >> rightChildNodeValue;
        
        unsigned int nodeIndex = NodeValueToNodesIndex(nodeValue);

        if (leftChildNodeValue == '.')
        {
            nodes[nodeIndex].pLeftChildOrNull = nullptr;
        }
        else
        {
            nodes[nodeIndex].pLeftChildOrNull = &nodes[NodeValueToNodesIndex(leftChildNodeValue)];
        }
        
        if (rightChildNodeValue == '.')
        {
            nodes[nodeIndex].pRightChildOrNull = nullptr;
        }
        else
        {
            nodes[nodeIndex].pRightChildOrNull = &nodes[NodeValueToNodesIndex(rightChildNodeValue)];
        }
    }

    PrintNodesPreOrder(&nodes[0], nodes);
    std::cout << '\n';

    PrintNodesInOrder(&nodes[0], nodes);
    std::cout << '\n';

    PrintNodesPostOrder(&nodes[0], nodes);

    return 0;
}