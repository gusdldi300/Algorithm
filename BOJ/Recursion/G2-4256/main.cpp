
#include <cassert>
#include <iostream>
#include <unordered_map>

int sPreOrderedIndex = 0;

void PrintPostOrderedNodesRecursive(int leftIndex, int rightIndex, const unsigned int* preOrderedNodes, const std::unordered_map<unsigned int, int>& inOrderedNodes)
{
	unsigned int currentNode = preOrderedNodes[sPreOrderedIndex];
	std::unordered_map<unsigned int, int>::const_iterator foundNodeIter = inOrderedNodes.find(currentNode);
	if (foundNodeIter == inOrderedNodes.end())
	{
		return;
	}

	if (foundNodeIter->second < leftIndex || foundNodeIter->second > rightIndex)
	{
		return;
	}

	sPreOrderedIndex++;
	PrintPostOrderedNodesRecursive(leftIndex, foundNodeIter->second - 1, preOrderedNodes, inOrderedNodes);
	PrintPostOrderedNodesRecursive(foundNodeIter->second + 1, rightIndex, preOrderedNodes, inOrderedNodes);
	std::cout << currentNode << ' ';
}

int main()
{
	const unsigned int MAX_NODE_COUNT = 1000;

	unsigned int testCount = 0;
	std::cin >> testCount;

	for (unsigned int i = 0; i < testCount; ++i)
	{
		sPreOrderedIndex = 0;

		int nodeCount = 0;
		std::cin >> nodeCount;

		assert(nodeCount >= 1 && nodeCount <= MAX_NODE_COUNT);

		unsigned int preOrderedNodes[MAX_NODE_COUNT] = { 0, };
		for (int nodeIndex = 0; nodeIndex < nodeCount; ++nodeIndex)
		{
			std::cin >> preOrderedNodes[nodeIndex];
		}

		std::unordered_map<unsigned int, int> inOrderedNodes;
		inOrderedNodes.reserve(MAX_NODE_COUNT);
		for (int nodeIndex = 0; nodeIndex < nodeCount; ++nodeIndex)
		{
			unsigned int nodeValue = 0;
			std::cin >> nodeValue;

			inOrderedNodes.insert(std::pair<unsigned int, int>(nodeValue, nodeIndex));
		}

		PrintPostOrderedNodesRecursive(0, nodeCount - 1, preOrderedNodes, inOrderedNodes);

		std::cout << std::endl;
	}

	return 0;
}