#ifndef RBT_H
#define RBT_H

#include "RBT_node.h"
#include "Pocket.h"
#include <iomanip>
#include <fstream>
#include <cstring>
#include <vector>


class TRBT{
private:
    TRBT_node* root = nullptr;

protected:
    // 1 -> первый больше второго(дальше по алфавиту)
    // 0 -> первый = второму
    // -1 -> первый меньше второго(раньше в алфавите)
    int Comparator(const std::string& a, const std::string& b);

    TRBT_node* ToLeft(TRBT_node* node);
    TRBT_node* ToRight(TRBT_node* node);
    TRBT_node* BalancingAfterInsert(TRBT_node* node);
    TRBT_node* BalancingAfterDelete(TRBT_node* node);
    TRBT_node* RotateRight(TRBT_node* node);
    TRBT_node* RotateLeft(TRBT_node* node);

public:
    TRBT() = default;
    TRBT(TRBT_node* root_);
    TRBT_node* Insert(TRBT_node* node, TItem& data);
    TRBT_node* Remove(TRBT_node* node);
    TRBT_node* Search(TRBT_node* node, const std::string& key);
    TRBT_node* GetRoot() const;
    void Serialize(TRBT_node* node, std::ofstream &file);
    static TRBT_node* Deserialize(TRBT_node *node, std::ifstream &file);
    void Clear(TRBT_node *node);
    ~TRBT();





};


#endif //RBT_H
