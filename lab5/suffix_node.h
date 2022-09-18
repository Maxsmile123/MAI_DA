#ifndef SUFFIX_NODE_H
#define SUFFIX_NODE_H

#include <cstddef>
#include <memory>
#include <utility>
#include <map>

#define TERMINATION_SYMBOL '$'


class TNode
{
public:
    friend class TSuffix_tree;

    TNode(std::shared_ptr<TNode> link, int start, int *end)
        : TNode(std::move(link), start, end, -1)
    {}
    TNode(std::shared_ptr<TNode> link, int start, int *end, int ind)
        :
        suffix_link(std::move(link)),
        start(start),
        end(end),
        suffix_index(ind)
    {}

private:
    std::map<char, std::shared_ptr<TNode>> children;
    std::shared_ptr<TNode> suffix_link;
    int start;                  // номер первого символа вершины в тексте
    int *end;                   // номер последнего символа вершины в тексте
    int suffix_index;

};

#endif
