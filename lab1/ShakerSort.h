#ifndef SHAKERSORT_H
#define SHAKERSORT_H

#include <vector>
#include "Element.h"


class TShakerSort
{
public:

    static void swap(TElement *a, TElement *b);
    static std::vector<TElement> sort(std::vector<TElement>& data);

};


#endif //SHAKERSORT_H
