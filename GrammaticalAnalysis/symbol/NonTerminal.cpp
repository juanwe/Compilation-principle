#include "NonTerminal.h"

NonTerminal::NonTerminal(std::string value) : value(value), node(new TreeNode(value)) {}

TreeNode *NonTerminal::getNode()
{
    return node;
}

std::string NonTerminal::getValue()
{
    return value;
}

bool NonTerminal::isBlank()
{
    return value == "blank";
}

NonTerminal *NonTerminal::nonFactory(std::string s)
{
    return new NonTerminal(s);
}
