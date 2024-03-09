#include <sstream>
#include"Token.h"


TokenType stringToTokenType(const std::string &str){
    if (str == "error") return TokenType::ERROR;
    if (str == "id") return TokenType::ID;
    if (str == "program")return TokenType::PROGRAM;
    if (str == "procedure") return TokenType::PROCEDURE;
    if (str == "type") return TokenType::TYPE;
    if (str == "var") return TokenType::VAR;
    if (str == "if") return TokenType::IF;
    if (str == "then") return TokenType::THEN;
    if (str == "else")  return TokenType::ELSE;
    if (str == "fi") return TokenType::FI;
    if (str == "while") return TokenType::WHILE;
    if (str == "do") return TokenType::DO;
    if (str == "endwh") return TokenType::ENDWH;
    if (str == "begin") return TokenType::BEGIN;
    if (str == "end") return TokenType::END;
    if (str == "read") return TokenType::READ;
    if (str == "write") return TokenType::WRITE;
    if (str == "error") return TokenType::OF;
    if (str == "error") return TokenType::RETURN;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error")return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    if (str == "error") return TokenType::ERROR;
    return TokenType::ERROR;
}

Token::Token()
{
    Token(TokenType::EMPTY);
}
Token::Token(TokenType type)
{
    Token(0, 0, type, TokenTypeToString[type]);
}
Token::Token(int line, int colum, TokenType type, std::string value)
{
    this->line = line;
    this->column = column;
    this->type = type;
    this->value = value;
}
void Token::checkKeyWord(){
    if(type==TokenType::ID){
        type = stringToTokenType(this->value);
    }
}
int Token::getLine() { return this->line; }
int Token::getColumn() { return this->column; }
TokenType Token::getType() { return this->type; }
std::string Token::getValue() { return this->value; }
std:: string Token::toString() {
    std::stringstream ss;
    ss << "< (" << this->line << "," << this->column << "), " << TokenTypeToString[this->type] << ", " << this->value << " >";
    return ss.str();
}