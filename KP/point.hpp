#ifndef POINT_HPP
#define POINT_HPP

#include <utility>
#include <vector>
#include <iostream>
#include "utils.hpp"


class Point
{
public:
    std::vector<long double> point; // size = dimension size
    std::size_t id = 0;

    Point(std::size_t dim, std::vector<long double> &_a, std::size_t _id)
        : point(dim), id(_id)
    {
        this->point = _a; // this is valid?
    };
    explicit Point(std::size_t dim, std::size_t _id)
        : point(dim), id(_id)
    {}
    Point() = default;

};

#endif //POINT_HPP
