#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> ZFunc(const std::string &string)
{
    unsigned int string_size = string.length();
    std::vector<int> z(string_size);
    z[0] = string_size;
    int l, r = 0;
    for (int i = 1; i < string_size; ++i) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while ((i + z[i] < string_size) && (string[z[i]] == string[i + z[i]])) {
            ++z[i];
        }
        if (r < i + z[i] - 1) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main()
{
    std::string pattern;
    std::cin >> pattern;
    std::string text;
    std::cin >> text;
    std::string s = pattern + "$" + text;
    std::vector<int> Z = ZFunc(s);
    for (unsigned int i = pattern.size() + 1; i < Z.size(); ++i) {
        if (Z[i] == pattern.size()) {
            std::cout << i - (pattern.size() + 1) << "\n";
        }
    }
    return 0;
}