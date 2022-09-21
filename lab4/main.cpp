#include "Aho_Corasick.h"


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::string pattern = "a";
    std::string norm_string;
    std::string text = "g";

   TTrie* root = new TTrie();
   int count = 0;
   while (true){
       std::getline(std::cin, pattern);
       if (pattern.length() == 0) break;
       pattern.push_back(' ');
       norm_string = TAho_Corasick::process(pattern);
       ++count;
       TAho_Corasick::Add(root, norm_string, count);
   }
   TAho_Corasick::Build_Links(root);
   count = 0;
   while(std::getline(std::cin, text)){
       if (text == "!") break;
       ++count;
       text.push_back(' ');
       norm_string = TAho_Corasick::process(text);
       TAho_Corasick::Search(root, norm_string, count);
   }
   delete root;
    return 0;
}

