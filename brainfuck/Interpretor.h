#ifndef INTERPRETOR_H_INCLUDED
#define INTERPRETOR_H_INCLUDED

#include <string>
#include <vector>

#include "Token.h"

class Interpretor
{
public:
    Interpretor();

    void scan();
    void openFile(const std::string& fileName);
    void setExpr(const std::string& expr);

    void cleanExpr();
    void tokenise();
    void mergeToken();
    void brainfuckOptimization();
    std::vector<Token> tokenList() const;

private:
    std::string m_expression;
    std::vector<Token> m_tokenList;
    static std::string s_legalsCharacter;
};

#endif // INTERPRETOR_H_INCLUDED
