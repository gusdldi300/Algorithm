
#include <algorithm>
#include <vector>

#include <iostream>

class Node
{
public:
	Node(int value);

	bool operator<(const Node& other);

public:
	int Value;
	Node* Left;
	Node* Right;
};

Node::Node(int value)
	: Value(value)
	, Left(nullptr)
	, Right(nullptr)
{
}

bool Node::operator<(const Node& other)
{
	return Value < other.Value;
}

void PrintPerfectBinarySearchTreePostOrderRecursive(Node* nodeOrNull)
{
	if (nodeOrNull == nullptr)
	{
		return;
	}

	PrintPerfectBinarySearchTreePostOrderRecursive(nodeOrNull->Left);
	PrintPerfectBinarySearchTreePostOrderRecursive(nodeOrNull->Right);
	std::cout << nodeOrNull->Value << ' ';
}

void PushNodeRecursive(std::vector<Node>& nodeValuesAscend, int parentIndex, int startIndex, int endIndex)
{
	if (startIndex > endIndex)
	{
		return;
	}

	int addIndex = (startIndex + endIndex) / 2;
	if (addIndex < parentIndex)
	{
		nodeValuesAscend[parentIndex].Left = &nodeValuesAscend[addIndex];
	}
	else
	{
		nodeValuesAscend[parentIndex].Right = &nodeValuesAscend[addIndex];
	}

	PushNodeRecursive(nodeValuesAscend, addIndex, startIndex, addIndex - 1);
	PushNodeRecursive(nodeValuesAscend, addIndex, addIndex + 1, endIndex);
}

int main()
{
	unsigned int nodeCount;
	std::cin >> nodeCount;
	
	std::vector<Node> nodes;
	int nodeValue;
	for (unsigned int i = 0; i < nodeCount; ++i)
	{
		std::cin >> nodeValue;
		
		if (nodeValue == -1)
		{
			continue;
		}

		nodes.push_back(Node(nodeValue));
	}
	
	std::cin >> nodeValue;
	nodes.push_back(Node(nodeValue));

	std::sort(nodes.begin(), nodes.end());

	int rootIndex = nodes.size() / 2;
	PushNodeRecursive(nodes, rootIndex, 0, rootIndex - 1);
	PushNodeRecursive(nodes, rootIndex, rootIndex + 1, nodes.size() - 1);

	PrintPerfectBinarySearchTreePostOrderRecursive(&nodes[rootIndex]);

	return 0;
}
