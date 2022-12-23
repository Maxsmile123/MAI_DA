#ifndef METRICS_HPP
#define METRICS_HPP

#include <cmath>
#include "point.hpp"

class Metrics
{
public:
    static double Euclidean(Point &a, Point &b)
    {
        if (a.point.size() != b.point.size()) {
            std::cerr << "Size of first point " << a.point.size()
                      << "\nSize of second point " << b.point.size() << std::endl;
            throw KPException(KPException::DIMENSION_ERROR);
        }
        double sum = 0;
        for (size_t i = 0; i < a.point.size(); ++i) {
            sum += pow((a.point[i] - b.point[i]), 2);
        }
        return sqrt(sum);
    };

    static double Manhattan(Point &a, Point &b)
    {
        if (a.point.size() != b.point.size()) {
            std::cerr << "Size of first point " << a.point.size()
                      << "\nSize of second point " << b.point.size() << std::endl;
            throw KPException(KPException::DIMENSION_ERROR);
        }
        double sum = 0;
        for (size_t i = 0; i < a.point.size(); ++i) {
            sum += std::abs(a.point[i] - b.point[i]);
        }
        return sum;
    };
};


#endif //METRICS_HPP
