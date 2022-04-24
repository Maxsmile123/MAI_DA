#ifndef RBT_H
#define RBT_H

#include "RBT_node.h"
#include "Pocket.h"
#include <fstream>
#include <cstring>
#include <vector>


class TRBT{
private:
    TRBT_node* root = nullptr;

    // 1 -> первый больше второго(дальше по алфавиту)
    // 0 -> первый = второму
    // -1 -> первый меньше второго(раньше в алфавите)
    int comparator(const std::string& a, const std::string& b);

    TRBT_node* toleft(TRBT_node* node);
    TRBT_node* toright(TRBT_node* node);
    TRBT_node* balancingAfterInsert(TRBT_node* node);
    TRBT_node* balancingAfterDelete(TRBT_node* node);
    TRBT_node* rotateright(TRBT_node* node);
    TRBT_node* rotateleft(TRBT_node* node);

public:
    TRBT() = default;
    TRBT(TRBT_node* root_);
    TRBT_node* insert(TRBT_node* node, TItem& data);
    TRBT_node* remove(TRBT_node* node);
    TRBT_node* search(TRBT_node* node, const std::string& key);
    TRBT_node* getroot() const;
    void serialize(TRBT_node* node, std::ofstream &file);
    static TRBT_node* deserialize(TRBT_node *node, std::ifstream &file);
    void clear(TRBT_node *node);
    ~TRBT();





};


#endif //RBT_H
