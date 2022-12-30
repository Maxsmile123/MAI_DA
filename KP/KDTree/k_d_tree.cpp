#include "k_d_tree.hpp"

KDTree::KDTree(std::function<double(Point &, Point &)> _metric)
    :
    distance(std::move(_metric))
{}

void KDTree::DFS(std::unique_ptr<Node> &node, Point *cur_nearest_point, Point &request, double *min_dist)
{
    if (node == nullptr) {
        return;
    }
    double dist_to_left = std::numeric_limits<double>::max();
    double dist_to_right = std::numeric_limits<double>::max();
    if (node->left) {
        dist_to_left = distance(node->left->point, request);
    }
    if (node->right) {
        dist_to_right = distance(node->right->point, request);
    }
    if (dist_to_left < *min_dist) {
        *cur_nearest_point = node->left->point;
        *min_dist = distance(node->left->point, request);
    }
    if (dist_to_right < *min_dist) {
        *cur_nearest_point = node->right->point;
        *min_dist = distance(node->right->point, request);
    }
    if (dist_to_left < dist_to_right) {
        DFS(node->left, cur_nearest_point, request, min_dist);
    }
    else {
        DFS(node->right, cur_nearest_point, request, min_dist);
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
    auto dist = distance(request, root->point);
    Point nearest_point = root->point;
    DFS(root, &nearest_point, request, &dist);
    return nearest_point.id;
}

