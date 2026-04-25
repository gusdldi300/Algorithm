#include <iostream>
#include <vector>

#define MAX_NODES_COUNT (10001U)
#define MAX_HEIGHT_LEVEL (MAX_NODES_COUNT)

struct BinaryTreeNode
{
    int LeftChild;
    int RightChild;
};

static BinaryTreeNode sBinaryTree[MAX_NODES_COUNT];
static std::vector<unsigned int> sWidthLevels[MAX_HEIGHT_LEVEL];

static unsigned int sMaxHeightLevel;

void SetLevelsRecursive(int node, unsigned int heightLevel, unsigned int& widthLevel)
{
    if (node == -1)
    {
        sMaxHeightLevel = std::max(sMaxHeightLevel, heightLevel - 1);

        return;
    }

    SetLevelsRecursive(sBinaryTree[node].LeftChild, heightLevel + 1, widthLevel);
    sWidthLevels[heightLevel].push_back(widthLevel);
    ++widthLevel;

    SetLevelsRecursive(sBinaryTree[node].RightChild, heightLevel + 1, widthLevel);
}

int main()
{
    unsigned int nodesCount;
    std::cin >> nodesCount;

    bool bChild[MAX_NODES_COUNT] = { false, };

    for (unsigned int i = 0; i < nodesCount; ++i)
    {
        int node;

        std::cin >> node;
        std::cin >> sBinaryTree[node].LeftChild >> sBinaryTree[node].RightChild;

        if (sBinaryTree[node].LeftChild != -1)
        {
            bChild[sBinaryTree[node].LeftChild] = true;
        }

        if (sBinaryTree[node].RightChild != -1)
        {
            bChild[sBinaryTree[node].RightChild] = true;
        }
    }

    int rootNode = 0;
    for (unsigned int node = 1; node <= nodesCount; ++node)
    {
        if (bChild[node] == false)
        {
            rootNode = node;
            break;
        }
    }

    unsigned int widthLevel = 1;
    SetLevelsRecursive(rootNode, 1, widthLevel);

    unsigned int maxWidth = 0;
    unsigned int maxHeight = 1;
    for (unsigned int height = 1; height <= sMaxHeightLevel; ++height)
    {
        unsigned int width = sWidthLevels[height][sWidthLevels[height].size() - 1] - sWidthLevels[height][0] + 1;

        if (width > maxWidth)
        {
            maxWidth = width;
            maxHeight = height;
        }
    }

    std::cout << maxHeight << " " << maxWidth;

    return 0;
}