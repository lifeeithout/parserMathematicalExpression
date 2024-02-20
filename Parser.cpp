#include "Parser.h"

#include <stdexcept>

float Parser::calculate(const std::string& expression)
{
    std::list<Lexeme> lexemes = lexicalAnalys(expression);

    LexemeBuffer lexemeBuffer(lexemes);

    return this->expression(lexemeBuffer);
}

std::list<Lexeme> Parser::lexicalAnalys(const std::string& expression)
{
    std::list<Lexeme> lexemes;

    for (size_t iter = 0; iter < expression.size(); ++iter)
    {
        switch (expression[iter])
        {
        case '(':
            lexemes.push_back(Lexeme(LexemeType::LEFT_BRACKET, expression[iter]));
            break;
        case ')':
            lexemes.push_back(Lexeme(LexemeType::RIGHT_BRACKET, expression[iter]));
            break;
        case '+':
            lexemes.push_back(Lexeme(LexemeType::OPERATOR_ADDITION, expression[iter]));
            break;
        case '-':
            lexemes.push_back(Lexeme(LexemeType::OPERATOR_SUBTRACTION, expression[iter]));
            break;
        case '*':
            lexemes.push_back(Lexeme(LexemeType::OPERATOR_MULTIPLICATION, expression[iter]));
            break;
        case '/':
            lexemes.push_back(Lexeme(LexemeType::OPERATOR_DIVISION, expression[iter]));
            break;
        case ',':
            lexemes.push_back(Lexeme(LexemeType::COMMA_LITERAL, expression[iter]));
            break;
        default:
            if (std::isdigit(expression[iter]))
            {
                std::string number;

                while (std::isdigit(expression[iter]) or expression[iter] == '.')
                {
                    number += expression[iter];
                    ++iter;
                }

                lexemes.push_back(Lexeme(LexemeType::NUMERIC_LITERAL, number, std::stof(number)));
                --iter;
            }
            else if (std::isalpha(expression[iter]))
            {
                std::string name;

                while (iter < expression.size() and expression[iter] != ' ' and
                    expression[iter] != '(' and expression[iter] != ')' and
                    expression[iter] != '+' and expression[iter] != '-' and
                    expression[iter] != '*' and expression[iter] != '/')
                {
                    name += expression[iter];
                    ++iter;
                }

                if (builtInFunctions.isHaveFunction(name))
                {
                    lexemes.push_back(Lexeme(LexemeType::NAME_OF_FUNCTION, name));
                }
                else
                {
                    throw std::invalid_argument("Bad argument in expression: " + name);
                }
                --iter;
            }
            else if (expression[iter] != ' ')
            {
                throw std::invalid_argument("Bad argument in expression: " + expression[iter]);
            }
            break;
        }
    }

    lexemes.push_back(Lexeme(LexemeType::END_OF_FILE, ""));

    return lexemes;
}

float Parser::expression(LexemeBuffer& lexemes)
{
    Lexeme lexeme = lexemes.next();

    if (lexeme.getType() == LexemeType::END_OF_FILE)
    {
        return 0.0f;
    }
    else
    {
        lexemes.back();
        return additionSubtruction(lexemes);
    }
}

float Parser::factor(LexemeBuffer& lexemes)
{
    Lexeme lexeme = lexemes.next();

    switch (lexeme.getType())
    {
    case LexemeType::NAME_OF_FUNCTION:
    {
        lexemes.back();
        return function(lexemes);
    }
    case LexemeType::OPERATOR_SUBTRACTION:
    {
        return -factor(lexemes);
    }
    case LexemeType::NUMERIC_LITERAL:
    case LexemeType::CONSTANT_LITERAL:
    {
        return lexeme.getValue();
    }
    case LexemeType::LEFT_BRACKET:
    {
        float value = expression(lexemes);

        lexeme = lexemes.next();
        if (lexeme.getType() != LexemeType::RIGHT_BRACKET)
        {
            throw std::invalid_argument("Unexpected token: " + lexeme.getView() + " at position: " + std::to_string(lexemes.getPosition()));
        }

        return value;
    }
    default:
        throw std::invalid_argument("Unexpected token: " + lexeme.getView() + " at position: " + std::to_string(lexemes.getPosition()));
    }
}

float Parser::function(LexemeBuffer& lexemes)
{
    std::string name = lexemes.next().getView();

    Lexeme lexeme = lexemes.next();
    if (lexeme.getType() != LexemeType::LEFT_BRACKET)
    {
        throw std::invalid_argument("Wrong function call syntax at + " + lexeme.getView());
    }

    std::list<float> arguments;

    Lexeme nextLexeme = lexemes.next();
    if (nextLexeme.getType() != LexemeType::RIGHT_BRACKET)
    {
        lexemes.back();

        do
        {
            arguments.push_back(expression(lexemes));
            nextLexeme = lexemes.next();

            if (nextLexeme.getType() != LexemeType::COMMA_LITERAL and nextLexeme.getType() != LexemeType::RIGHT_BRACKET)
            {
                throw std::invalid_argument("Wrong function call syntax at + " + lexeme.getView());
            }

        } while (nextLexeme.getType() == LexemeType::COMMA_LITERAL);
    }

    return (builtInFunctions.getFunction(name))->second(arguments);
}

float Parser::additionSubtruction(LexemeBuffer& lexemes)
{
    float value = multiplicationDivision(lexemes);

    while (true)
    {
        Lexeme lexeme = lexemes.next();

        switch (lexeme.getType())
        {
        case LexemeType::OPERATOR_ADDITION:
            value += multiplicationDivision(lexemes);
            break;
        case LexemeType::OPERATOR_SUBTRACTION:
            value -= multiplicationDivision(lexemes);
            break;
        case LexemeType::RIGHT_BRACKET:
        case LexemeType::END_OF_FILE:
        case LexemeType::COMMA_LITERAL:
        {
            lexemes.back();
            return value;
        }
        default:
            throw std::invalid_argument("Unexpected token: " + lexeme.getView() + " at position: " + std::to_string(lexemes.getPosition()));
        }
    }
}

float Parser::multiplicationDivision(LexemeBuffer& lexemes)
{
    float value = factor(lexemes);

    while (true)
    {
        Lexeme lexeme = lexemes.next();

        switch (lexeme.getType())
        {
        case LexemeType::OPERATOR_MULTIPLICATION:
            value *= factor(lexemes);
            break;
        case LexemeType::OPERATOR_DIVISION:
            value /= factor(lexemes);
            break;
        case LexemeType::RIGHT_BRACKET:
        case LexemeType::END_OF_FILE:
        case LexemeType::COMMA_LITERAL:
        case LexemeType::OPERATOR_ADDITION:
        case LexemeType::OPERATOR_SUBTRACTION:
        {
            lexemes.back();
            return value;
        }
        default:
            throw std::invalid_argument("Unexpected token: " + lexeme.getView() + " at position: " + std::to_string(lexemes.getPosition()));
        }
    }
}

