#include <iostream>
#include <cstring>
#include "RBT.h"

const size_t KEY_VALUE = 256;


int main()
{
    std::ofstream fout;
    std::ifstream fin;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    TRBT *tree = new TRBT();
    char cmd[KEY_VALUE + 1];
    std::string key;
    TItem data;
    while (std::cin >> cmd) {
        if (!strcmp(cmd, "+")) {
            std::cin >> data;
            tree->insert(tree->getroot(), data);
        }
        else if (!strcmp(cmd, "-")) {
            std::cin >> key;
            TRBT_node *need_to_delete = tree->search(tree->getroot(), key);
            if (need_to_delete == nullptr) {
                std::cout << "NoSuchWord" << std::endl;
            }
            else {
                tree->remove(need_to_delete);
            }
        }
        else if (!strcmp(cmd, "!")) {
            std::cin >> cmd;
            if (!strcmp(cmd, "Save")) {
                std::cin >> cmd;

                fout.open(cmd,  std::ios::out | std::ios::binary | std::ios::trunc);

                tree->serialize(tree->getroot(), fout);
                fout.close();
                std::cout << "OK" << std::endl;
            }
            else if (!strcmp(cmd, "Load")) {
                std::cin >> cmd;
                fin.open(cmd, std::ios::in | std::ios::binary);
                tree->clear(tree->getroot());
                TRBT_node* root = nullptr;
                root = TRBT::deserialize(root, fin);
                tree = new TRBT(root);
                fin.close();
                std::cout << "OK" << std::endl;
            }
        }
        else {
            key = cmd;
            TRBT_node *temp = tree->search(tree->getroot(), key);
            if (temp == nullptr) std::cout << "NoSuchWord" << std::endl;
            else std::cout << "OK: " << temp->data.getvalue() << std::endl;
        }

    }


//
//    unsigned long long a = 18446744073709551615;
//
//    std::cout << a -1;
    return 0;
}