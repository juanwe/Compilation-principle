#pragma once

#include"../../LexicalAnalysis/lexer.h"
#include"../../LexicalAnalysis/Token.h"
#include"../Tree/SyntaxTree.h"
#include"../Tree/TreeNode.h"
#include"NonTerminal.h"
#include"Symbol.h"
#include"NonTerminalEnum.h"

class LexParse{
private:
    std::list<Token> tokenList;
    int currentIndex = 0;
    std::string log_file_path = "./log/logfile.txt";
    
public:
    std::ofstream fileStream;
    LexParse();
    ~LexParse();
    //语法分析之前的词法分析工作
    void lexParse(std::string inPath);
    //用于匹配终结符和当前token列表头的token的类型
    TreeNode match(TokenType type);
    //通过预测分析表，查询该非终结符应该替换的列表
    std::vector<std::shared_ptr<Symbol>> find(NonTerminal symbol);
    //获取token列表中当前token，并将指针指向下一个token
    Token popToken();
    //获取token列表中指针当前指向的token
    Token peekToken();
};