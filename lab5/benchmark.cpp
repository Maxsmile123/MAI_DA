#include "suffix_tree.h"
#include "suffix_array.h"
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ifstream fin;
    fin.open("C:\\Users\\Sysoe\\CLionProjects\\MAI_DA\\lab5\\test");
    std::string input_text;
    fin >> input_text;
    TSuffix_array array(input_text);
    input_text.push_back('a' - 1);
    unsigned int count = 0;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    {
        TSuffix_tree tree(input_text);
        array.BuildSiffixArray(tree.get_root());
    }
    while (fin >> input_text) {
        ++count;
        array.Find(input_text, count);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Build ST & SA + Search = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

}

// 1000 - 6 ms
// 10000 - 22 ms
// 100000 - 268 ms
// 1000000 - 1821 ms
// 10000000 - 17600 ms




