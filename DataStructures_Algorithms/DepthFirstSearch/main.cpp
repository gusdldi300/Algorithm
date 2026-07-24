

#include "DepthFirstSearch.h"
#include "Node.h"
#include <cassert>

int main()
{
    std::vector<Node*> pNodes;
    Node* pStartNode = nullptr;

    // Create node graph
    {
        Node* nodeA = new Node('A');
        Node* nodeB = new Node('B');
        Node* nodeC = new Node('C');
        Node* nodeD = new Node('D');
        Node* nodeE = new Node('E');
        Node* nodeF = new Node('F');
        Node* nodeG = new Node('G');

        nodeA->addNeighbor(nodeE);
        nodeA->addNeighbor(nodeC);

        nodeB->addNeighbor(nodeF);

        nodeC->addNeighbor(nodeA);
        nodeC->addNeighbor(nodeE);
        nodeC->addNeighbor(nodeD);

        nodeD->addNeighbor(nodeC);

        nodeE->addNeighbor(nodeA);
        nodeE->addNeighbor(nodeC);
        nodeE->addNeighbor(nodeF);

        nodeF->addNeighbor(nodeB);
        nodeF->addNeighbor(nodeE);

        pNodes.push_back(nodeA);
        pNodes.push_back(nodeB);
        pNodes.push_back(nodeC);
        pNodes.push_back(nodeD);
        pNodes.push_back(nodeE);
        pNodes.push_back(nodeF);
        pNodes.push_back(nodeG);

        pStartNode = nodeA;
    }

    std::vector<char> preorderTraversedValues;
    DepthFirstSearch::GetPreorderTraversedValues(pNodes, &preorderTraversedValues);
    assert(preorderTraversedValues[0] == 'A');
    assert(preorderTraversedValues[1] == 'C');
    assert(preorderTraversedValues[2] == 'D');
    assert(preorderTraversedValues[3] == 'E');
    assert(preorderTraversedValues[4] == 'F');
    assert(preorderTraversedValues[5] == 'B');
    assert(preorderTraversedValues[6] == 'G');

    std::vector<char> postorderTraversedValues;
    DepthFirstSearch::GetPostorderTraversedValues(pNodes, &postorderTraversedValues);
    assert(postorderTraversedValues[0] == 'D');
    assert(postorderTraversedValues[1] == 'C');
    assert(postorderTraversedValues[2] == 'B');
    assert(postorderTraversedValues[3] == 'F');
    assert(postorderTraversedValues[4] == 'E');
    assert(postorderTraversedValues[5] == 'A');
    assert(postorderTraversedValues[6] == 'G');

    for (Node* deleteNode : pNodes)
    {
        delete deleteNode;
    }

    return 0;
}