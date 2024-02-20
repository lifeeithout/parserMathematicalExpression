#ifndef PARSER_H
#define PARSER_H

#include <list>

#include <string>

#include <functional>

#include "Lexeme.h"

#include "LexemeBuffer.h"

#include "FunctionBuffer.h"

class Parser
{
public:
	float calculate(const std::string&);
private:
	std::list<Lexeme> lexicalAnalys(const std::string&); 

	float expression(LexemeBuffer&);

	float factor(LexemeBuffer&);

	float function(LexemeBuffer&);

	float additionSubtruction(LexemeBuffer&);

	float multiplicationDivision(LexemeBuffer&);

	FunctionBuffer builtInFunctions; // Встроенные функции типа sin(), cos()...
};

#endif // !PARSER_H
