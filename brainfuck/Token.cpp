#include "Token.h"

std::ostream& operator<<(std::ostream& stream, const Token& token)
{
    stream << "{ ";
    switch(token.kind())
    {
    case Token::None:
        stream << "None";
        break;
    case Token::Right:
        stream << "Right";
        break;
    case Token::Left:
        stream << "Left";
        break;
    case Token::Plus:
        stream << "+";
        break;
    case Token::Minus:
        stream << "-";
        break;
    case Token::While_beg:
        stream << "While_beg";
        break;
    case Token::While_end:
        stream << "While_end";
        break;
    case Token::Print:
        stream << "Print";
        break;
    case Token::Input:
        stream << "Input";
        break;

    // Logic
    case Token::Set:
        stream << "Set";
        break;

    default:
        stream << "Error.";
        break;
    }
    if(token.canHaveValue())
    {
        stream << " value = " << token.value();
    }
    stream << " }";
    return stream;
}
