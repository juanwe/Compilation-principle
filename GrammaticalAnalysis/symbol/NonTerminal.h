#pragma once

#include <string>
#include"../Tree/TreeNode.h"
#include"Symbol.h"

class NonTerminal : public Symbol
{
private:
    TreeNode *node;
    std::string value;

public:
    NonTerminal(std::string value);
    TreeNode *getNode();
    std::string getValue();
    bool isBlank();

    static NonTerminal *nonFactory(std::string s);
};