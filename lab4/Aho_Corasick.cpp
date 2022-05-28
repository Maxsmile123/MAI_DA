#include "Aho_Corasick.h"


bool TAho_Corasick::check(char letter){
    return (letter >= '1' && letter <= '9');
}

std::string TAho_Corasick::process(const std::string& text){
    std::string res;
    bool for_zeroes = false;
    for(int i = 0; i < text.length(); ++i){
        if ((text[i] == '0' && !i) || (text[i] == '0' && text[i - 1] == ' ')){
            for_zeroes = true;
            continue;
        } else if (text[i] == ' ' && i && text[i - 1] == '0' && for_zeroes){
            for_zeroes = false;
            res.push_back(text[i - 1]);
            res.push_back(text[i]);
            continue;
        } else if (text[i] == ' ' && i && (check(text[i - 1]) || text[i - 1] == '0')){
            res.push_back(text[i]);
            continue;
        } else if (check(text[i])){
            for_zeroes = false;
            res.push_back(text[i]);
            continue;
        } else if (text[i] == '0' && !for_zeroes){
            res.push_back(text[i]);
            continue;
        }
    }
    if (text.length() == 1 && text[0] == '0'){
        res.push_back('0');
    }
    return res;
}

void TAho_Corasick::Add(TTrie* root, const std::string& word, int pattern_number){
    TTrie* it = root;
    std::string letter;
    int pat_len = 0;
    bool flag; // показывает, перешли ли мы куда-то
    for(int i = 0; i < word.length(); ++i){
        if (word[i] == ' '){
            letter = "";
            continue;
        } else if (check(word[i]) || word[i] == '0'){
            letter.push_back(word[i]);
            if (word[i + 1] != ' '){
                continue;
            } else{
                ++pat_len;
            }
        }

        flag = false;
        for (auto child: it->next){
            if (child->letter == letter){
                it = child;
                flag = true;
                break;
            }
        }
        if(!flag){
            it->next.push_back(new TTrie(letter, it));
            it = it->next.back();
        }
    }

    it->is_end = pattern_number;
    it->pattern_len = pat_len;
}

void TAho_Corasick::Build_Links(TTrie* root){
    std::queue<TTrie*> queue;
    queue.push(root);
    TTrie* it = root;
    while (!queue.empty()){
        it = queue.front();
        queue.pop();
        link(it);
        for (auto child: it->next){
            queue.push(child);
        }
    }
}

void TAho_Corasick::link(TTrie* node){
    if (!node->prew){
        node->fail_link = node;
    } else if (!node->prew->prew){
        node->fail_link = node->prew;
    }
    else{
        node->fail_link = go(node->prew->fail_link, node->letter);
        if(node->fail_link->is_end){
            node->output_link = node->fail_link;
        } else if (node->fail_link->output_link){
            node->output_link = node->fail_link->output_link;
        }
    }
}

TTrie* TAho_Corasick::go(TTrie* node, std::string& letter){
    for (auto child: node->next){
        if (child->letter == letter){
            return child;
        }
    }
    if(!node->prew) return node;
    return go(node->fail_link, letter);
}

void TAho_Corasick::Search(TTrie* root, const std::string& text, int string_number){
    TTrie* it = root;
    bool stop;
    std::string letter;
    int count_spaces = 1;
    for (int i = 0; i < text.length(); ++i){
        if (text[i] == ' '){
            letter = "";
            continue;
        } else if (check(text[i]) || text[i] == '0'){
            letter.push_back(text[i]);
            if (text[i + 1] != ' '){
                continue;
            } else{
                ++count_spaces;
            }
        }
        stop = true;
        do{
            for(auto child: it->next){
                if (child->letter == letter){
                    it = child;
                    stop = false;
                    if (it->output_link) {
                        //std::cout << "[ol]:";
                        std::cout << string_number << ", " << count_spaces - it->output_link->pattern_len << ", " << it->output_link->is_end << std::endl;
                    }
                    if(it->is_end){
                        //std::cout << "[end]:";
                        std::cout << string_number << ", " << count_spaces - it->pattern_len << ", " << it->is_end << std::endl;
                    }
                    break;
                }
            }
            if (stop){
                if (it == root){
                    break;
                }
                it = it->fail_link;
                if (it->output_link) {
                    std::cout << "[ol]:";
                    std::cout << string_number << ", " << count_spaces - it->output_link->pattern_len << ", " << it->output_link->is_end << std::endl;
                }
                if(it->is_end){
                    std::cout << "[end]:";
                    std::cout << string_number << ", " << count_spaces - it->pattern_len << ", " << it->is_end << std::endl;
                }
            }
        } while (stop);

    }
}