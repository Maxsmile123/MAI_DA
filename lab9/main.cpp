#include <iostream>

#include "Graph.h"


int main()
{
    size_t n, m;
    std::cin >> n >> m;
    Graph graph = Graph(n);
    int from, to, flow;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> from >> to >> flow;
        graph.nodes[from].neighbors.push_back(std::make_shared<Graph::Edge>(from, to, flow));
    }
    std::cout << graph.Ford_Fulkerson();

    return 0;
}

