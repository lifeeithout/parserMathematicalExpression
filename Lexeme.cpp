#include "Lexeme.h"

Lexeme::Lexeme(LexemeType type, const std::string& view, float value)
{
	this->type = type;
	this->view = view;
	this->value = value;
}

Lexeme::Lexeme(LexemeType type, char view, float value)
{
	this->type = type;
	this->view = view;
	this->value = value;
}

LexemeType Lexeme::getType() const
{
	return type;
}

float Lexeme::getValue() const
{
	return value;
}

std::string Lexeme::getView() const
{
	return view;
}
