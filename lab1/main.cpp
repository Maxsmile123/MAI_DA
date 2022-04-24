#include <iomanip>
#include <chrono>
#include "BucketSort.h"

const double infinum = -100.0;
const double supremum = 100.0;

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(nullptr);
    std::vector<TElement> inputData;
    TElement temp;
    while(std::cin >> temp){
        inputData.push_back(temp);
    }
    auto start = std::chrono::steady_clock::now();
    inputData = TBucketSort::sort(inputData, infinum, supremum, inputData.size());
    auto finish = std::chrono::steady_clock::now();
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(6);
    for(auto values: inputData){
        std::cout << values;
    }
    auto dur = finish - start;
    std::cerr << "input " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms" << std::endl;
    return 0;
}