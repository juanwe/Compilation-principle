#pragma once

#include"../../LexicalAnalysis/Token.h"
#include"../Tree/TreeNode.h"
#include"Symbol.h"

class Terminal : public Symbol{
private:
    TreeNode *node;
    Token *token;
public:
    Terminal(Token *token);
    Terminal(TokenType tokenType);
    TreeNode *getNode();

    Token *getToken();
    
    static Terminal *terFactory(TokenType tokenType);
};