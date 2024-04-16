#include <sstream>
#include "Token.h"

TokenType stringToTokenType(const std::string &str)
{
    if (str == "error")
        return TokenType::ERROR;
    if (str == "id")
        return TokenType::ID;
    if (str == "program")
        return TokenType::PROGRAM;
    if (str == "procedure")
        return TokenType::PROCEDURE;
    if (str == "type")
        return TokenType::TYPE;
    if (str == "var")
        return TokenType::VAR;
    if (str == "if")
        return TokenType::IF;
    if (str == "then")
        return TokenType::THEN;
    if (str == "else")
        return TokenType::ELSE;
    if (str == "fi")
        return TokenType::FI;
    if (str == "while")
        return TokenType::WHILE;
    if (str == "do")
        return TokenType::DO;
    if (str == "endwh")
        return TokenType::ENDWH;
    if (str == "begin")
        return TokenType::BEGIN;
    if (str == "end")
        return TokenType::END;
    if (str == "read")
        return TokenType::READ;
    if (str == "write")
        return TokenType::WRITE;
    if (str == "of")
        return TokenType::OF;
    if (str == "return")
        return TokenType::RETURN;
    if (str == "integer")
        return TokenType::INTEGER;
    if (str == "char")
        return TokenType::CHAR;
    if (str == "array")
        return TokenType::ARRAY;
    if (str == "record")
        return TokenType::RECORD;
    if (str == "inic")
        return TokenType::INTC;
    if (str == "=")
        return TokenType::EQ;
    if (str == "<")
        return TokenType::LT;
    if (str == ".")
        return TokenType::_EOF_;
    if (str == " ")
        return TokenType::EMPTY;
    if (str == "+")
        return TokenType::PLUS;
    if (str == "-")
        return TokenType::MINUS;
    if (str == "*")
        return TokenType::MULTIPLE;
    if (str == "/")
        return TokenType::DIVISION;
    if (str == "(")
        return TokenType::L_BRACKET;
    if (str == ")")
        return TokenType::R_BRACKET;
    if (str == "[")
        return TokenType::L_S_BRACKETS;
    if (str == "]")
        return TokenType::R_S_BRACKET;
    if (str == ";")
        return TokenType::SEMI;
    if (str == ",")
        return TokenType::COMMA;
    if (str == ".")
        return TokenType::DOT;
    if (str == ":=")
        return TokenType::ASSIGN;
    if (str == "..")
        return TokenType::ARRAY_BOUNDS;
    return TokenType::ERROR;
}

Token::Token(){
    Token(false);
}
Token::Token(bool isValid)
{
    Token(TokenType::EMPTY,bool isValid);
}
Token::Token(TokenType type,bool isValid)
{
    Token(0, 0, type, TokenTypeToString[type]);
}
Token::Token(int line, int colum, TokenType type, std::string value,bool isValid)
{
    this->line = line;
    this->column = column;
    this->type = type;
    this->value = value;
    this->isValid = isValid;
}
void Token::checkKeyWord()
{
    if (type == TokenType::ID)
    {
        type = stringToTokenType(this->value);
    }
}
int Token::getLine() { return this->line; }
int Token::getColumn() { return this->column; }
TokenType Token::getType() { return this->type; }
std::string Token::getValue() { return this->value; }
bool Token::isValidObject() { return this->isValid; }
std::string Token::toString()
{
    std::stringstream ss;
    ss << "< (" << this->line << "," << this->column << "), " << TokenTypeToString[this->type] << ", " << this->value << " >";
    return ss.str();
}