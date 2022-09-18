#include <vector>
#include <string>
#include <queue>
#include <iostream>

class TTrie
{
    std::string letter;
    std::vector<TTrie *> next;
    TTrie *prew = nullptr;
    TTrie *fail_link = nullptr;
    TTrie *output_link = nullptr;
    int is_end = 0; // number of pattern
    int pattern_len = 0;
public:
    friend class TAho_Corasick;
    TTrie()
        : letter("$")
    {}
    TTrie(std::string &l, TTrie *p)
        : letter(l), prew(p)
    {}
    ~TTrie() = default;
};

class TAho_Corasick
{
private:
    static bool check(char letter);
    static void link(TTrie *node);
    static TTrie *go(TTrie *node, std::string &c);
    static void bypass_output_links(TTrie *node, int counter, int string_number);
    static bool sep(char letter);

public:
    static std::string process(const std::string &text);
    static void Add(TTrie *root, const std::string &word, int pattern_number);
    static void Build_Links(TTrie *root);
    static void Search(TTrie *root, const std::string &text, int string_number);
};

bool TAho_Corasick::check(char letter)
{
    return (letter >= '1' && letter <= '9');
}

bool TAho_Corasick::sep(char letter)
{
    return (letter == ' ' || letter == '\t');
}

std::string TAho_Corasick::process(const std::string &text)
{
    std::string res;
    bool for_zeroes = false;
    for (int i = 0; i < text.length(); ++i) {
        if ((text[i] == '0' && !i) || (text[i] == '0' && sep(text[i - 1]))) {
            for_zeroes = true;
            continue;
        }
        else if (sep(text[i]) && i && text[i - 1] == '0' && for_zeroes) {
            for_zeroes = false;
            res.push_back(text[i - 1]);
            res.push_back(text[i]);
            continue;
        }
        else if (sep(text[i]) && i && (check(text[i - 1]) || text[i - 1] == '0')) {
            res.push_back(text[i]);
            continue;
        }
        else if (check(text[i])) {
            for_zeroes = false;
            res.push_back(text[i]);
            continue;
        }
        else if (text[i] == '0' && !for_zeroes) {
            res.push_back(text[i]);
            continue;
        }
    }
    return res;
}
// Принимает на вход нормализованную строку!
void TAho_Corasick::Add(TTrie *root, const std::string &word, int pattern_number)
{
    TTrie *it = root;
    std::string letter;
    int pat_len = 0;
    bool flag; // показывает, перешли ли мы куда-то
    for (int i = 0; i < word.length(); ++i) {
        if (sep(word[i])) {
            letter = "";
            continue;
        }
        else if (check(word[i]) || word[i] == '0') {
            letter.push_back(word[i]);
            if (!sep(word[i + 1])) {
                continue;
            }
            else {
                ++pat_len;
            }
        }
        flag = false;
        for (TTrie *child: it->next) {
            if (child->letter == letter) {
                it = child;
                flag = true;
                break;
            }
        }
        if (!flag) {
            it->next.push_back(new TTrie(letter, it));
            it = it->next.back();
        }
    }

    it->is_end = pattern_number;
    it->pattern_len = pat_len;
}

void TAho_Corasick::Build_Links(TTrie *root)
{
    std::queue<TTrie *> queue;
    queue.push(root);
    TTrie *it;
    while (!queue.empty()) {
        it = queue.front();
        queue.pop();
        link(it);
        for (auto child: it->next) {
            queue.push(child);
        }
    }
}

void TAho_Corasick::link(TTrie *node)
{
    if (!node->prew) {
        node->fail_link = node; // Может, его в nullptr перевести?
    }
    else if (!node->prew->prew) {
        node->fail_link = node->prew;
    }
    else {
        node->fail_link = go(node->prew->fail_link, node->letter);
        if (node->fail_link->is_end) {
            node->output_link = node->fail_link;
        }
        else if (node->fail_link->output_link) {
            node->output_link = node->fail_link->output_link;
        }
    }
}

void TAho_Corasick::bypass_output_links(TTrie *node, int counter, int string_number)
{
    do {
        std::cout << string_number << ", " << counter - node->output_link->pattern_len << ", "
                  << node->output_link->is_end << std::endl;
        node = node->output_link;
    }
    while (node->output_link);
}

TTrie *TAho_Corasick::go(TTrie *node, std::string &letter)
{
    for (TTrie *child: node->next) {
        if (child->letter == letter) {
            return child;
        }
    }
    if (!node->prew) return node;
    return go(node->fail_link, letter);
}

void TAho_Corasick::Search(TTrie *root, const std::string &text, int string_number)
{
    TTrie *it = root;
    bool stop;
    std::string letter;
    int count_spaces = 1;
    for (int i = 0; i < text.length(); ++i) {
        if (sep(text[i])) {
            letter = "";
            continue;
        }
        else if (check(text[i]) || text[i] == '0') {
            letter.push_back(text[i]);
            if (!sep(text[i + 1])) {
                continue;
            }
            else {
                ++count_spaces;
            }
        }
        stop = true;
        do {
            for (TTrie *child: it->next) {
                if (child->letter == letter) {
                    it = child;
                    stop = false;
                    if (it->output_link) {
                        //std::cout << "[ol]:";
                        bypass_output_links(it, count_spaces, string_number);
                    }
                    if (it->is_end) {
                        //std::cout << "[end]:";
                        std::cout << string_number << ", " << count_spaces - it->pattern_len << ", " << it->is_end
                                  << std::endl;
                    }
                    break;
                }
            }
            if (stop) {
                if (it == root) {
                    break;
                }
                it = it->fail_link;
            }
        }
        while (stop);

    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::string pattern = "a";
    std::string norm_string;
    std::string text = "g";
    TTrie *root = new TTrie();
    int count = 0;
    while (true) {
        std::getline(std::cin, pattern);
        if (pattern.length() == 0) break;
        pattern.push_back(' ');
        norm_string = TAho_Corasick::process(pattern);
        ++count;
        TAho_Corasick::Add(root, norm_string, count);
    }
    TAho_Corasick::Build_Links(root);
    count = 0;
    while (std::getline(std::cin, text)) {
        if (text == "!") break;
        ++count;
        text.push_back(' ');
        norm_string = TAho_Corasick::process(text);
        //std::cout << "[ns]: " << norm_string << std::endl;
        norm_string.push_back(' ');
        TAho_Corasick::Search(root, norm_string, count);
    }
    delete root;
    return 0;
}
