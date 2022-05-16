#include "RBT.h"


int TRBT::Comparator(const std::string& a, const std::string& b){
    unsigned int min_len = std::min(a.length(), b.length());
    for(int i = 0; i < min_len; ++i){
        if (std::tolower(a[i]) > std::tolower(b[i])){
            return 1;
        } else if (std::tolower(a[i]) < std::tolower(b[i])){
            return -1;
        }
    }
    if (a.length() > b.length()){
        return 1;
    } else if (a.length() < b.length()){
        return -1;
    } else return 0;
}



TRBT_node* TRBT::Search(TRBT_node* node, const std::string& key){
    if (node == nullptr) return nullptr;
    int next_way = Comparator(key, node->data.GetKey());
    if(!next_way) return node;
    else if (next_way == 1){
        return Search(node->right, key);
    } else{
        return Search(node->left, key);
    }
}



TRBT_node* TRBT::Insert(TRBT_node* node, TItem& data){
    if (root == nullptr){
        root = new TRBT_node(nullptr, nullptr, nullptr, false, data);
        std::cout << "OK" << std::endl;
        return root;
    }
    int next_way = Comparator(data.GetKey(), node->GetData().GetKey());
    if (!next_way){
        std::cout << "Exist" << std::endl;
        return root;
    } else if (next_way == 1){
        if (node->right == nullptr){
            node->right = new TRBT_node(node, nullptr, nullptr, true, data);
            std::cout << "OK" << std::endl;
            BalancingAfterInsert(node->right);
            return root;
        } else{
            Insert(node->right, data);
        }
    } else{
        if (node->left == nullptr){
            node->left = new TRBT_node(node, nullptr, nullptr, true, data);
            std::cout << "OK" << std::endl;
            BalancingAfterInsert(node->left);
            return root;
        } else{
            Insert(node->left, data);
        }
    }
    return root;
}

void TRBT::Serialize(TRBT_node* node, std::ofstream &file) {
    if (!node){
        TPocket towrite;
        file << towrite;
    } else{
        TPocket towrite(node->color + '0', node->data.value, node->data.key);
        file << towrite;
        Serialize(node->left, file);
        Serialize(node->right, file);
    }

}

TRBT_node* TRBT::Deserialize(TRBT_node *node, std::ifstream &file){
    TPocket toread;
    TItem data;

    file >> toread;
    if (toread.color != '#'){
        data.key = toread.key;
        data.value = toread.value;
        if (toread.color == '0'){
            node = new TRBT_node(nullptr, nullptr, nullptr, false, data);
        } else{
            node = new TRBT_node(nullptr, nullptr, nullptr, true, data);
        }
        node->left = Deserialize(node->left, file);
        if (node->left) node->left->parent = node;
        node->right = Deserialize(node->right, file);
        if (node->right) node->right->parent = node;
        return node;
    }
    return nullptr;
}

/// на вход - вершина, которую надо удалить
TRBT_node* TRBT::Remove(TRBT_node* node){
    if (!node->parent && !node->left && !node->right){ // if just once root
        delete node;
        std::cout << "OK" << std::endl;
        this->root = nullptr;
        return root;
    }
    TRBT_node *replace;
    if (node->color){
        if (!node->right && !node->left) { // Если у нас красный лист
            if (node->parent) {
                if (node->parent->left == node) {
                    node->parent->left = nullptr;
                }
                else {
                    node->parent->right = nullptr;
                }
            }
            delete node;
            std::cout << "OK" << std::endl;
            return root;
        } else if (node->right) {
            replace = ToLeft(node->right);
            node->data = replace->data;
            return Remove(replace);
        } else if (node->left) {
            replace = ToRight(node->left);
            node->data = replace->data;
            return Remove(replace);
        }
    } else{
        // Если левый сын - красный, а правого нет
        if (node->left && node->left->color && !node->right){
            if (node->parent) {
                if (node->parent->left == node) {
                    node->parent->left = node->left;
                }
                else {
                    node->parent->right = node->left;
                }
            }else{
                root = node->left;
            }
            node->left->color = false;
            node->left->parent = node->parent;
            delete node;
            std::cout << "OK" << std::endl;
            return root;
            // Если правый сын - красный, а левого нет
        } else if (node->right && node->right->color && !node->left){
            if (node->parent) {
                if (node->parent->left == node) {
                    node->parent->left = node->right;
                }
                else {
                    node->parent->right = node->right;
                }

            } else{
                root = node->right;
            }
            node->right->color = false;
            node->right->parent = node->parent;
            delete node;
            std::cout << "OK" << std::endl;
            return root;
        } // Если чёрный лист
        else if (!node->right && !node->left){
            BalancingAfterDelete(node);
            if (node->parent) {
                if (node->parent->left == node) {
                    node->parent->left = nullptr;
                }
                else {
                    node->parent->right = nullptr;
                }
            }
            delete node;
            std::cout << "OK" << std::endl;
            return root;
        }else{
            // Если просто чёрный элемент
            replace = node->right ? ToLeft(node->right) : ToRight(node->left);
            node->data = replace->data;
            Remove(replace);
        }
    }

    return root;
}


TRBT_node* TRBT::BalancingAfterDelete(TRBT_node* node){
    // false - левый сын, true - правый сын
    if (!node->parent) return root;
    TRBT_node* brother = node->parent->right;
    bool side = false;
    if (node->parent->right == node) {
        side = true;
        brother = node->parent->left;
    }
    // Brother is red
    if (brother == nullptr) return BalancingAfterDelete(node->parent);
    if (brother->color) {
        side ? RotateRight(brother) : RotateLeft(brother);
        return BalancingAfterDelete(node);
    } // Brother is black
    else{
        // У брата два чёрных сына
        if ((!brother->left || !brother->left->color) && (!brother->right || !brother->right->color)){
            brother->color = true;
            if (brother->parent->color){
                brother->parent->color = false;
                return root;
            } else{
                return BalancingAfterDelete(brother->parent);
            }

        }
        if (side){
            if ((!brother->left || !brother->left->color) && brother->right->color){
                RotateLeft(brother->right);
                return BalancingAfterDelete(node);
            }
            brother->left->color = false;
            return RotateRight(brother);

        } else{
            if ((!brother->right || !brother->right->color) && brother->left->color){
                RotateRight(brother->left);
                return BalancingAfterDelete(node);
            }
            brother->right->color = false;
            return RotateLeft(brother);
        }
    }

}

TRBT_node* TRBT::ToLeft(TRBT_node* node){
    if (node->left){
        return ToLeft(node->left);
    }
    return node;
}

TRBT_node* TRBT::ToRight(TRBT_node* node){
    if (node->right){
        return ToLeft(node->right);
    }
    return node;
}

TRBT_node* TRBT::BalancingAfterInsert(TRBT_node* node)
{
    if (!node->parent || !node->parent->color) return root;
    // Ушли в левое поддерево
    if (node->parent->parent->left == node->parent) {
        // first case. Uncle - black
        if (node->parent->parent->right == nullptr || !node->parent->parent->right->color) {
            if (node->parent->right == node) {
                RotateLeft(node);
                RotateRight(node);
                return root;
            } else{
                RotateRight(node->parent);
                return root;
            }
        }
            // second case. Uncle - red
        else if (node->parent->parent->right->color) {
            node->parent->color = false;
            node->parent->parent->right->color = false;
            if (node->parent->parent->parent != nullptr) {
                node->parent->parent->color = true;
            }
            if(node->parent->parent->parent && node->parent->parent->parent->color){
                return BalancingAfterInsert(node->parent->parent);
            }
        }
    } else {
        if (node->parent->parent->left == nullptr || !node->parent->parent->left->color) {
            if (node->parent->left == node)
            {
                RotateRight(node);
                RotateLeft(node);
                return root;
            } else{
                RotateLeft(node->parent);
                return root;
            }
        }
        else if (node->parent->parent->left->color) {
            node->parent->color = false;
            node->parent->parent->left->color = false;
            if (node->parent->parent->parent != nullptr) {
                node->parent->parent->color = true;
            }
            if(node->parent->parent->parent && node->parent->parent->parent->color){
                return BalancingAfterInsert(node->parent->parent);
            }
        }
    }
    return root;
}

TRBT_node* TRBT::RotateRight(TRBT_node* node){
    TRBT_node* gp = node->parent;
    TRBT_node* p = node;
    bool p_color = p->color;
    p->color = gp->color;
    gp->color = p_color;
    gp->left = p->right;
    if (p->right)  p->right->parent = gp;
    p->right = gp;
    p->parent = gp->parent;
    if (gp->parent && gp->parent->left == gp) {
        gp->parent->left = p;
    } else if (gp->parent){
        gp->parent->right = p;
    }
    gp->parent = p;
    if (p->parent == nullptr) root = p;
    return root;
}

TRBT_node* TRBT::RotateLeft(TRBT_node* node)
{
    TRBT_node* gp = node->parent;
    TRBT_node* p = node;
    bool p_color = p->color;
    p->color = gp->color;
    gp->color = p_color;
    gp->right = p->left;
    if (p->left)  p->left->parent = gp;
    p->left = gp;
    p->parent = gp->parent;
    if (gp->parent && gp->parent->left == gp) {
        gp->parent->left = p;
    } else if (gp->parent){
        gp->parent->right = p;
    }
    gp->parent = p;
    if (p->parent == nullptr) root = p;
    return root;

}

void TRBT::Clear(TRBT_node *node){
    if (!node) return;
    Clear(node->left);
    Clear(node->right);
    delete node;
}

