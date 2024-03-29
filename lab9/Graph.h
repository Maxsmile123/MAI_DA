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
        unsigned int flow = 0;
        unsigned int flow_capacity = 0;
        Edge() = default;
        Edge(int _from, int _to, int _flow_capacity)
            :
            from(_from), to(_to), flow_capacity(_flow_capacity)
        {};
    };
    struct Node
    {
        std::vector<std::shared_ptr<Edge>> neighbors;
        Node() = default;
    };
    std::vector<Node> nodes; // number of node = index in this vector


    Graph() = default;
    explicit Graph(size_t n)
        : nodes(n + 1)
    {};
    unsigned int Ford_Fulkerson();
    bool BFS(std::shared_ptr<Edge> &edge, size_t n, unsigned int *min_flow);
    bool BFS(std::list<std::shared_ptr<Edge>> *path, size_t start, size_t dest);
    std::list<std::shared_ptr<Edge>> recover_path(const std::shared_ptr<Edge> &edge);

};


#endif //GRAPH_H
