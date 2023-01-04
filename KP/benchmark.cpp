#include "KDTree/k_d_tree.hpp"
#include <chrono>
#include <fstream>

std::vector<size_t> bruteforce(std::vector<Point> &data, std::vector<Point> &queries)
{
    std::vector<size_t> res(queries.size());
    size_t i = 0;
    double min = std::numeric_limits<double>::max();
    Point closest_point;
    for (auto &p: queries) {
        for (auto &p_data: data) {
            if (Metrics::Euclidean(p_data, p) < min) {
                min = Metrics::Euclidean(p_data, p);
                closest_point = p_data;
            }
        }
        res[i] = closest_point.id;
        ++i;
        min = std::numeric_limits<double>::max();
        closest_point = Point();
    }
    return res;
}

KDTree kdtree(std::vector<Point> &data)
{
    std::vector<size_t> res;
    KDTree tree(Metrics::Euclidean);
    for (auto &p: data) {
        tree.insert(p);
    }
    return tree;
}

std::vector<size_t> tree_search(KDTree &tree, std::vector<Point> &queries)
{
    std::vector<size_t> res(queries.size());
    size_t i = 0;
    for (auto &q: queries) {
        res[i] = tree.search_nearest_neighbor(q);
        ++i;
    }
    return res;
}

void benchmark()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ifstream fin;
    std::string filename = R"(test_)";
    size_t n, dim, q;
    int temp;
    bool resize = false;
    for (size_t i = 0; i < 16; ++i) {
        if (i < 10) {
            filename.pop_back();
            filename.push_back(i + '0');
        }
        else {
            if (resize) {
                filename.pop_back();
                filename.pop_back();
                filename.push_back((i / 10) + '0');
                filename.push_back((i % 10) + '0');
            }
            else {
                filename.pop_back();
                filename.push_back((i / 10) + '0');
                filename.push_back((i % 10) + '0');
                resize = true;
            }
        }
        fin.open(filename);
        fin >> n >> dim;
        std::vector<Point> data(n);
        for (size_t j = 1; j <= n; ++j) {
            Point point(dim, j);
            for (size_t k = 0; k < dim; ++k) {
                fin >> temp;
                point.point[k] = temp;
            }
            data[j - 1] = point;
        }
        fin >> q;
        std::vector<Point> queries(q);
        Point point(dim, 0);
        for (size_t j = 0; j < q; ++j) {
            for (size_t k = 0; k < dim; ++k) {
                fin >> temp;
                point.point[k] = temp;
            }
            queries[j] = point;
        }
        std::vector<size_t> res1;
        std::vector<size_t> res2;
        std::cout << "Test " << i << ". BF: ";
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        res1 = bruteforce(data, queries);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        std::cout << "Test " << i << ". KDTREE: ";
        begin = std::chrono::steady_clock::now();
        KDTree tree = kdtree(data);
        res2 = tree_search(tree, queries);
        end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        if (res1.size() != res2.size()) {
            throw std::exception();
        }
        for (size_t b = 0; b < res1.size(); ++b) {
            if (res1[b] != res2[b]) {
                std::cout << b << ": res1[b] =" << res1[b] << " res2[b] =" << res2[b] << std::endl;
                throw std::exception();
            }
        }
        fin.close();
    }
}



