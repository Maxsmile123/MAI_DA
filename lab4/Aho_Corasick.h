#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

#include "Trie.h"
#include <string>
#include <queue>
#include <iostream>

class TAho_Corasick
{
private:
    static bool check(char letter);
    static void link(TTrie *node);
    static TTrie *go(TTrie *node, const std::string &c);
    static void bypass_output_links(TTrie *node, int counter, int string_number);
    static bool sep(char letter);

public:
    static std::string process(const std::string& text);
    static void Add(TTrie* root, const std::string& word, int pattern_number);
    static void Build_Links(TTrie* root);
    static void Search(TTrie* root, const std::string& text, int string_number);
};


#endif //AHO_CORASICK_H
