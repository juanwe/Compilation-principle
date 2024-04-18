#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include "../../LexicalAnalysis/Token.h"
#include "Symbol.h"
#include"Terminal.h"
#include"NonTerminal.h"

enum class NON_TERMINAL
{
    Program,
    ProgramHead,
    ProgramName,
    DeclarePart,
    TypeDecpart,
    TypeDec,
    TypeDecList,
    TypeDecMore,
    TypeId,
    TypeDef,
    BaseType,
    StructureType,
    ArrayType,
    Low,
    Top,
    RecType,
    FieldDecList,
    FieldDecMore,
    IdList,
    IdMore,
    VarDecpart,
    VarDec,
    VarDecList,
    VarDecMore,
    VarIdList,
    VarIdMore,
    ProcDecpart,
    ProcDec,
    ProcDecMore,
    ProcName,
    ParamList,
    ParamDecList,
    ParamMore,
    Param,
    FormList,
    FidMore,
    ProcDecPart,
    ProcBody,
    ProgramBody,
    StmList,
    StmMore,
    Stm,
    AssCall,
    AssignmentRest,
    ConditionalStm,
    LoopStm,
    InputStm,
    Invar,
    OutputStm,
    ReturnStm,
    CallStmRest,
    ActParamList,
    ActParamMore,
    RelExp,
    OtherRelE,
    Exp,
    OtherTerm,
    Term,
    OtherFactor,
    Factor,
    Variable,
    VariMore,
    FieldVar,
    FieldVarMore,
    CmpOp,
    AddOp,
    MultOp
};
// 将字符串映射到枚举值的函数
NON_TERMINAL stringToNON_TERMINAL(const std::string &str);
// 枚举值的预测规则类
class NonTerminalEnum
{
public:
    NonTerminalEnum(NON_TERMINAL type);

    std::vector<std::shared_ptr<Symbol>> predict(Token token);

private:
    NON_TERMINAL type;
    std::vector<std::shared_ptr<Symbol>> result;
};