#include "Terminal.h"

Terminal::Terminal(Token *token) : token(token), node(new TreeNode(token->getValue())) {}
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
