#ifndef KDTREE_HPP
#define KDTREE_HPP

#include "../point.hpp"
#include "../Metrics/metrics.hpp"
#include <memory>
#include <limits>
#include <functional>

class KDTree
{
    struct Node
    {
        Point point;
        std::unique_ptr<Node> left = nullptr;
        std::unique_ptr<Node> right = nullptr;
        explicit Node(Point _p)
            : point(std::move(_p))
        {};
    };
    std::unique_ptr<Node> root = nullptr;
    std::function<double(Point &, Point &)> distance; // Euclidean as default
public:
    explicit KDTree(std::function<double(Point &, Point &)>);
    KDTree()
    {
        distance = Metrics::Euclidean;
    };

    void insert(std::unique_ptr<Node> &, Point &, unsigned int);
    void insert(Point &);
    size_t search_nearest_neighbor(Point &);
    void DFS(std::unique_ptr<Node> &node, Point *cur_nearest_point, unsigned int, Point &request, double *min_dist);

};


#endif //KDTREE_HPP
