
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <queue>

class Node
{
public:
	Node(char value);

public:
	char Value;
	Node* LeftNode;
	Node* RightNode;
};

Node::Node(char value)
	: Value(value)
	, LeftNode(nullptr)
	, RightNode(nullptr)
{
}


Node* PlaceNewNodeRecursive(Node* nodeOrNull, char newValue, const std::unordered_map<char, unsigned int>& nodeIndexesMap)
{
	if (nodeOrNull == nullptr)
	{
		return new Node(newValue);
	}

	unsigned int parentNodeIndex = nodeIndexesMap.find(nodeOrNull->Value)->second;
	unsigned int nodeIndex = nodeIndexesMap.find(newValue)->second;

	assert(nodeIndex != parentNodeIndex);

	if (nodeIndex < parentNodeIndex)
	{
		nodeOrNull->LeftNode = PlaceNewNodeRecursive(nodeOrNull->LeftNode, newValue, nodeIndexesMap);
	}
	else
	{
		nodeOrNull->RightNode = PlaceNewNodeRecursive(nodeOrNull->RightNode, newValue, nodeIndexesMap);
	}

	return nodeOrNull;
}

void PrintAndDeleteNodesPostOrderRecursive(Node* nodeOrNull)
{
	if (nodeOrNull == nullptr)
	{
		return;
	}

	PrintAndDeleteNodesPostOrderRecursive(nodeOrNull->LeftNode);
	PrintAndDeleteNodesPostOrderRecursive(nodeOrNull->RightNode);
	std::cout << nodeOrNull->Value;

	delete nodeOrNull;
}

int main()
{
	const unsigned int MAX_NODES_SIZE = 26;

	std::queue<std::string*> nodesQueue;

	while (true)
	{
		std::string newNodes;

		std::cin >> newNodes;
		if (std::cin.eof())
		{
			break;
		}

		assert(newNodes.size() <= MAX_NODES_SIZE);
		
		std::string* newNodesVector = new std::string[2];
		newNodesVector[0] = newNodes;

		std::cin >> newNodes;
		assert(newNodes.size() <= MAX_NODES_SIZE);
		
		newNodesVector[1] = newNodes;

		nodesQueue.push(newNodesVector);
	}

	while (nodesQueue.empty() == false)
	{
		std::string* nodesVector = nodesQueue.front();
		nodesQueue.pop();

		std::string preOrderNodes = nodesVector[0];
		std::string inOrderNodes = nodesVector[1];

		std::unordered_map<char, unsigned int> nodeIndexesMap;
		for (unsigned int i = 0; i < inOrderNodes.size(); ++i)
		{
			nodeIndexesMap.insert(std::pair<char, unsigned int>(inOrderNodes[i], i));
		}

		Node* rootNode = new Node(preOrderNodes[0]);
		for (unsigned int i = 1; i < preOrderNodes.size(); ++i)
		{
			rootNode = PlaceNewNodeRecursive(rootNode, preOrderNodes[i], nodeIndexesMap);
		}

		PrintAndDeleteNodesPostOrderRecursive(rootNode);
		std::cout << std::endl;

		delete[] nodesVector;
	}

	return 0;
}
