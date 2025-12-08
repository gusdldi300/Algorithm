
#include <algorithm>
#include <iostream>
#include <cassert>
#include <climits>
#include <stack>
#include <vector>
#include <queue>

struct Vertex
{
    int x;
    int y;
};

struct Line
{
    Vertex StartVertex;
    Vertex EndVertex;
};

struct Peak
{
    Vertex LeftVertex;
    Vertex RightVertex;
};

bool CompareByVertexX(const Peak& peak, const Peak& other)
{
    return peak.LeftVertex.x < other.LeftVertex.x;
}

int main()
{
    unsigned int vertexCount = 0;
    std::cin >> vertexCount;
    assert(vertexCount >= 4);

    Vertex startVertex = { INT_MAX, INT_MAX };
    unsigned int startVertexIndex = 0;

    std::queue<Vertex> vertexQueue;
    for (unsigned int vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex)
    {
        Vertex vertex;
        std::cin >> vertex.x >> vertex.y;

        vertexQueue.push(vertex);

        if (vertex.x == startVertex.x)
        {
            if (vertex.y < startVertex.y)
            {
                startVertex = vertex;
                startVertexIndex = vertexIndex;
            }
        }
        else if (vertex.x < startVertex.x)
        {
            startVertex = vertex;
            startVertexIndex = vertexIndex;
        }
    }

    for (unsigned int i = 0; i < startVertexIndex; ++i)
    {
        Vertex vertex = vertexQueue.front();
        vertexQueue.pop();

        vertexQueue.push(vertex);
    }

    std::vector<Peak> PeaksleftMostAligned;
    std::stack<Line> lineStack;

    Vertex lastVertex = vertexQueue.front();
    vertexQueue.pop();

    unsigned int vertexIndex = 1;
    while (vertexQueue.empty() == false)
    {
        Vertex vertex = vertexQueue.front();
        vertexQueue.pop();

        if (vertexIndex % 2 != 0)
        {
            if ((lastVertex.y < 0 && vertex.y > 0) || lastVertex.y > 0 && vertex.y < 0)
            {
                if (lineStack.empty() == false)
                {
                    Line endLine = lineStack.top();
                    lineStack.pop();

                    if (vertex.x < endLine.StartVertex.x)
                    {
                        PeaksleftMostAligned.push_back({ vertex, endLine.StartVertex });
                    }
                    else
                    {
                        PeaksleftMostAligned.push_back({ endLine.StartVertex, vertex });
                    }
                }
                else
                {
                    lineStack.push({ lastVertex, vertex });
                }
            }
        }

        lastVertex = vertex;
        ++vertexIndex;
    }
    
    if (PeaksleftMostAligned.size() == 0)
    {
        std::cout << 0 << " " << 0;

        return 0;
    } 

    std::sort(PeaksleftMostAligned.begin(), PeaksleftMostAligned.end(), CompareByVertexX);

    unsigned int nonSubPeakCount = 0;
    unsigned int outerPeakCount = 1;

    const Peak* pOuterPeak = &PeaksleftMostAligned[0];
    const Peak* pLastPeak = pOuterPeak;
    
    for (unsigned int i = 1; i < PeaksleftMostAligned.size(); ++i)
    {
        const Peak* pPeak = &PeaksleftMostAligned[i];
        
        if (pLastPeak->RightVertex.x < pPeak->LeftVertex.x)
        {
            ++nonSubPeakCount;
        }

        if (pOuterPeak->RightVertex.x < pPeak->LeftVertex.x)
        {
            ++outerPeakCount;

            pOuterPeak = pPeak;
        }

        pLastPeak = pPeak;
    }

    ++nonSubPeakCount;

    std::cout << outerPeakCount << " " << nonSubPeakCount;

    return 0;
}

