#include <algorithm>
#include "suffix_array.h"

void TSuffix_array::Find(const std::string &pattern, unsigned int count)
{
    if (is_first) {
        array.erase(array.begin());
        is_first = false;
    }
    if (pattern.length() > text.length()) return;
    std::pair<size_t, size_t> result_range = {-1, -1};
    std::vector<size_t> answer;
    size_t l, r, m;
    size_t i = 0;
    for (int j = 0; j < 2; ++j) {
        l = 0;
        r = array.size();
        while (l < r) {
            m = (l + r) / 2;
            if (text[array[m] + i - 1] == pattern[i]) {
                ++i;
                if (i == pattern.length()) {
                    if (j) {
                        result_range.second = m;
                        l = m + 1;
                    }
                    else {
                        result_range.first = m;
                        r = m;
                    }
                    i = 0;
                }
            }
            else if (text[array[m] + i - 1] < pattern[i]) {
                l = m + 1;
                i = 0;
            }
            else {
                r = m;
                i = 0;
            }
        }
    }
    if (result_range.first == -1 && result_range.second == -1) return;
    for (auto k = result_range.first; k <= result_range.second; ++k) {
        answer.push_back(array[k]);
    }
    std::sort(answer.begin(), answer.end());
    std::cout << count << ": ";
    for (auto k = 0; k < answer.size(); ++k) {
        std::cout << answer[k];
        if (k != answer.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

}

void TSuffix_array::BuildSiffixArray(const std::shared_ptr<TNode> &node)
{
    if (!node) {
        return;
    }
    for (const auto &it: node->children) {
        BuildSiffixArray(it.second);
    }
    if (node->suffix_index != -1) {
        array.push_back(node->suffix_index + 1);
    }

}
TSuffix_array::TSuffix_array(std::string s)
    : text(std::move(s))
{}

