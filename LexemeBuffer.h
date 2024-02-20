#ifndef LEXEMEBUFFER_H
#define LEXEMEBUFFER_H

#include <list>

#include "Lexeme.h"

class LexemeBuffer
{
public:
	LexemeBuffer(const std::list<Lexeme>&);

	Lexeme next();
	void back();
	size_t getPosition() const;
private:
	size_t position;
	std::list<Lexeme> lexemes;
};

#endif // !LEXEMEBUFFER_H
