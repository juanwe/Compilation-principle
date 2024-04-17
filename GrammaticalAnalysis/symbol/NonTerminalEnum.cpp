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
    case NON_TERMINAL::VarDecpart:
        TokenType type = token.getType();
        if (type == TokenType::PROCEDURE||type==TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (type == TokenType::VAR)
        {
            result.push_back(std::make_shared<NonTerminal>("VarDec"));
        }
        break;
        //32
    case NON_TERMINAL::VarDec:
        TokenType type = token.getType();
        if (type == TokenType::VAR)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::VAR));
            result.push_back(std::make_shared<NonTerminal>("VarDecList"));
        }
        else if (type == TokenType::VAR)
        {
            result.push_back(std::make_shared<NonTerminal>("VarDec"));
        }
        break;
        //33
    case NON_TERMINAL::VarDecList:
        TokenType type = token.getType();
        if (type == TokenType::INTEGER || type == TokenType::CHAR || type == TokenType::ARRAY || type == TokenType::RECORD || type == TokenType::ID)
        {
            result.push_back(std::make_shared<NonTerminal>("TypeDef"));
            result.push_back(std::make_shared<NonTerminal>("VarIdList"));
            result.push_back(std::make_shared<Terminal>(TokenType::SEMI));
            result.push_back(std::make_shared<NonTerminal>("VarDecMore"));
        }
        break;
        //34 35
    case NON_TERMINAL::VarDecMore:
        TokenType type = token.getType();
        if (type == TokenType::PROCEDURE||type==TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (type == TokenType::INTEGER||type==TokenType::CHAR||type==TokenType::ARRAY||type==TokenType::RECORD||type==TokenType::ID)
        {
            result.push_back(std::make_shared<NonTerminal>("VarDecList"));
        }
        break;
        //36
    case NON_TERMINAL::VarIdList:
        TokenType type = token.getType();
        if (type == TokenType::ID )
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
            result.push_back(std::make_shared<NonTerminal>("VarIdMore"));
        }
        break;
        //37 38
    case NON_TERMINAL::VarIdMore:
        TokenType type = token.getType();
        if (type == TokenType::SEMI)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (type == TokenType::COMMA)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::COMMA));
            result.push_back(std::make_shared<NonTerminal>("VarIdList"));
        }
        break;
        //39 40
    case NON_TERMINAL::ProcDecpart:
        TokenType type = token.getType();
        if (type == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (type == TokenType::PROCEDURE)
        {
            result.push_back(std::make_shared<NonTerminal>("ProcDec"));
        }
        break;
        //41
    case NON_TERMINAL::ProcDec:
        TokenType type = token.getType();
        if (type == TokenType::PROCEDURE)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::PROCEDURE));
            result.push_back(std::make_shared<NonTerminal>("ProcName"));
            result.push_back(std::make_shared<Terminal>(TokenType::L_BRACKET));
            result.push_back(std::make_shared<NonTerminal>("ParamList"));
            result.push_back(std::make_shared<Terminal>(TokenType::R_BRACKET));
            result.push_back(std::make_shared<Terminal>(TokenType::SEMI));
            result.push_back(std::make_shared<NonTerminal>("ProcDecPart"));
            result.push_back(std::make_shared<NonTerminal>("ProcBody"));
            result.push_back(std::make_shared<NonTerminal>("ProcDecMore"));
        }
        break;
        //42 43
    case NON_TERMINAL::ProcDecMore:
        TokenType type = token.getType();
        if (type == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (type == TokenType::PROCEDURE)
        {
            result.push_back(std::make_shared<NonTerminal>("ProcDec"));
        }
        break;
        //44
    case NON_TERMINAL::ProcName:
        TokenType type = token.getType();
        if (type == TokenType::ID)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
        }
        break;
        //45 46
    case NON_TERMINAL::ProcDecMore:
        TokenType type = token.getType();
        if (type == TokenType::R_BRACKET)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (type == TokenType::VAR)
        {
            result.push_back(std::make_shared<NonTerminal>("ParamDecList"));
        }
        break;
        //47
    case NON_TERMINAL::ParamDecList:
        TokenType type = token.getType();
        if (type == TokenType::INTEGER || type == TokenType::CHAR || type == TokenType::ARRAY || type == TokenType::RECORD || type == TokenType::VAR || type == TokenType::ID)
        {
            result.push_back(std::make_shared<NonTerminal>("Param"));
            result.push_back(std::make_shared<NonTerminal>("ParamMore"));
        }
        break;
        // 48 49
    case NON_TERMINAL::ParamMore:
        TokenType type = token.getType();
        if (type == TokenType::R_BRACKET)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (type == TokenType::SEMI)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::SEMI));
            result.push_back(std::make_shared<NonTerminal>("ParamDecList"));
        }
        break;
        //50 51
    case NON_TERMINAL::Param:
        TokenType type = token.getType();
        if (type == TokenType::INTEGER || type == TokenType::CHAR || type == TokenType::ARRAY || type == TokenType::RECORD || type == TokenType::ID)
        {
            result.push_back(std::make_shared<NonTerminal>("TypeDef"));
            result.push_back(std::make_shared<NonTerminal>("FormList"));
        }
        else if (type == TokenType::VAR)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::VAR));
            result.push_back(std::make_shared<NonTerminal>("TypeDef"));
            result.push_back(std::make_shared<NonTerminal>("FormList"));
        }
        break;
        //52
    case NON_TERMINAL::FormList:
        TokenType type = token.getType();
        if (type == TokenType::ID)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
            result.push_back(std::make_shared<NonTerminal>("FidMore"));
        }
        break;
        //53 54
    case NON_TERMINAL::Param:
        TokenType type = token.getType();
        if (type == TokenType::R_BRACKET)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (type == TokenType::COMMA)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::COMMA));
            result.push_back(std::make_shared<NonTerminal>("FormList"));
        }
        break;
        //55
    case NON_TERMINAL::ProcDecPart:
        TokenType type = token.getType();
        if (type == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("DeclarePart"));
        }
        break;
        //56
    case NON_TERMINAL::ProcBody:
        TokenType type = token.getType();
        if (type == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("ProgramBody"));
        }
        break;
        //57
    case NON_TERMINAL::ProgramBody:
        TokenType type = token.getType();
        if (type == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::BEGIN));
            result.push_back(std::make_shared<NonTerminal>("StmList"));
            result.push_back(std::make_shared<Terminal>(TokenType::END));
        }
        break;
        //58
    case NON_TERMINAL::StmList:
        TokenType type = token.getType();
        if (type == TokenType::WRITE)
        {
            result.push_back(std::make_shared<NonTerminal>("Stm"));
            result.push_back(std::make_shared<NonTerminal>("StmMore"));
        }
        break;
        //59 60
    case NON_TERMINAL::StmMore:
        TokenType type = token.getType();
        if (type == TokenType::ENDWH)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (type == TokenType::SEMI)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::SEMI));
            result.push_back(std::make_shared<NonTerminal>("StmList"));
        }
        break;
        //61 62 63 64 65 66
    case NON_TERMINAL::Stm:
        TokenType type = token.getType();
        switch(type){
            case TokenType::IF:
                result.push_back(std::make_shared<NON_TERMINAL>("ConditionalStm"));
                break;
            case TokenType::WHILE:
                result.push_back(std::make_shared<NON_TERMINAL>("LoopStm"));
                break;
            case TokenType::READ:
                result.push_back(std::make_shared<NON_TERMINAL>("InputStm"));
                break;
            case TokenType::WRITE:
                result.push_back(std::make_shared<NON_TERMINAL>("OutputStm"));
                break;
            case TokenType::RETURN:
                result.push_back(std::make_shared<NON_TERMINAL>("ReturnStm"));
                break;
            case TokenType::ID:
                result.push_back(std::make_shared<Terminal>(TokenType::ID));
                result.push_back(std::make_shared<NON_TERMINAL>("AssCall"));
                break;
            default:
                break;
        }
        break;
        //67 68
    case NON_TERMINAL::AssCall:
        TokenType type = token.getType();
        if (type == TokenType::ASSIGN)
        {
            result.push_back(std::make_shared<NonTerminal>("AssignmentRest"));
        }
        else if (type == TokenType::LPAREN)
        {
            result.push_back(std::make_shared<NonTerminal>("CallStmRest"));
        }
        break;
        //69
    case NON_TERMINAL::AssignmentRest:
        TokenType type = token.getType();
        if (type == TokenType::ASSIGN)
        {
            result.push_back(std::make_shared<NonTerminal>("VariMore"));
            result.push_back(std::make_shared<Terminal>(TokenType::ASSIGN));
            result.push_back(std::make_shared<NonTerminal>("Exp"));
        }
        break;
        //70 条件语句
    case NON_TERMINAL::ConditionalStm:
        TokenType type = token.getType();
        if (type == TokenType::IF)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::IF));
            result.push_back(std::make_shared<NonTerminal>("RelExp"));
            result.push_back(std::make_shared<Terminal>(TokenType::THEN));
            result.push_back(std::make_shared<NonTerminal>("StmList"));
            result.push_back(std::make_shared<Terminal>(TokenType::ELSE));
            result.push_back(std::make_shared<NonTerminal>("StmList"));
            result.push_back(std::make_shared<Terminal>(TokenType::FI));
        }
        break;
        //71 循环语句
    case NON_TERMINAL::LoopStm:
        TokenType type = token.getType();
        if (type == TokenType::WHILE)
        {

            result.push_back(std::make_shared<Terminal>(TokenType::WHILE));
            result.push_back(std::make_shared<NonTerminal>("RelExp"));
            result.push_back(std::make_shared<Terminal>(TokenType::DO));
            result.push_back(std::make_shared<NonTerminal>("StmList"));
            result.push_back(std::make_shared<Terminal>(TokenType::ENDWH));
        }
        break;
        // 72
    case NON_TERMINAL::InputStm:
        TokenType type = token.getType();
        if (type == TokenType::READ)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::READ));
            result.push_back(std::make_shared<Terminal>(TokenType::L_BRACKET));
            result.push_back(std::make_shared<NonTerminal>("Invar"));
            result.push_back(std::make_shared<Terminal>(TokenType::R_BRACKET));
        }
        break;
        // 73
    case NON_TERMINAL::Invar:
        TokenType type = token.getType();
        if (type == TokenType::ID)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
        }
        break;
        // 74
    }
    return this->result;
}