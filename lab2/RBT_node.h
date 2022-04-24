#ifndef RBT_NODE_H
#define RBT_NODE_H

#include "Item.h"


class TRBT_node {
public:
    TRBT_node* parent;
    TRBT_node* left;
    TRBT_node* right;
    bool color; // false = black, true = red
    TItem data;

    TRBT_node(TRBT_node* parent, TRBT_node* left, TRBT_node* right, bool color, TItem& data);
    TItem getdata() const;



};


#endif //RBT_NODE_H
