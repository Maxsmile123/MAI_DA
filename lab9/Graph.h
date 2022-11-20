#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>
#include <list>
#include <queue>
#include <climits>


class Graph
{
public:
    struct Edge
    {
        int from = 0;
        int to = 0;
        int flow = 0;
        int flow_capacity = 0;
        Edge() = default;
        Edge(int _from, int _to, int _flow_capacity)
            :
            from(_from), to(_to), flow_capacity(_flow_capacity)
        {};
        Edge(Edge &) = default;
    };
    struct Node
    {
        std::vector<Edge *> neighbors;
        Node() = default;
    };
    std::vector<Node> nodes; // number of node = index in this vector


    Graph() = default;
    Graph(size_t n)
        : nodes(n + 1)
    {};
    int Ford_Fulkerson();
    bool BFS(Edge *edge, size_t n, unsigned int *min_flow);
    std::list<Edge *> recover_path(Edge *edge);

    ~Graph()
    {
        for (auto &node: this->nodes) {
            for (auto &edge: node.neighbors) {
                delete edge;
            }
        }
    };

    bool BFS(std::list<Edge *> *path, size_t start, size_t dest);
};


#endif //GRAPH_H
