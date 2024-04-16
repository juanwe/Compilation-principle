#include "NonTerminalEnum.h"
#include "NonTerminal.h"
#include "Terminal.h"

// 构造函数
NonTerminalEnum::NonTerminalEnum(NON_TERMINAL type, const NonTerminal &nonTerminal) : type(type), nonTerminal(nonTerminal) {}

// 预测方法
std::vector<std::shared_ptr<Symbol>> NonTerminalEnum::predict(Token token)
{
    switch (type)
    {
    case NON_TERMINAL::Program:
        if (token.getType() == TokenType::PROGRAM)
        {
            result.push_back(std::make_shared<NonTerminal>("ProgramHead"));
            result.push_back(std::make_shared<NonTerminal>("DeclarePart"));
            result.push_back(std::make_shared<NonTerminal>("ProgramBody"));
            result.push_back(std::make_shared<Terminal>(TokenType::_EOF_));
        }
        break;
    case NON_TERMINAL::ProgramHead:
        if (token.getType() == TokenType::PROGRAM)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::PROGRAM));
            result.push_back(std::make_shared<NonTerminal>("ProgramName"));
        }
        break;
    case NON_TERMINAL::ProgramName:
        if (token.getType() == TokenType::ID)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
        }
        break;
    case NON_TERMINAL::DeclarePart : 
        TokenType type = token.getType();
        if (type == TokenType::TYPE || type == TokenType::VAR || type == TokenType::PROCEDURE || type == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("TypeDecpart"));
            result.push_back(std::make_shared<NonTerminal>("VarDecpart"));
            result.push_back(std::make_shared<NonTerminal>("ProcDecpart"));
        }
        break;
    case NON_TERMINAL::TypeDecpart:
        TokenType type = token.getType();
        if(type == TokenType::VAR||type==TokenType::PROCEDURE||type==TokenType::BEGIN){
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }else if(type==TokenType::TYPE){
            result.push_back(std::make_shared<NonTerminal>("TypeDec"));
        }
        break;
    case NON_TERMINAL::TypeDec:
        TokenType type = token.getType();
        if (type == TokenType::TYPE)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::TYPE));
            result.push_back(std::make_shared<NonTerminal>("TypeDecList"));
        }
        break;
    }
    return this->result;
}