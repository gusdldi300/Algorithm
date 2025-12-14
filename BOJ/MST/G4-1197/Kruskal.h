#pragma once

#include <vector>

#include "Edge.h"

class Kruskal
{
public:
    static void GetMST(const std::vector<unsigned int>& nodes, std::vector<Edge>& edges, std::vector<Edge>* outMst);
private:
    Kruskal() = delete;
};