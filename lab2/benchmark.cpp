#include "BST.h"
#include "RBT.h"
#include <chrono>
#include <map>
#include <fstream>


const size_t KEY_VALUE = 256;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    char cmd[KEY_VALUE + 1];
    std::ifstream fin;
    TRBT *rb_tree = new TRBT();
    BST *bst_tree = new BST();
    TItem data;
    std::string KEY;
    std::vector<char> operations;
    std::vector<std::string> keys;

    fin.open("tests");
    while (fin >> cmd) {
        if (!strcmp(cmd, "+")) {
            fin >> data;
            keys.push_back(data.GetKey());
            operations.push_back('+');
        }
        else if (!strcmp(cmd, "-")) {
            fin >> KEY;
            keys.push_back(KEY);
            operations.push_back('-');
        }
        else {
            if (!strcmp(cmd, "?")) {
                fin >> KEY;
            }
            KEY = cmd;
            keys.push_back(KEY);
            operations.push_back('?');
        }
    }
    fin.close();

    if (keys.size() != operations.size()) {
        std::cout << "[-] keys.size() and operations.size() must be equal!\n";
        return -1;
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < keys.size(); ++i) {
        if (operations[i] == '+') {
            TItem data_(keys[i], 0);
            rb_tree->Insert(rb_tree->GetRoot(), data_);
        }

        else if (operations[i] == '-') {
            TRBT_node *need_to_delete = rb_tree->Search(rb_tree->GetRoot(), keys[i]);
            if (need_to_delete) rb_tree->Remove(need_to_delete);
        }
        else if (operations[i] == '?') {
            rb_tree->Search(rb_tree->GetRoot(), keys[i]);
        }

    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference for RB tree = "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    std::map<std::string, unsigned long long> dict;
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < keys.size(); ++i) {
        if (operations[i] == '+') {
            dict[keys[i]] = 1;
        }

        else if (operations[i] == '-') {
            dict.erase(keys[i]);
        }
        else if (operations[i] == '?') {
            dict.find(keys[i]);
        }

    }
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference for std::map = "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < keys.size(); ++i) {
        if (operations[i] == '+') {
            TItem data_(keys[i], 0);
            bst_tree->Insert(data_);
        }

        else if (operations[i] == '-') {
            bst_tree->Remove(keys[i]);
        }
        else if (operations[i] == '?') {
            bst_tree->Search(keys[i]);
        }

    }
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference for BS tree = "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;


//    std::ofstream fout;
//    fout.open("test");
//    std::string key = "+ ";
//    std::vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k','l','m'};
//    for (auto letter: letters) {
//        key = "+ ";
//        for (int i = 0; i < KEY_VALUE; ++i) {
//            key += letter;
//            fout << key << " " << 5 << "\n";
//        }
//    }

    return 0;

}

