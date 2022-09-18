#include "suffix_tree.h"

TSuffix_tree::TSuffix_tree(std::string_view &str)
    : text(str)
{
    BuildSuffixTree();
}

void TSuffix_tree::BuildSuffixTree()
{
    activeNode = root;
    for (size_t i = 0; i < text.length(); ++i) {
        ExtendSuffixTree(i);
    }
}

int TSuffix_tree::EdgeLength(const std::shared_ptr<TNode> &node)
{
    return *(node->end) - (node->start) + 1;
}

void TSuffix_tree::ExtendSuffixTree(int phase)
{
    lastCreatedInternalNode = nullptr;
    leafEnd++;
    remainingSuffixCount++;

    while (remainingSuffixCount > 0) {
        if (activeLength == 0) {
            activeEdge = phase;
        }
        auto find = activeNode->children.find(text[activeEdge]);

        if (find == activeNode->children.end()) {
            activeNode->children.insert(std::make_pair(
                text[activeEdge],
                new TNode(root, phase, &leafEnd, phase - remainingSuffixCount + 1)));

            if (lastCreatedInternalNode != nullptr) {
                lastCreatedInternalNode->suffix_link = activeNode;
                lastCreatedInternalNode = nullptr;
            }
        }
        else {
            std::shared_ptr<TNode> next = find->second;
            int edge_length = EdgeLength(next);
            if (activeLength >= edge_length) {
                activeEdge += edge_length;
                activeLength -= edge_length;
                activeNode = next;
                continue;
            }


            if (text[next->start + activeLength] == text[phase]) {
                if (lastCreatedInternalNode != nullptr && activeNode != root) {
                    lastCreatedInternalNode->suffix_link = activeNode;
                }
                activeLength++;
                break;
            }


            std::shared_ptr<TNode> split = std::make_shared<TNode>
                (root, next->start, new int(next->start + activeLength - 1));

            activeNode->children[text[activeEdge]] = split;
            next->start += activeLength;
            split->children.insert(std::make_pair
                                       (text[phase],
                                        new TNode(root, phase, &leafEnd, phase - remainingSuffixCount + 1)));

            split->children.insert(std::make_pair(text[next->start], next));
            if (lastCreatedInternalNode != nullptr) {
                lastCreatedInternalNode->suffix_link = split;
            }
            lastCreatedInternalNode = split;
        }

        remainingSuffixCount--;

        if (activeNode == root && activeLength > 0) {
            activeLength--;
            activeEdge++;
        }
        else if (activeNode != root)
            activeNode = activeNode->suffix_link;
    }
}

void TSuffix_tree::CountIndex(const std::shared_ptr<TNode> &node, std::vector<int> &vec)
{
    if (!node) {
        return;
    }
    for (const auto &it: node->children) {
        CountIndex(it.second, vec);
    }
    if (node->suffix_index != -1) {
        vec.push_back(node->suffix_index);
    }
}
