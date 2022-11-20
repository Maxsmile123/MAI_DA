#include "Graph.h"


unsigned int Graph::Ford_Fulkerson()
{
    unsigned int result_flow = 0;
    Edge min_edge;
    unsigned int min_flow = INT_MAX;
    while (true) {
        min_flow = INT_MAX;
        if (!BFS(&min_edge, nodes.size(), &min_flow)) {
            break;
        }

        std::list<Edge *> path = recover_path(&min_edge);

        for (auto &edge: path) {
            edge->flow += min_flow;
        }
        result_flow += min_flow;
    }
    return result_flow;
}

bool Graph::BFS(Edge *min_edge, size_t n, unsigned int *min_flow)
{
    std::queue<Node> queue;
    queue.push(nodes[1]);
    bool visited[n + 1];
    visited[1] = true;

    while (!queue.empty()) {
        auto v = queue.front();
        queue.pop();
        for (auto edge: v.neighbors) {
            if (!visited[edge->to] && (edge->flow_capacity - edge->flow) > 0) {
                if (*min_flow > (edge->flow_capacity - edge->flow)) {
                    *min_flow = edge->flow_capacity - edge->flow;
                    *min_edge = *edge;
                }
                queue.push(nodes[edge->to]);
                visited[edge->to] = true;
            }
        }

    }
    return visited[n - 1];
}

bool Graph::BFS(std::list<Edge *> *path, size_t start, size_t dest)
{
    if (start == dest) return true;
    std::queue<Node> queue;
    size_t n = nodes.size();
    queue.push(nodes[start]);
    bool visited[n + 1];
    visited[start] = true;

    while (!queue.empty()) {
        auto v = queue.front();
        queue.pop();
        for (auto edge: v.neighbors) {
            if (edge->to == dest) {
                (*path).push_back(edge);
                return true;
            }
            if (!visited[edge->to]) {
                queue.push(nodes[edge->to]);
                visited[edge->to] = true;
            }
        }

    }
    return false;
}

std::list<Graph::Edge *> Graph::recover_path(Graph::Edge *edge)
{
    std::list<Graph::Edge *> path;
    std::list<Graph::Edge *> temp_list;
    size_t start = 1;
    size_t end = this->nodes.size() - 1;
    if (!BFS(&path, start, edge->to)) {
        return {};
    }
    if (!BFS(&temp_list, edge->to, end)) {
        return {};
    }
    path.splice(path.end(), temp_list);

    return path;
}

