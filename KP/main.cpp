#include "k_d_tree.hpp"

int main()
{
    size_t n, dim, q;
    double temp;
    std::cin >> n >> dim;
    KDTree tree;
    if (dim <= 200) {
        tree = KDTree(Metrics::Euclidean);
    }
    else {
        tree = KDTree(Metrics::Manhattan);
    }
    for (size_t i = 1; i <= n; ++i) {
        Point point(dim, i);
        for (size_t j = 0; j < dim; ++j) {
            std::cin >> temp;
            point.point[j] = temp;
        }
        tree.insert(point);
    }
    std::cin >> q;
    Point point(dim, 0);
    for (size_t i = 0; i < q; ++i) {
        for (size_t j = 0; j < dim; ++j) {
            std::cin >> temp;
            point.point[j] = temp;
        }
        std::cout << tree.search_nearest_neighbor(point) << std::endl;
    }

    return 0;
}