#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    unsigned int N, p, M;
    std::cin >> N >> p >> M;
    std::vector<std::pair<unsigned int, unsigned int>> coins(N); // first - cost, second - number
    for (size_t i = 0; i < N; ++i) {
        coins[i].first = pow(p, i);
    }
    size_t i = N - 1;
    while (M != 0) {
        coins[i].second = M / coins[i].first;
        M -= coins[i].second * coins[i].first;
        --i;
    }
    for (auto &key: coins) {
        std::cout << key.second << std::endl;
    }
    return 0;
}

