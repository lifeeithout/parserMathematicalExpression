#include "LexemeBuffer.h"

#include <stdexcept>

LexemeBuffer::LexemeBuffer(const std::list<Lexeme>& lex)
	:lexemes(lex), position(0ull)
{   }

Lexeme LexemeBuffer::next()
{
    std::list<Lexeme>::const_iterator iter = lexemes.begin();
    std::advance(iter, position++);

    if (iter != lexemes.end()) 
    {
        return *iter;
    }
    else 
    {
        throw std::out_of_range("Index out of range");
    }
}

void LexemeBuffer::back()
{
    --position;
}

size_t LexemeBuffer::getPosition() const
{
    return position;
}
