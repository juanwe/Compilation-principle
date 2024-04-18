#include "NonTerminalEnum.h"
#include "NonTerminal.h"
#include "Terminal.h"

// 构造函数
NonTerminalEnum::NonTerminalEnum(NON_TERMINAL type) : type(type){}

// 预测方法
std::vector<std::shared_ptr<Symbol>> NonTerminalEnum::predict(Token token)
{
    TokenType t = token.getType();
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
        
        if (t == TokenType::TYPE || t == TokenType::VAR || t == TokenType::PROCEDURE || t == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("TypeDecpart"));
            result.push_back(std::make_shared<NonTerminal>("VarDecpart"));
            result.push_back(std::make_shared<NonTerminal>("ProcDecpart"));
        }
        break;
        //5 6
    case NON_TERMINAL::TypeDecpart:
        if(t == TokenType::VAR||t==TokenType::PROCEDURE||t==TokenType::BEGIN){
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }else if(t==TokenType::TYPE){
            result.push_back(std::make_shared<NonTerminal>("TypeDec"));
        }
        break;
        //7
    case NON_TERMINAL::TypeDec:
        if (t == TokenType::TYPE)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::TYPE));
            result.push_back(std::make_shared<NonTerminal>("TypeDecList"));
        }
        break;
        //8
    case NON_TERMINAL::TypeDecList:
        if (t == TokenType::ID)
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
        if (t == TokenType::VAR || t == TokenType::PROCEDURE || t == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }else if(t==TokenType::ID){
            result.push_back(std::make_shared<NonTerminal>("TypeDecList"));
        }
        break;
        //11
    case NON_TERMINAL::TypeId:
        if (t == TokenType::ID )
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
        }
        break;
        //12 13 14
    case NON_TERMINAL::TypeDef:
        if (t == TokenType::INTEGER || t == TokenType::CHAR)
        {
            result.push_back(std::make_shared<NonTerminal>("BaseType"));
        }
        else if (t == TokenType::ARRAY||t==TokenType::RECORD)
        {
            result.push_back(std::make_shared<NonTerminal>("StructureType"));
        }else if(t==TokenType::ID){
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
        }
        break;
        //15 16
    case NON_TERMINAL::BaseType:
        if (t == TokenType::INTEGER)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::INTEGER));
        }
        else if (t == TokenType::CHAR)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::CHAR));
        }
        break;
        //17 18
    case NON_TERMINAL::StructureType:
        if (t == TokenType::ARRAY)
        {
            result.push_back(std::make_shared<NonTerminal>("ArrayType"));
        }
        else if (t == TokenType::RECORD)
        {
            result.push_back(std::make_shared<NonTerminal>("RecType"));
        }
        break;
        //19
    case NON_TERMINAL::ArrayType:
        if (t == TokenType::ARRAY)
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
        if (t == TokenType::INTC)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::INTC));
        }
        break;
        //21
    case NON_TERMINAL::Top:
        if (t == TokenType::INTC)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::INTC));
        }
        break;
        //22
    case NON_TERMINAL::RecType:
        if (t == TokenType::RECORD)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::RECORD));
            result.push_back(std::make_shared<NonTerminal>("FieldDecList"));
            result.push_back(std::make_shared<Terminal>(TokenType::END));
        }
        break;
        //23 24
    case NON_TERMINAL::FieldDecList:
        if (t == TokenType::INTEGER || t == TokenType::CHAR)
        {
            result.push_back(std::make_shared<NonTerminal>("BaseType"));
            result.push_back(std::make_shared<NonTerminal>("IdList"));
            result.push_back(std::make_shared<Terminal>(TokenType::SEMI));
            result.push_back(std::make_shared<NonTerminal>("FieldDecMore"));
        }
        else if (t == TokenType::ARRAY)
        {
            result.push_back(std::make_shared<NonTerminal>("ArrayType"));
            result.push_back(std::make_shared<NonTerminal>("IdList"));
            result.push_back(std::make_shared<Terminal>(TokenType::SEMI));
            result.push_back(std::make_shared<NonTerminal>("FieldDecMore"));
        }
        break;
        // 25 26
    case NON_TERMINAL::FieldDecMore:
        if (t == TokenType::END )
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::INTEGER || t == TokenType::CHAR || t == TokenType::ARRAY)
        {
            result.push_back(std::make_shared<NonTerminal>("FieldDecList"));
        }
        break;
        //27
    case NON_TERMINAL::IdList:
        if (t == TokenType::ID)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
            result.push_back(std::make_shared<NonTerminal>("IdMore"));
        }
        break;
        //28 29
    case NON_TERMINAL::IdMore:
        if (t == TokenType::SEMI)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }else if(t == TokenType::COMMA){
            result.push_back(std::make_shared<Terminal>(TokenType::COMMA));
            result.push_back(std::make_shared<NonTerminal>("IdList"));
        }
        break;
        //30 31
    case NON_TERMINAL::VarDecpart:
        if (t == TokenType::PROCEDURE||t==TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::VAR)
        {
            result.push_back(std::make_shared<NonTerminal>("VarDec"));
        }
        break;
        //32
    case NON_TERMINAL::VarDec:
        if (t == TokenType::VAR)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::VAR));
            result.push_back(std::make_shared<NonTerminal>("VarDecList"));
        }
        else if (t == TokenType::VAR)
        {
            result.push_back(std::make_shared<NonTerminal>("VarDec"));
        }
        break;
        //33
    case NON_TERMINAL::VarDecList:
        if (t == TokenType::INTEGER || t == TokenType::CHAR || t == TokenType::ARRAY || t == TokenType::RECORD || t == TokenType::ID)
        {
            result.push_back(std::make_shared<NonTerminal>("TypeDef"));
            result.push_back(std::make_shared<NonTerminal>("VarIdList"));
            result.push_back(std::make_shared<Terminal>(TokenType::SEMI));
            result.push_back(std::make_shared<NonTerminal>("VarDecMore"));
        }
        break;
        //34 35
    case NON_TERMINAL::VarDecMore:
        if (t == TokenType::PROCEDURE||t==TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::INTEGER||t==TokenType::CHAR||t==TokenType::ARRAY||t==TokenType::RECORD||t==TokenType::ID)
        {
            result.push_back(std::make_shared<NonTerminal>("VarDecList"));
        }
        break;
        //36
    case NON_TERMINAL::VarIdList:
        if (t == TokenType::ID )
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
            result.push_back(std::make_shared<NonTerminal>("VarIdMore"));
        }
        break;
        //37 38
    case NON_TERMINAL::VarIdMore:
        if (t == TokenType::SEMI)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::COMMA)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::COMMA));
            result.push_back(std::make_shared<NonTerminal>("VarIdList"));
        }
        break;
        //39 40
    case NON_TERMINAL::ProcDecpart:
        if (t == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::PROCEDURE)
        {
            result.push_back(std::make_shared<NonTerminal>("ProcDec"));
        }
        break;
        //41
    case NON_TERMINAL::ProcDec:
        if (t == TokenType::PROCEDURE)
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
        if (t == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::PROCEDURE)
        {
            result.push_back(std::make_shared<NonTerminal>("ProcDec"));
        }
        break;
        //44
    case NON_TERMINAL::ProcName:
        if (t == TokenType::ID)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
        }
        break;
        //45 46
    case NON_TERMINAL::ParamList:
        if (t == TokenType::R_BRACKET)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::VAR)
        {
            result.push_back(std::make_shared<NonTerminal>("ParamDecList"));
        }
        break;
        //47
    case NON_TERMINAL::ParamDecList:
        if (t == TokenType::INTEGER || t == TokenType::CHAR || t == TokenType::ARRAY || t == TokenType::RECORD || t == TokenType::VAR || t == TokenType::ID)
        {
            result.push_back(std::make_shared<NonTerminal>("Param"));
            result.push_back(std::make_shared<NonTerminal>("ParamMore"));
        }
        break;
        // 48 49
    case NON_TERMINAL::ParamMore:
        if (t == TokenType::R_BRACKET)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::SEMI)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::SEMI));
            result.push_back(std::make_shared<NonTerminal>("ParamDecList"));
        }
        break;
        //50 51
    case NON_TERMINAL::Param:
        if (t == TokenType::INTEGER || t == TokenType::CHAR || t == TokenType::ARRAY || t == TokenType::RECORD || t == TokenType::ID)
        {
            result.push_back(std::make_shared<NonTerminal>("TypeDef"));
            result.push_back(std::make_shared<NonTerminal>("FormList"));
        }
        else if (t == TokenType::VAR)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::VAR));
            result.push_back(std::make_shared<NonTerminal>("TypeDef"));
            result.push_back(std::make_shared<NonTerminal>("FormList"));
        }
        break;
        //52
    case NON_TERMINAL::FormList:
        if (t == TokenType::ID)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
            result.push_back(std::make_shared<NonTerminal>("FidMore"));
        }
        break;
        //53 54
    case NON_TERMINAL::FidMore:
        if (t == TokenType::R_BRACKET)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::COMMA)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::COMMA));
            result.push_back(std::make_shared<NonTerminal>("FormList"));
        }
        break;
        //55
    case NON_TERMINAL::ProcDecPart:
        if (t == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("DeclarePart"));
        }
        break;
        //56
    case NON_TERMINAL::ProcBody:
        if (t == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<NonTerminal>("ProgramBody"));
        }
        break;
        //57
    case NON_TERMINAL::ProgramBody:
        if (t == TokenType::BEGIN)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::BEGIN));
            result.push_back(std::make_shared<NonTerminal>("StmList"));
            result.push_back(std::make_shared<Terminal>(TokenType::END));
        }
        break;
        //58
    case NON_TERMINAL::StmList:
        if (t == TokenType::WRITE)
        {
            result.push_back(std::make_shared<NonTerminal>("Stm"));
            result.push_back(std::make_shared<NonTerminal>("StmMore"));
        }
        break;
        //59 60
    case NON_TERMINAL::StmMore:
        if (t == TokenType::ENDWH)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::SEMI)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::SEMI));
            result.push_back(std::make_shared<NonTerminal>("StmList"));
        }
        break;
        //61 62 63 64 65 66
    case NON_TERMINAL::Stm:
        switch(t){
            case TokenType::IF:
                result.push_back(std::make_shared<NonTerminal>("ConditionalStm"));
                break;
            case TokenType::WHILE:
                result.push_back(std::make_shared<NonTerminal>("LoopStm"));
                break;
            case TokenType::READ:
                result.push_back(std::make_shared<NonTerminal>("InputStm"));
                break;
            case TokenType::WRITE:
                result.push_back(std::make_shared<NonTerminal>("OutputStm"));
                break;
            case TokenType::RETURN:
                result.push_back(std::make_shared<NonTerminal>("ReturnStm"));
                break;
            case TokenType::ID:
                result.push_back(std::make_shared<Terminal>(TokenType::ID));
                result.push_back(std::make_shared<NonTerminal>("AssCall"));
                break;
            default:
                break;
        }
        break;
        //67 68
    case NON_TERMINAL::AssCall:
        if (t == TokenType::ASSIGN)
        {
            result.push_back(std::make_shared<NonTerminal>("AssignmentRest"));
        }
        else if (t == TokenType::L_BRACKET)
        {
            result.push_back(std::make_shared<NonTerminal>("CallStmRest"));
        }
        break;
        //69
    case NON_TERMINAL::AssignmentRest:
        if (t == TokenType::ASSIGN)
        {
            result.push_back(std::make_shared<NonTerminal>("VariMore"));
            result.push_back(std::make_shared<Terminal>(TokenType::ASSIGN));
            result.push_back(std::make_shared<NonTerminal>("Exp"));
        }
        break;
        //70 条件语句
    case NON_TERMINAL::ConditionalStm:
        if (t == TokenType::IF)
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
        if (t == TokenType::WHILE)
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
        if (t == TokenType::READ)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::READ));
            result.push_back(std::make_shared<Terminal>(TokenType::L_BRACKET));
            result.push_back(std::make_shared<NonTerminal>("Invar"));
            result.push_back(std::make_shared<Terminal>(TokenType::R_BRACKET));
        }
        break;
        // 73
    case NON_TERMINAL::Invar:
        if (t == TokenType::ID)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
        }
        break;
        // 74
    case NON_TERMINAL::OutputStm:
        if (t == TokenType::WRITE)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::WRITE));
            result.push_back(std::make_shared<Terminal>(TokenType::L_BRACKET));
            result.push_back(std::make_shared<NonTerminal>("Exp"));
            result.push_back(std::make_shared<Terminal>(TokenType::R_BRACKET));
        }
        break;
        //75
    case NON_TERMINAL::ReturnStm:
        if (t == TokenType::RETURN)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::RETURN));
        }
        break;
        //76
    case NON_TERMINAL::CallStmRest:
        if (t == TokenType::L_BRACKET)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::L_BRACKET));
            result.push_back(std::make_shared<NonTerminal>("ActParamList"));
            result.push_back(std::make_shared<Terminal>(TokenType::R_BRACKET));
        }
        break;
        //77 78
    case NON_TERMINAL::ActParamList:
        if (t == TokenType::R_BRACKET)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }else if(t==TokenType::ID){
            result.push_back(std::make_shared<NonTerminal>("Exp"));
            result.push_back(std::make_shared<NonTerminal>("ActParamMore"));
        }
        break;
        //79 80
    case NON_TERMINAL::ActParamMore:
        if (t == TokenType::R_BRACKET)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::COMMA)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::COMMA));
            result.push_back(std::make_shared<NonTerminal>("ActParamList"));
        }
        break;
        //81
    case NON_TERMINAL::RelExp:
        if (t == TokenType::ID)
        {
            result.push_back(std::make_shared<NonTerminal>("Exp"));
            result.push_back(std::make_shared<NonTerminal>("OtherRelE"));
        }
        break;
        //82
    case NON_TERMINAL::OtherRelE:
        if (t == TokenType::EQ||t==TokenType::LT)
        {
            result.push_back(std::make_shared<NonTerminal>("CmpOp"));
            result.push_back(std::make_shared<NonTerminal>("Exp"));
        }
        break;
        //83
    case NON_TERMINAL::Exp:
        if (t == TokenType::ID)
        {
            result.push_back(std::make_shared<NonTerminal>("Term"));
            result.push_back(std::make_shared<NonTerminal>("OtherTerm"));
        }
        break;
        //84 85
    case NON_TERMINAL::OtherTerm:
        if (t == TokenType::COMMA)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::MINUS)
        {
            result.push_back(std::  make_shared<NonTerminal>("AddOp"));
            result.push_back(std:: make_shared<NonTerminal>("Exp"));
        }
        break;
        //86
    case NON_TERMINAL::Term:
        if (t == TokenType::ID)
        {
            result.push_back(std::make_shared<NonTerminal>("Factor"));
            result.push_back(std::make_shared<NonTerminal>("OtherFactor"));
        }
        break;
        //87 88
    case NON_TERMINAL::OtherFactor:
        if (t == TokenType::COMMA)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::DIVISION)
        {
            result.push_back(std:: make_shared<NonTerminal>("MultOp"));
            result.push_back(std:: make_shared<NonTerminal>("Term"));
        }
        break;
        //89 90 91
    case NON_TERMINAL::Factor:
        if (t == TokenType::L_BRACKET)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::L_BRACKET));
            result.push_back(std::make_shared<NonTerminal>("Exp"));
            result.push_back(std::make_shared<Terminal>(TokenType::R_BRACKET));
        }
        else if (t == TokenType::INTC)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::INTC));
        }else if(t==TokenType::ID){
            result.push_back(std::make_shared<NonTerminal>("Variable"));
        }
        break;
        //92
    case NON_TERMINAL::Variable:
        if (t == TokenType::ID)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::ID));
            result.push_back(std::make_shared<NonTerminal>("VariMore"));
        }
        break;
        //93 94 95
    case NON_TERMINAL::VariMore:
        if (t == TokenType::COMMA)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::L_S_BRACKETS)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::L_S_BRACKETS));
            result.push_back(std::make_shared<NonTerminal>("Exp"));
            result.push_back(std::make_shared<Terminal>(TokenType::R_S_BRACKET));
        }
        else if (t == TokenType::DOT)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::DOT));
            result.push_back(std::make_shared<NonTerminal>("FieldVar"));
        }
        break;
        //97 98
    case NON_TERMINAL::FieldVarMore:
        if (t == TokenType::COMMA)
        {
            result.push_back(std::make_shared<NonTerminal>("blank"));
        }
        else if (t == TokenType::L_S_BRACKETS)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::L_S_BRACKETS));
            result.push_back(std::make_shared<NonTerminal>("Exp"));
            result.push_back(std::make_shared<Terminal>(TokenType::R_S_BRACKET));
        }
        break;
        //99 100
    case NON_TERMINAL::CmpOp:
        if (t == TokenType::LT)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::LT));
        }
        else if (t == TokenType::EQ)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::EQ));
        }
        break;
        //101 102
    case NON_TERMINAL::AddOp:
        if (t == TokenType::PLUS)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::PLUS));
        }
        else if (t == TokenType::MINUS)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::MINUS));
        }
        break;
        //103 104
    case NON_TERMINAL::MultOp:
        if (t == TokenType::MULTIPLE)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::PLUS));
        }
        else if (t == TokenType::DIVISION)
        {
            result.push_back(std::make_shared<Terminal>(TokenType::DIVISION));
        }
        break;
    }
    return this->result;
}

NON_TERMINAL stringToNON_TERMINAL(const std::string &str)
{
    static const std::unordered_map<std::string, NON_TERMINAL> enumMap = {
        {"Program", NON_TERMINAL::Program},
        {"ProgramHead", NON_TERMINAL::ProgramHead},
        {"ProgramName", NON_TERMINAL::ProgramName},
        {"DeclarePart", NON_TERMINAL::DeclarePart},
        {"TypeDecpart", NON_TERMINAL::TypeDecpart},
        {"TypeDec", NON_TERMINAL::TypeDec},
        {"TypeDecList", NON_TERMINAL::TypeDecList},
        {"TypeDecMore", NON_TERMINAL::TypeDecMore},
        {"TypeId", NON_TERMINAL::TypeId},
        {"TypeDef", NON_TERMINAL::TypeDef},
        {"BaseType", NON_TERMINAL::BaseType},
        {"StructureType", NON_TERMINAL::StructureType},
        {"ArrayType", NON_TERMINAL::ArrayType},
        {"Low", NON_TERMINAL::Low},
        {"Top", NON_TERMINAL::Top},
        {"RecType", NON_TERMINAL::RecType},
        {"FieldDecList", NON_TERMINAL::FieldDecList},
        {"FieldDecMore", NON_TERMINAL::FieldDecMore},
        {"IdList", NON_TERMINAL::IdList},
        {"IdMore", NON_TERMINAL::IdMore},
        {"VarDecpart", NON_TERMINAL::VarDecpart},
        {"VarDec", NON_TERMINAL::VarDec},
        {"VarDecList", NON_TERMINAL::VarDecList},
        {"VarDecMore", NON_TERMINAL::VarDecMore},
        {"VarIdList", NON_TERMINAL::VarIdList},
        {"VarIdMore", NON_TERMINAL::VarIdMore},
        {"ProcDecpart", NON_TERMINAL::ProcDecpart},
        {"ProcDec", NON_TERMINAL::ProcDec},
        {"ProcDecMore", NON_TERMINAL::ProcDecMore},
        {"ProcName", NON_TERMINAL::ProcName},
        {"ParamList", NON_TERMINAL::ParamList},
        {"ParamDecList", NON_TERMINAL::ParamDecList},
        {"ParamMore", NON_TERMINAL::ParamMore},
        {"Param", NON_TERMINAL::Param},
        {"FormList", NON_TERMINAL::FormList},
        {"FidMore", NON_TERMINAL::FidMore},
        {"ProcDecPart", NON_TERMINAL::ProcDecPart},
        {"ProcBody", NON_TERMINAL::ProcBody},
        {"ProgramBody", NON_TERMINAL::ProgramBody},
        {"StmList", NON_TERMINAL::StmList},
        {"StmMore", NON_TERMINAL::StmMore},
        {"Stm", NON_TERMINAL::Stm},
        {"AssCall", NON_TERMINAL::AssCall},
        {"AssignmentRest", NON_TERMINAL::AssignmentRest},
        {"ConditionalStm", NON_TERMINAL::ConditionalStm},
        {"LoopStm", NON_TERMINAL::LoopStm},
        {"InputStm", NON_TERMINAL::InputStm},
        {"Invar", NON_TERMINAL::Invar},
        {"OutputStm", NON_TERMINAL::OutputStm},
        {"ReturnStm", NON_TERMINAL::ReturnStm},
        {"CallStmRest", NON_TERMINAL::CallStmRest},
        {"ActParamList", NON_TERMINAL::ActParamList},
        {"ActParamMore", NON_TERMINAL::ActParamMore},
        {"RelExp", NON_TERMINAL::RelExp},
        {"OtherRelE", NON_TERMINAL::OtherRelE},
        {"Exp", NON_TERMINAL::Exp},
        {"OtherTerm", NON_TERMINAL::OtherTerm},
        {"Term", NON_TERMINAL::Term},
        {"OtherFactor", NON_TERMINAL::OtherFactor},
        {"Factor", NON_TERMINAL::Factor},
        {"Variable", NON_TERMINAL::Variable},
        {"VariMore", NON_TERMINAL::VariMore},
        {"FieldVar", NON_TERMINAL::FieldVar},
        {"FieldVarMore", NON_TERMINAL::FieldVarMore},
        {"CmpOp", NON_TERMINAL::CmpOp},
        {"AddOp", NON_TERMINAL::AddOp},
        {"MultOp", NON_TERMINAL::MultOp}};
    auto it = enumMap.find(str);
    if (it != enumMap.end())
    {
        return it->second;
    }
    else
    {
        throw std::invalid_argument("Invalid NON_TERMINAL string");
    }
}