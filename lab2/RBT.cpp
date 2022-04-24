#include "RBT.h"


int TRBT::comparator(const std::string& a, const std::string& b){
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

TRBT::TRBT(TRBT_node* root_): root(root_) {};


TRBT_node* TRBT::search(TRBT_node* node, const std::string& key){
    if (node == nullptr) return nullptr;
    int next_way = comparator(key, node->data.getkey());
    if(!next_way) return node;
    else if (next_way == 1){
        return search(node->right, key);
    } else{
        return search(node->left, key);
    }
}

TRBT_node* TRBT::getroot() const {
    return root;
}

TRBT_node* TRBT::insert(TRBT_node* node, TItem& data){
    if (root == nullptr){
        root = new TRBT_node(nullptr, nullptr, nullptr, false, data);
        std::cout << "OK" << std::endl;
        return root;
    }
    int next_way = comparator(data.getkey(), node->getdata().getkey());
    if (!next_way){
        std::cout << "Exist" << std::endl;
        return root;
    } else if (next_way == 1){
        if (node->right == nullptr){
            node->right = new TRBT_node(node, nullptr, nullptr, true, data);
            std::cout << "OK" << std::endl;
            balancingAfterInsert(node->right);
            return root;
        } else{
            insert(node->right, data);
        }
    } else{
        if (node->left == nullptr){
            node->left = new TRBT_node(node, nullptr, nullptr, true, data);
            std::cout << "OK" << std::endl;
            balancingAfterInsert(node->left);
            return root;
        } else{
            insert(node->left, data);
        }
    }
    return root;
}

void TRBT::serialize(TRBT_node* node, std::ofstream &file) {
    if (!node){
        TPocket towrite;
        file << towrite;
    } else{
        TPocket towrite(node->color + '0', node->data.value, node->data.key);
        file << towrite;
        serialize(node->left, file);
        serialize(node->right, file);
    }

}

TRBT_node* TRBT::deserialize(TRBT_node *node, std::ifstream &file){
    TPocket toread;
    TItem data;
    TRBT_node* temp;

    file >> toread;
    if (toread.color != '#'){
        data.key = toread.key;
        data.value = toread.value;
        if (toread.color == '0'){
            node = new TRBT_node(nullptr, nullptr, nullptr, false, data);
        } else{
            node = new TRBT_node(nullptr, nullptr, nullptr, true, data);
        }
        temp = deserialize(node->left, file);
        node->left = temp ;
        if (node->left) node->left->parent = node;
        temp = deserialize(node->right, file);
        node->right = temp;
        if (node->right) node->right->parent = node;
        return node;
    }
    return nullptr;
}

// на вход - верина, которую надо удалить
TRBT_node* TRBT::remove(TRBT_node* node){
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
            replace = toleft(node->right);
            node->data = replace->data;
            return remove(replace);
        } else if (node->left) {
            replace = toright(node->left);
            node->data = replace->data;
            return remove(replace);
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
            balancingAfterDelete(node);
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
            replace = node->right ? toleft(node->right) : toright(node->left);
            node->data = replace->data;
            remove(replace);
        }
    }

    return root;
}

TRBT::~TRBT(){
    this->clear(root);
}

TRBT_node* TRBT::balancingAfterDelete(TRBT_node* node){
    // false - левый сын, true - правый сын
    if (!node->parent) return root;
    TRBT_node* brother = node->parent->right;
    bool side = false;
    if (node->parent->right == node) {
        side = true;
        brother = node->parent->left;
    }
    // Brother is red
    if (brother->color) {
        side ? rotateright(brother) : rotateleft(brother);
        return balancingAfterDelete(node);
    } // Brother is black
    else{
        // У брата два чёрных сына
        if ((!brother->left || !brother->left->color) && (!brother->right || !brother->right->color)){
            brother->color = true;
            return brother->parent->color ? root : balancingAfterDelete(brother->parent);
        }
        if (side){
            if ((!brother->left || !brother->left->color) && brother->right->color){
                rotateleft(brother->right);
                return balancingAfterDelete(node);
            }
            brother->left->color = false;
            return rotateright(brother);

        } else{
            if ((!brother->right || !brother->right->color) && brother->left->color){
                rotateright(brother->left);
                return balancingAfterDelete(node);
            }
            brother->right->color = false;
            return rotateleft(brother);
        }
    }

}

TRBT_node* TRBT::toleft(TRBT_node* node){
    while (node->left){
        toleft(node->left);
    }
    return node;
}

TRBT_node* TRBT::toright(TRBT_node* node){
    while (node->right){
        toleft(node->right);
    }
    return node;
}

TRBT_node* TRBT::balancingAfterInsert(TRBT_node* node){
    if (node == nullptr || !node->parent || !node->parent->color) return root;
    // Ушли в левое поддерево
    if (node->parent->parent->left == node->parent) {
        // first case. Uncle - black
        if (node->parent->parent->right == nullptr || !node->parent->parent->right->color) {
            if (node->parent->right == node) {
                rotateleft(node);
                rotateright(node);
                balancingAfterInsert(node);
            } else{
                rotateright(node->parent);
                balancingAfterInsert(node->parent);
            }
        }
        // second case. Uncle - red
        else if (node->parent->parent->right->color) {
            node->parent->color = false;
            node->parent->parent->right->color = false;
            if (node->parent->parent->parent != nullptr) {
                node->parent->parent->color = true;
            }
        }
    } else {
        if (node->parent->parent->left == nullptr || !node->parent->parent->left->color) {
            if (node->parent->left == node)
            {
                rotateright(node);
                rotateleft(node);
                balancingAfterInsert(node);
            } else{
                rotateleft(node->parent);
                balancingAfterInsert(node->parent);
            }
        }
        else if (node->parent->parent->left->color) {
            node->parent->color = false;
            node->parent->parent->left->color = false;
            if (node->parent->parent->parent != nullptr) {
                node->parent->parent->color = true;
            }
        }
    }
    return root;
}

TRBT_node* TRBT::rotateright(TRBT_node* node){
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

TRBT_node* TRBT::rotateleft(TRBT_node* node)
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

void TRBT::clear(TRBT_node *node){
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}
