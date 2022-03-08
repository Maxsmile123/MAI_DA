#include "BucketSort.h"

std::vector<TElement> TBucketSort::sort(const std::vector<TElement>& data, const double inf, const double sup, const int numBuckets){
    std::vector<TElement> answer;
    double minElement = sup;
    double maxElement = inf;
    std::vector<std::vector<TElement>> buckets(numBuckets);
    for (auto i : data) {
        minElement = std::min(minElement, i.key);
        maxElement = std::max(maxElement, i.key);
    }

    double range = (maxElement - minElement + 1) / numBuckets;
    for (auto i : data) {
        int index = int((i.key - minElement) / range);
        if (index == numBuckets){
            index--;
        }
        buckets[index].push_back(i);
    }
    for (int i = 0; i < numBuckets; ++i){
        buckets[i] = TShakerSort::sort(buckets[i]);
    }
    for (int i = 0; i < numBuckets; ++i) {
        for(auto k : buckets[i]){
            answer.push_back(k);
        }
    }

    return answer;
}