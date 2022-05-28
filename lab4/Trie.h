#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <string>


class TTrie{
    std::string letter;
    std::vector<TTrie*> next;
    TTrie* prew = nullptr;
    TTrie* fail_link = nullptr;
    TTrie* output_link = nullptr;
    int is_end = 0; // number of pattern
    int pattern_len = 0;
public:
    friend class TAho_Corasick;
    TTrie(): letter("$"){}
    TTrie(std::string& l,  TTrie* p): letter(l), prew(p){}
    ~TTrie() = default;
};



#endif //TRIE_H
