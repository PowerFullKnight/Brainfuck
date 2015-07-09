#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <ostream>


class Token
{
public:
    enum Kind{
        None,
        Right, Left, Plus, Minus, While_beg, While_end, Print, Input, // Brainfuck token
        Set
    };

    typedef unsigned long long value_type;

    Token(Kind kind_arg, value_type value_arg = 0):
        m_kind(kind_arg), m_value(value_arg)
    {
        if(m_value == 0)
        {
            switch(m_kind)
            {
            case Right:
            case Left:
            case Plus:
            case Minus:
                m_value = 1;
                break;
            default:
                break;
            }
        }
    }

    Token(char character, value_type value_arg = 0):
        m_kind(None), m_value(value_arg)
    {
        switch(character)
        {
        case '>':
            m_kind = Right;
            break;
        case '<':
            m_kind = Left;
            break;
        case '+':
            m_kind = Plus;
            break;
        case '-':
            m_kind = Minus;
            break;
        case '[':
            m_kind = While_beg;
            break;
        case ']':
            m_kind = While_end;
            break;
        case '.':
            m_kind = Print;
            break;
        case ',':
            m_kind = Input;
            break;
        default:
            m_kind = None;
            break;
        }
        if(m_value == 0)
        {
            switch(m_kind)
            {
            case Right:
            case Left:
            case Plus:
            case Minus:
                m_value = 1;
                break;
            default:
                break;
            }
        }
    }

    Kind kind() const noexcept { return m_kind; }
    void setKind(Kind kind_arg) noexcept { m_kind = kind_arg; }

    Token::value_type value() const noexcept { return m_value; }
    void setValue(Token::value_type value_arg) noexcept { m_value = value_arg; }

    bool isNull() const noexcept     { return m_kind == None;     }
    bool isRight() const noexcept    { return m_kind == Right;     }
    bool isLeft() const noexcept     { return m_kind == Left;      }
    bool isPlus() const noexcept     { return m_kind == Plus;      }
    bool isMinus() const noexcept    { return m_kind == Minus;     }
    bool isWhileBeg() const noexcept { return m_kind == While_beg; }
    bool isWhileEnd() const noexcept { return m_kind == While_end; }
    bool isPrint() const noexcept    { return m_kind == Print;     }
    bool isInput() const noexcept    { return m_kind == Input;     }
    bool isSet() const noexcept      { return m_kind == Set;     }

    bool canHaveValue() const noexcept { return (m_kind == Right || m_kind == Left || m_kind == Plus || m_kind == Minus || m_kind == Set); }
    bool isOpposite(const Token& lhs) const noexcept
    {
        switch(lhs.m_kind)
        {
        case Left:
            return m_kind == Right;
            break;
        case Right:
            return m_kind == Left;
            break;
        case Plus:
            return m_kind == Minus;
            break;
        case Minus:
            return m_kind == Plus;
            break;
        default:
            break;
        }
        return false;
    }

    bool operator==(const Token& lhs) const { return lhs.m_kind == m_kind; }
    bool operator!=(const Token& lhs) const { return lhs.m_kind != m_kind; }

private:
    Kind m_kind;
    value_type m_value;
};

std::ostream& operator<<(std::ostream& stream, const Token& token);

#endif // TOKEN_H_INCLUDED
