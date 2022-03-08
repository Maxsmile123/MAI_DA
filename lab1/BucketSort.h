#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include <vector>
#include "Element.h"
#include "ShakerSort.h"



class TBucketSort
{
public:
    static std::vector<TElement> sort(const std::vector<TElement>& data, const double inf, const double sup, const int numBuckets);

};


#endif //BUCKETSORT_H
