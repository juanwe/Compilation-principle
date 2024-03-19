#pragma once

#include <fstream>
#include <string>
#include <list>
#include<iostream>
#include "Token.h"

class LexerResult
{
private:
    std::list<Token> tokenList;

public:
    std::list<Token> getTokenList();
    void setTokenList(std::list<Token> tokenList);
};
class Lexer
{
private:
    // 状态
    enum StateEnum
    {
        NORMAL,     // 初始
        IN_ID,      // 标识符
        IN_NUM,     // 数字
        IN_ASSIGN,  // 赋值
        IN_COMMENT, // 注释
        IN_DOT,     // 点
        IN_RANGE,   // 数组下标界限
        IN_CHAR,    // 字符标志
        ERROR       // 出错
    };

    std::string log_file_path = "./log/logfile.txt";
    int line = 1;
    int column = 0;
    int backtraceNumber = -1;
    bool lf = false;
    std::ifstream fileStream;

public:
    Lexer(std::ifstream&& fileStream);
    // 返回词法分析的结果
    LexerResult getResult();
    // 词法分析的直接转向法
    Token getToken();
    // 回溯字符
    void backTrackChar(int ch);
    // 取得下一个字符
    int getChar();
    // 显示回车等字符，用于日志记录
    std::string showChar(int ch);

    // 判断是否为字母
    bool isAlpha(int ch);
    // 判断是否为数字
    bool isDigit(int ch);
    // 判断是否为空格、制表符、回车符、换行符
    bool isBlank(int ch);
};