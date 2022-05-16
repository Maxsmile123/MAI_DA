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

    char cmd[KEY_VALUE + 1];
    std::string key;
    TRBT *tree = new TRBT();
    TItem data;
    while (std::cin >> cmd) {
        if (!strcmp(cmd, "+")) {
            std::cin >> data;
            tree->Insert(tree->root, data);
        }
        else if (!strcmp(cmd, "-")) {
            std::cin >> key;
            TRBT_node *need_to_delete = tree->Search(tree->root, key);
            if (need_to_delete == nullptr) {
                std::cout << "NoSuchWord" << std::endl;
            }
            else {
                tree->Remove(need_to_delete);
            }
        }
        else if (!strcmp(cmd, "!")) {
            std::cin >> cmd;
            if (!strcmp(cmd, "Save")) {
                std::cin >> cmd;

                fout.open(cmd,  std::ios::out | std::ios::binary | std::ios::trunc);

                tree->Serialize(tree->root, fout);
                fout.close();
                std::cout << "OK" << std::endl;
            }
            else if (!strcmp(cmd, "Load")) {
                std::cin >> cmd;
                fin.open(cmd, std::ios::in | std::ios::binary);
                TRBT::Clear(tree->root);
                tree->root = TRBT::Deserialize(tree->root, fin);
                fin.close();
                std::cout << "OK" << std::endl;
            }
        }
        else if (!strcmp(cmd, "`")) {
            TRBT::Clear(tree->root);
            delete tree;
            return 0;
        }
        else {
            key = cmd;
            TRBT_node *temp = tree->Search(tree->root, key);
            if (temp == nullptr) std::cout << "NoSuchWord" << std::endl;
            else std::cout << "OK: " << temp->data.GetValue() << std::endl;
        }

    }
    delete tree;
    return 0;
}