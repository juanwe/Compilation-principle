#include "Terminal.h"

Terminal::Terminal(Token *token) : token(token), node(new TreeNode(token->getValue())) {}
Terminal::Terminal(TokenType TokenType){
    Terminal(new Token(TokenType, true));
}
Token *Terminal::getToken()
{
    return token;
}
TreeNode *Terminal::getNode()
{
    return node;
}
Terminal *Terminal::terFactory(TokenType tokenType)
{
    return new Terminal(new Token(tokenType, true));
}
