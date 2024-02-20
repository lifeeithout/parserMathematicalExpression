#ifndef LEXEME_H
#define LEXEME_H

#include <string>

enum class LexemeType
{
    RIGHT_BRACKET, 
    LEFT_BRACKET,
    OPERATOR_ADDITION,
    OPERATOR_SUBTRACTION,
    OPERATOR_MULTIPLICATION,
    OPERATOR_DIVISION,
    NUMERIC_LITERAL,
    CONSTANT_LITERAL,
    NAME_OF_FUNCTION,
    COMMA_LITERAL,
    END_OF_FILE
};

class Lexeme
{
public:
	Lexeme(LexemeType, const std::string&, float = 0.0f);
	Lexeme(LexemeType, char, float = 0.0f);

    LexemeType getType() const;
    float getValue() const;
    std::string getView() const;
private:
	LexemeType type;
	std::string view;
    float value;
};

#endif // !LEXEME_H
