#include <iostream>
#include <vector>

int less(std::pair<unsigned int, int> &a1, std::pair<unsigned int, int> &a2,
         std::pair<unsigned int, int> &a3)
{
    auto a4 = std::min(std::min(a1.first, a2.first), a3.first);
    if (a4 == a1.first) return 0;
    if (a4 == a2.first) return 1;
    if (a4 == a3.first) return 2;
}

int less(std::pair<unsigned int, int> &a1, std::pair<unsigned int, int> &a2,
         bool is_three)
{
    auto a4 = std::min(a1.first, a2.first);
    if (a4 == a1.first) return 0;
    if (a4 == a2.first) {
        if (is_three) {
            return 2;
        }
        else {
            return 1;
        }
    }
}

int main()
{
    unsigned int N;
    std::cin >> N;
    std::vector<std::pair<unsigned int, int>> F(N + 1); // first - min sum, second: 0 = -1, 1 = /2, 2 = /3
    F[2] = {2, 1};
    F[3] = {3, 2};
    for (size_t i = 4; i <= N; ++i) {
        if (i % 6 == 0) {
            F[i] = {i + std::min(std::min(F[i - 1].first, F[i / 2].first), F[i / 3].first),
                less(F[i - 1], F[i / 2], F[i / 3])
            };
        }
        else if (i % 3 == 0) {
            F[i] = {i + std::min(F[i - 1].first, F[i / 3].first),
                less(F[i - 1], F[i / 3], true)
            };
        }
        else if (i % 2 == 0) {
            F[i] = {i + std::min(F[i - 1].first, F[i / 2].first),
                less(F[i - 1], F[i / 2], false)
            };
        }
        else {
            F[i] = {i + F[i - 1].first, 0};
        }
    }
    std::cout << F[N].first << std::endl;
    auto cur = N;
    while (cur != 1) {
        if (F[cur].second == 0) {
            std::cout << "-1";
            --cur;
        }
        else if (F[cur].second == 1) {
            std::cout << "/2";
            cur /= 2;
        }
        else {
            std::cout << "/3";
            cur /= 3;
        }
        if (cur != 1) {
            std::cout << " ";
        }
    }


    return 0;

}

