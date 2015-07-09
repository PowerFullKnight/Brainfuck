#include "Interpretor.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

#include "Translator.h"

std::string Interpretor::s_legalsCharacter = "><+-[],.";

// => Class implementation
Interpretor::Interpretor():
    m_expression(),
    m_tokenList()
{}

void Interpretor::scan()
{
    std::cout << ">>> ";
    getline(std::cin, m_expression);
}

void Interpretor::openFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    if(!file)
    {
        std::cerr << "Cannot read file \"" << fileName << "\".\n";
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    m_expression = buffer.str();
}

void Interpretor::setExpr(const std::string& expr)
{
    m_expression = expr;
}

void Interpretor::cleanExpr()
{
    for(std::size_t i(0); i < m_expression.size();)
    {
        const auto ch = m_expression[i];
        if(s_legalsCharacter.find(ch) == std::string::npos){ // No legal character
            m_expression.erase(i, 1);
        }else{
            ++i;
        }
    }
}

void Interpretor::tokenise()
{
    const auto sz = m_expression.size();

    for(std::size_t i(0); i < sz; ++i)
    {
        Token actual(m_expression[i]);
        m_tokenList.push_back(actual);
    }
}

void Interpretor::mergeToken()
{
    auto beg = m_tokenList.begin();
    bool inc {true}; // Are we do increment beg ?
    while(beg != m_tokenList.end())
    {
        inc = true;
        // Merge equals tokens
        if( beg+1 != m_tokenList.end() && beg->kind() == (beg+1)->kind())
        {
            if(beg->canHaveValue())
            {
                beg->setValue(beg->value() + (beg+1)->value());
                m_tokenList.erase(beg + 1);
                inc = false;
            }
        }

        // Merge opposite tokens
        if(beg+1 != m_tokenList.end() && beg->isOpposite(*(beg+1)))
        {
            auto opposate = beg+1;
            if(opposate->value() > beg->value())
            {
                beg->setKind(opposate->kind());
                beg->setValue(opposate->value() - beg->value());
                m_tokenList.erase(beg+1);
            }
            else if(opposate->value() < beg->value())
            {
                beg->setValue(beg->value() - opposate->value());
                m_tokenList.erase(beg+1);
            }
            else // Value equal = null instruction
            {
                beg->setValue(0);
                m_tokenList.erase(beg+1);
            }
            inc = false;
        }
        if(inc)
            ++beg;
    }

    // Removing null value
    for(auto it = m_tokenList.begin(); it != m_tokenList.end();)
    {
        if(it->canHaveValue() && it->value() == 0 && it->kind()!= Token::Set){
            it = m_tokenList.erase(it);
        }
        else
            ++it;
    }

}

void Interpretor::brainfuckOptimization()
{

    auto beg = m_tokenList.begin();
    bool inc { false };
    while(beg != m_tokenList.end())
    {
        inc = true;
        // [-]
        if(beg + 1 != m_tokenList.end() && beg +2 != m_tokenList.end())
        {
            if(beg->isWhileBeg() && (beg+1)->isMinus() && (beg+2)->isWhileEnd())
            {
                *beg = Token(Token::Set, 0);
                m_tokenList.erase(beg+1, beg+3);
                inc = false;
            }
        }
        // [-]+++
        if(beg + 1 != m_tokenList.end() && beg->isSet())
        {
            if((beg+1)->isPlus())
            {
                beg->setValue(beg->value() + (beg+1)->value());
                m_tokenList.erase(beg+1);
                inc = false;
            }
            if((beg+1)->isMinus())
            {
                beg->setValue(255 - (beg+1)->value() +1);
                m_tokenList.erase(beg+1);
                inc = false;
            }
        }

        if(inc)
            ++beg;
    }
}

std::vector<Token> Interpretor::tokenList() const
{
    return m_tokenList;
}
