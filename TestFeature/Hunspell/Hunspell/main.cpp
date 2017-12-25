#include <iostream>
#include <string>
#include <hunspell/hunspell.hxx>


int main()
{
    Hunspell hun ("/usr/share/hunspell/vi_VN.aff", "/usr/share/hunspell/vi_VN.dic");

    std::cout << "Please enter one word:" << std::endl;
    std::string word = "chậng";
    std::vector<std::string> suggestion;
    if (hun.spell(word.c_str(), NULL, NULL) == 0) {
            std::cout << "Spelling Error!" << std::endl;
            suggestion = hun.suggest(word.c_str());
            for(int i=0; i<suggestion.size(); ++i)
            {
                std::cout << suggestion[i] << std::endl;
            }
    } else {
            std::cout << "Correct Spelling!";
    }

    return 0;
}
