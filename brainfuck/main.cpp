#include <iostream>
#include <string>
#include <fstream>

#include <cctype>

#include "Interpretor.h"
#include "Translator.h"

void launchInterpretor(const std::string& fileName = std::string());

void launchInterpretor(const std::string& fileName)
{
    Interpretor inter;
    if(fileName.empty())
        inter.scan();
    else{
        std::cout << "Opening file ...\n";
        inter.openFile(fileName);
    }

    inter.cleanExpr();
    inter.tokenise();
    inter.mergeToken();
    inter.brainfuckOptimization();

    const auto tokenSz = inter.tokenList().size();
    std::cout << "Show token ? (" << tokenSz;
    if(tokenSz > 1)
        std::cout <<" token";
    else
        std::cout << " tokens";
    std::cout << ") {O;N} ";

    char c;
    std::cin >> c;
    if(toupper(c) == 'O')
    {
        for(auto t : inter.tokenList())
        {
            std::cout << t<< ' ';
        }
        if(tokenSz == 0)
        {
            std::cout << "Nothing.\n";
        }
    }

    std::cout << "\n\nFile output : ";
    std::string filePath;
    std::cin >> filePath;
    std::ofstream file(filePath);
    if(!file){
        std::cerr << "Cannot open file \"" << filePath << "\".\n";
        return;
    }
    Translator translator(inter.tokenList());
    translator.toStream(file, Translator::C);

}

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        launchInterpretor();
    }
    else if(argc == 2)
    {
        launchInterpretor(argv[1]);
    }
    return 0;
}
