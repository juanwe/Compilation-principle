#pragma once

#include <string>
#include <array>

//词法单元

enum TokenType{
    // 错误
    ERROR=0,
    // 标识符，包含变量名，类型名，过程名，保留字等
    ID,
    // 保留字
    PROGRAM,PROCEDURE, TYPE, VAR,IF,THEN,ELSE,FI,
    WHILE,DO,ENDWH,BEGIN,END,
    READ,WRITE,OF,RETURN,
    // 类型
    INTEGER,CHAR,ARRAY,RECORD,INTC,
    // 单字符分界符
    EQ,LT,_EOF_,EMPTY,PLUS,MINUS,MULTIPLE,DIVISION,
    L_BRACKET,R_BRACKET,L_S_BRACKETS,R_S_BRACKET,
    SEMI,COMMA,DOT,
    // 双字符分界符
    ASSIGN,ARRAY_BOUNDS
};
//与枚举值相关联的字符串
const std::array<const char *, 41>TokenTypeToString{
    
    "error",

    "id",

    "program", "procedure", "type", "var", "if", "then", "else", "fi",
    "while", "do", "endwh", "begin", "end",
    "read", "write", "of", "return",
    
    "integer", "char", "array", "record", "inic",
    
    "=", "<", ".", " ", "+", "-", "*", "/",
    "(", ")", "[", "]",
    ";", ",", ".",
    
    ":=", ".."
};
//将字符串转化为对应的枚举值方法
TokenType stringToTokenType(const std::string& str);

//token结构类
class Token{
private:
    int line; //行
    int column; //列
    TokenType type; //类型
    std::string value; //读入的值
public:
    Token();
    Token(TokenType type);
    Token(int line, int colum, TokenType type, std::string value);
    //如果输入的标识符是保留字就把它转换成相应的类型
    void checkKeyWord();

    //常规get函数
    int getLine();
    int getColumn();
    TokenType getType();
    std::string getValue();
    //输出类中内容
    std::string toString();
};
