#include "suffix_tree.h"
#include "suffix_array.h"
#include <string>
#include <iostream>

int main()
{
    std::string input_text;
    std::cin >> input_text;
    TSuffix_array array(input_text);
    input_text.push_back('a' - 1); // сентинел - лексикографически наименьший символ алфавита
    unsigned int count = 0;
    {
        std::shared_ptr<TSuffix_tree> ptr = std::make_shared<TSuffix_tree>(input_text);
        array.BuildSiffixArray(ptr->get_root());
    }
    while (std::cin >> input_text) {
        ++count;
        array.Find(input_text, count);
    }
    return 0;
}
