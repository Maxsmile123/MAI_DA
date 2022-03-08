#include <iostream>
#include <vector>
#include <iomanip>
#include "BucketSort.h"

const double infinum = -100.0;
const double supremum = 100.0;

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::vector<TElement> inputData;
    TElement temp;
    while(std::cin >> temp){
        inputData.push_back(temp);
    }
    inputData = TBucketSort::sort(inputData, infinum, supremum, inputData.size());
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(6);
    for(auto values: inputData){
        std::cout << values;
    }
    return 0;
}