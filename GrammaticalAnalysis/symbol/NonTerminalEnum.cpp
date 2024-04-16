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
        //1
    case NON_TERMINAL::Program:
        if (token.getType() == TokenType::PROGRAM)
        {
            result.push_back(std::make_shared<NonTerminal>("ProgramHead"));
            result.push_back(std::make_shared<NonTerminal>("DeclarePart"));
            result.push_back(std::make_shared<NonTerminal>("ProgramBody"));
            result.push_back(std::make_shared<Terminal>(TokenType::_EOF_));
        }
        break;
        //2
    case NON_TERMINAL::ProgramHead:
        if (token.getType() == TokenType::PROGRAM)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::PROGRAM));
            result.push_back(std::make_shared<NonTerminal>("ProgramName"));
        }
        break;
        //3
    case NON_TERMINAL::ProgramName:
        if (token.getType() == TokenType::ID)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
        }
        break;
        //4
    case NON_TERMINAL::DeclarePart : 
        TokenType type = token.getType();
        if (type == TokenType::TYPE || type == TokenType::VAR || type == TokenType::PROCEDURE || type == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("TypeDecpart"));
            result.push_back(std::make_shared<NonTerminal>("VarDecpart"));
            result.push_back(std::make_shared<NonTerminal>("ProcDecpart"));
        }
        break;
        //5 6
    case NON_TERMINAL::TypeDecpart:
        TokenType type = token.getType();
        if(type == TokenType::VAR||type==TokenType::PROCEDURE||type==TokenType::BEGIN){
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }else if(type==TokenType::TYPE){
            result.push_back(std::make_shared<NonTerminal>("TypeDec"));
        }
        break;
        //7
    case NON_TERMINAL::TypeDec:
        TokenType type = token.getType();
        if (type == TokenType::TYPE)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::TYPE));
            result.push_back(std::make_shared<NonTerminal>("TypeDecList"));
        }
        break;
        //8
    case NON_TERMINAL::TypeDecList:
        TokenType type = token.getType();
        if (type == TokenType::ID)
        {
            result.push_back(std::make_shared<NonTerminal>("TypeId"));
            result.push_back(std::make_shared<Terminal>(TokenType::EQ));
            result.push_back(std::make_shared<NonTerminal>("TypeDef"));
            result.push_back(std::make_shared<Terminal>(TokenType::SEMI));
            result.push_back(std::make_shared<NonTerminal>("TypeDecMore"));
        }
        break;
        //9 10
    case NON_TERMINAL::TypeDecMore:
        TokenType type = token.getType();
        if (type == TokenType::VAR || type == TokenType::PROCEDURE || type == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }else if(type==TokenType::ID){
            result.push_back(std::make_shared<NonTerminal>("TypeDecList"));
        }
        break;
        //11
    case NON_TERMINAL::TypeId:
        TokenType type = token.getType();
        if (type == TokenType::ID )
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
        }
        break;
        //12 13 14
    case NON_TERMINAL::TypeDef:
        TokenType type = token.getType();
        if (type == TokenType::INTEGER || type == TokenType::CHAR)
        {
            result.push_back(std::make_shared<NonTerminal>("BaseType"));
        }
        else if (type == TokenType::ARRAY||type==TokenType::RECORD)
        {
            result.push_back(std::make_shared<NonTerminal>("StructureType"));
        }else if(type==TokenType::ID){
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
        }
        break;
        //15 16
    case NON_TERMINAL::BaseType:
        TokenType type = token.getType();
        if (type == TokenType::INTEGER)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::INTEGER));
        }
        else if (type == TokenType::CHAR)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::CHAR));
        }
        break;
        //17 18
    case NON_TERMINAL::StructureType:
        TokenType type = token.getType();
        if (type == TokenType::ARRAY)
        {
            result.push_back(std::make_shared<NonTerminal>("ArrayType"));
        }
        else if (type == TokenType::RECORD)
        {
            result.push_back(std::make_shared<NonTerminal>("RecType"));
        }
        break;
        //19
    case NON_TERMINAL::ArrayType:
        TokenType type = token.getType();
        if (type == TokenType::ARRAY)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ARRAY));
            result.push_back(std::make_shared<Terminal>(TokenType::L_S_BRACKETS));
            result.push_back(std::make_shared<NonTerminal>("Low"));
            result.push_back(std::make_shared<Terminal>(TokenType::ARRAY_BOUNDS));
            result.push_back(std::make_shared<NonTerminal>("Top"));
            result.push_back(std::make_shared<Terminal>(TokenType::R_S_BRACKET));
            result.push_back(std::make_shared<Terminal>(TokenType::OF));
            result.push_back(std::make_shared<NonTerminal>("BaseType"));
        }
        break;
        //20
    case NON_TERMINAL::Low:
        TokenType type = token.getType();
        if (type == TokenType::INTC)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::INTC));
        }
        break;
        //21
    case NON_TERMINAL::Top:
        TokenType type = token.getType();
        if (type == TokenType::INTC)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::INTC));
        }
        break;
        //22
    case NON_TERMINAL::RecType:
        TokenType type = token.getType();
        if (type == TokenType::RECORD)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::RECORD));
            result.push_back(std::make_shared<NonTerminal>("FieldDecList"));
            result.push_back(std::make_shared<Terminal>(TokenType::END));
        }
        break;
        //23 24
    case NON_TERMINAL::FieldDecList:
        TokenType type = token.getType();
        if (type == TokenType::INTEGER || type == TokenType::CHAR)
        {
            result.push_back(std::make_shared<NonTerminal>("BaseType"));
            result.push_back(std::make_shared<NonTerminal>("IdList"));
            result.push_back(std::make_shared<Terminal>(TokenType::SEMI));
            result.push_back(std::make_shared<NonTerminal>("FieldDecMore"));
        }
        else if (type == TokenType::ARRAY)
        {
            result.push_back(std::make_shared<NonTerminal>("ArrayType"));
            result.push_back(std::make_shared<NonTerminal>("IdList"));
            result.push_back(std::make_shared<Terminal>(TokenType::SEMI));
            result.push_back(std::make_shared<NonTerminal>("FieldDecMore"));
        }
        break;
        // 25 26
    case NON_TERMINAL::FieldDecMore:
        TokenType type = token.getType();
        if (type == TokenType::END )
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (type == TokenType::INTEGER || type == CHAR || type == ARRAY)
        {
            result.push_back(std::make_shared<NonTerminal>("FieldDecList"));
        }
        break;
        //27
    case NON_TERMINAL::IdList:
        TokenType type = token.getType();
        if (type == TokenType::ID)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
            result.push_back(std::make_shared<NonTerminal>("IdMore"));
        }
        break;
        //28 29
    case NON_TERMINAL::IdMore:
        TokenType type = token.getType();
        if (type == TokenType::SEMI)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }else if(type == TokenType::COMMA){
            result.push_back(std::make_shared<Terminal>(TokenType::COMMA));
            result.push_back(std::make_shared<NonTerminal>("IdList"));
        }
        break;
        //30 31
        
    }
    return this->result;
}