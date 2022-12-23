#ifndef POINT_HPP
#define POINT_HPP

#include <vector>
#include <iostream>
#include "utils.hpp"


class Point
{
public:
    std::vector<double> point; // size = dimension size
    std::size_t id;

    Point(std::size_t dim, std::vector<double> &_a, std::size_t _id)
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
