#include<fstream>
#include<string>
class Lexer{
private:
    //状态
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
    }

    std::string log_file_path = "logfile.txt";
    
}
