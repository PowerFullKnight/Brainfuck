#ifndef TRANSLATOR_H_INCLUDED
#define TRANSLATOR_H_INCLUDED

#include <ostream>
#include <vector>
#include "Token.h"

class Translator
{
public:
    enum Language{C, Cpp};
    Translator(const std::vector<Token>& tokenList_arg);

    void toStream(std::ostream& stream, Language lang);

private:
    void toStream_c(std::ostream& stream);

    std::vector<Token> m_tokenList;
};

#endif // TRANSLATOR_H_INCLUDED
