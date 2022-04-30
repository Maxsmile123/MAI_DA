#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include "Item.h"


class BSTNode
{
public:
    TItem Key;
    BSTNode * Left;
    BSTNode * Right;
    BSTNode * Parent;
    int Height;
};

class BST
{
private:
    BSTNode * root;

protected:
    BSTNode * Insert(BSTNode * node, TItem key);
    BSTNode * Search(BSTNode * node, std::string& key);
    std::string& FindMin(BSTNode * node);
    std::string& FindMax(BSTNode * node);
    std::string& Successor(BSTNode * node);
    std::string& Predecessor(BSTNode * node);
    BSTNode * Remove(BSTNode * node, std::string& v);
    int comparator(const std::string& a, const std::string& b);

public:
    BST() = default;

    void Insert(TItem key);
    bool Search(std::string& key);
    std::string& FindMin();
    std::string& FindMax();
    std::string& Successor(std::string& key);
    std::string& Predecessor(std::string& key);
    void Remove(std::string& v);
};

int BST::comparator(const std::string& a, const std::string& b){
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

BSTNode * BST::Insert(BSTNode * node, TItem key)
{

    if(node == NULL)
    {
        node = new BSTNode;
        node->Key = key;
        node->Left = NULL;
        node->Right = NULL;
        node->Parent = NULL;
        return node;
    }
    int next_way = comparator(node->Key.key, key.key);
    if(next_way == 1)
    {
        node->Right = Insert(node->Right, key);
        node->Right->Parent = node;
    } else if (next_way == -1)
    {
        node->Left = Insert(node->Left, key);
        node->Left->Parent = node;
    } else{
        return node;
    }

}

void BST::Insert(TItem key)
{
    root = Insert(root, key);
}



BSTNode * BST::Search(BSTNode * node, std::string& key)
{
    if (node == NULL)
        return NULL;
    int next_way = comparator(node->Key.key, key);
    if(!next_way)
        return node;
    else if(next_way == 1)
        return Search(node->Right, key);
    else
        return Search(node->Left, key);
}

bool BST::Search(std::string& key)
{
    BSTNode * result = Search(root, key);
    if (result == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

std::string& BST::FindMin(BSTNode * node)
{
    if (node) {
        if (node->Left == NULL)
            return node->Key.key;
        else
            return FindMin(node->Left);
    }
}

std::string& BST::FindMin()
{
    return FindMin(root);
}

std::string& BST::FindMax(BSTNode * node)
{
    if (node) {
        if (node->Right == NULL)
            return node->Key.key;
        else
            return FindMax(node->Right);
    }
}

std::string& BST::FindMax()
{
    return FindMax(root);
}

std::string& BST::Successor(BSTNode * node)
{

    if (node->Right != NULL)
    {
        return FindMin(node->Right);
    }
    else
    {
        BSTNode * parentNode = node->Parent;
        BSTNode * currentNode = node;

        while ((parentNode != NULL) &&
            (currentNode == parentNode->Right))
        {
            currentNode = parentNode;
            parentNode = currentNode->Parent;
        }
        if (parentNode != nullptr){
            return parentNode->Key.key;
        }
    }
}

std::string& BST::Successor(std::string& key)
{
    BSTNode * keyNode = Search(root, key);

    if (keyNode != nullptr){
        return Successor(keyNode);
    }
}

std::string& BST::Predecessor(BSTNode * node)
{
    if (node->Left != NULL)
    {
        return FindMax(node->Left);
    }
    else
    {
        BSTNode * parentNode = node->Parent;
        BSTNode * currentNode = node;

        while ((parentNode != NULL) &&
            (currentNode == parentNode->Left))
        {
            currentNode = parentNode;
            parentNode = currentNode->Parent;
        }
        if (parentNode != nullptr){
            return parentNode->Key.key;
        }
    }
}

std::string& BST::Predecessor(std::string& key)
{
    BSTNode * keyNode = Search(root, key);
    if (keyNode != nullptr){
        return Successor(keyNode);
    }
}

BSTNode * BST::Remove(BSTNode * node, std::string& key)
{
    if (node == NULL)
        return NULL;

    int next_way = comparator(node->Key.key, key);
    if (!next_way)
    {
        if (node->Left == NULL && node->Right == NULL)
            node = NULL;
        else if (node->Left == NULL && node->Right != NULL)
        {
            node->Right->Parent = node->Parent;
            node = node->Right;
        }
        else if (node->Left != NULL && node->Right == NULL)
        {
            node->Left->Parent = node->Parent;
            node = node->Left;
        }
        else
        {
            std::string successorKey = Successor(key);
            node->Key.key = successorKey;
            node->Right = Remove(node->Right, successorKey);
        }
    }
    else if (next_way == 1)
        node->Right = Remove(node->Right, key);
    else
        node->Left = Remove(node->Left, key);
    return node;
}

void BST::Remove(std::string& key)
{
    root = Remove(root, key);
}

#endif //RBT_H