
#include <algorithm>

#include "Kruskal.h"
#include "DisjointSet.h"

void Kruskal::GetMST(const std::vector<unsigned int>& nodes, std::vector<Edge>& edges, std::vector<Edge>* outMst)
{
    DisjointSet set(nodes);

    std::sort(edges.begin(), edges.end());

	for (int i = 0; i < edges.size(); ++i) {
		unsigned int firstNode = edges[i].GetFirstNode();
		unsigned int secondNode = edges[i].GetSecondNode();

		unsigned int firstRoot = set.FindRootNodeRercursive(firstNode);
		unsigned int secondRoot = set.FindRootNodeRercursive(secondNode);

		if (firstRoot != secondRoot)
		{
			outMst->push_back(edges[i]);
			set.Union(firstNode, secondNode);
		}
	}
}
