#include "RBT_node.h"


TItem TRBT_node::getdata() const {
    return data;
}

TRBT_node::TRBT_node(TRBT_node* p, TRBT_node* l, TRBT_node* r, bool c, TItem& d):
parent(p), left(l), right(r), color(c), data(d){}

