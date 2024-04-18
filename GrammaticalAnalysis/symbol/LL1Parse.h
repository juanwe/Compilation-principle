#pragma once
// LL1，自顶向下的非递归分析

#include <stack>
#include<vector>
#include<memory>

#include "NonTerminal.h"
#include "Symbol.h"
#include "Terminal.h"
#include "../Tree/TreeNode.h"
#include "../Tree/SyntaxTree.h"
#include"LexParse.h"

class LL1Parse : public LexParse
{
private:
    SyntaxTree* syntaxTree;

public:
    SyntaxTree* syntaxParse();
};
