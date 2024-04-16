#pragma once

#include <vector>
#include <memory>
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
    VarDecList
};

// 枚举值的预测规则类
class NonTerminalEnum
{
public:
    NonTerminalEnum(NON_TERMINAL type, const NonTerminal &nonTerminal);

    std::vector<std::shared_ptr<Symbol>> predict(Token token);

private:
    NON_TERMINAL type;
    NonTerminal nonTerminal;
    std::vector<std::shared_ptr<Symbol>> result;
};