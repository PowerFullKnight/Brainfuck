#include "Translator.h"

#include <fstream>


Translator::Translator(const std::vector<Token>& tokenList_arg):
    m_tokenList(tokenList_arg)
{}

void Translator::toStream(std::ostream& stream, Language lang)
{
    switch(lang)
    {
    case C:
        toStream_c(stream);
        break;
    default:
        break;
    }
}

void Translator::toStream_c(std::ostream& stream)
{
    stream << "#include <stdio.h>\n"
              "#include <stdlib.h>\n"
              "int main(int argc, char* argv[]){\n"
              "unsigned char *ptr = calloc(30000,sizeof(unsigned char));\n";
    for(auto t : m_tokenList)
    {
        switch(t.kind())
        {
        case Token::Right:
            stream << "ptr+=" << t.value() << ';';
            break;
        case Token::Left:
            stream << "ptr-=" << t.value() << ';';
            break;
        case Token::Plus:
            stream << "(*ptr) +=" << t.value() << ';';
            break;
        case Token::Minus:
            stream << "(*ptr) -= " << t.value() << ';';
            break;
        case Token::While_beg:
            stream << "while(*ptr){";
            break;
        case Token::While_end:
            stream << "}";
            break;
        case Token::Print:
            stream << "putchar(*ptr);";
            break;
        case Token::Input:
            stream << "*ptr = getchar();";
            break;
        case Token::Set:
            stream << "*ptr = " << t.value() << ';';
            break;
        default:
            break;
        }
        stream << '\n';
    }
    stream << "free(ptr);\nreturn 0;/* END PRGM*/\n} /* End main */";
}
