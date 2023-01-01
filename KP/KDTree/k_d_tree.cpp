#include "k_d_tree.hpp"

KDTree::KDTree(std::function<double(Point &, Point &)> _metric)
    :
    distance(std::move(_metric))
{}

void KDTree::DFS(std::unique_ptr<Node> &node,
                 Point *cur_nearest_point,
                 unsigned int depth,
                 Point &request,
                 double *min_dist)
{
    if (node == nullptr) {
        return;
    }
    auto dist_to_node = distance(node->point, request);
    if (dist_to_node < *min_dist) {
        *cur_nearest_point = node->point;
        *min_dist = dist_to_node;
    }
    auto cur_dim = depth % node->point.point.size();
    double diff = fabs(node->point.point[cur_dim] - request.point[cur_dim]);
    if (node->point.point[cur_dim] > request.point[cur_dim]) {
        DFS(node->left, cur_nearest_point, depth + 1, request, min_dist);
        if (diff < *min_dist) {
            DFS(node->right, cur_nearest_point, depth + 1, request, min_dist);
        }
    }
    else {
        DFS(node->right, cur_nearest_point, depth + 1, request, min_dist);
        if (diff < *min_dist) {
            DFS(node->left, cur_nearest_point, depth + 1, request, min_dist);
        }
    }

}

void KDTree::insert(std::unique_ptr<Node> &node, Point &request, unsigned int depth)
{
    if (node == nullptr) { // We are in list. Time to insert here
        node = std::make_unique<Node>(request);
        return;
    }
    if (node->point.point.size() != request.point.size()) {
        std::cerr << "Size of first point " << node->point.point.size()
                  << "\nSize of second point " << request.point.size() << std::endl;
        throw KPException(KPException::DIMENSION_ERROR);
    }
    unsigned int cur_d = depth % request.point.size();
    if (request.point[cur_d] < node->point.point[cur_d]) {
        insert(node->left, request, depth + 1);
    }
    else {
        insert(node->right, request, depth + 1);
    }
}

void KDTree::insert(Point &request)
{
    insert(root, request, 0);
}

size_t KDTree::search_nearest_neighbor(Point &request)
{
    double dist = std::numeric_limits<double>::max();
    Point nearest_point;
    DFS(root, &nearest_point, 0, request, &dist);
    return nearest_point.id;
}

