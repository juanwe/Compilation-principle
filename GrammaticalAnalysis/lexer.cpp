#include "lexer.h"

std::list<Token> LexerResult::getTokenList() { return tokenList; }
void LexerResult::setTokenList(std::list<Token> tokenList) { this->tokenList = tokenList; }

Lexer::Lexer(std::ifstream &&fileStream) : fileStream(std::move(fileStream))
{
}
LexerResult Lexer::getResult()
{
    LexerResult result;
    std::list<Token> tokenList;

    std::ofstream logFile(this->log_file_path, std::ios::app);
    if (!logFile.is_open())
    {
        std::cerr << "无法打开日志文件" << log_file_path << std::endl;
        result.setTokenList(tokenList);
        return result;
    }

    if (fileStream.is_open())
    {
        if (fileStream.peek() == EOF)
        {
            logFile << "字符输入流为空" << std::endl;
            logFile.close();
            result.setTokenList(tokenList);
            return result;
        }

        Token token = getToken();
        while (token.isValidObject())
        {
            tokenList.push_back(token);
            token = getToken();
        }
        result.setTokenList(tokenList);
        logFile.close();
        fileStream.close();
        return result;
    }
    else
    {
        logFile << "无法打开字符输入流" << std::endl;
        logFile.close();
        result.setTokenList(tokenList);
        return result;
    }
}

Token Lexer::getToken()
{
    std::ofstream fileStream(log_file_path);
    if (!fileStream.is_open())
    {
        std::cerr << "Failed to open the file" << std::endl;
    }
    fileStream << "调用getToken方法" << std::endl;

    StateEnum stateEnum = NORMAL;
    std::string s;
    int dotLine = 0, dotColumn = 0;
    int ch = getChar();
    while (ch != -1)
    {
        s.append(1, (char)ch);
        Token token;
        switch (stateEnum)
        {
        case NORMAL:
            break;
        case IN_ID:
            break;
        case IN_NUM:
            break;
        case IN_ASSIGN:
            break;
        case IN_COMMENT:
            break;
        case DOT:
            break;
        case IN_RANGE:
            break;
        case IN_CHAR:
            break;
        case ERROR:
            break;
        default:
            stateEnum = ERROR;
            break;
        }
        ch = getchar();
    }
    if (stateEnum != NORMAL)
    {
        fileStream << "[错误]在" << line << "行" << column << "列" << std::endl;
    }
    fileStream.close();
    return new Token();
}

int Lexer::getChar()
{
    int ch;
    if (backtraceNumber != -1 && backtraceNumber != ' ' && backtraceNumber != '\r' && backtraceNumber != '\n')
    {
        ch = backtraceNumber;
        backtraceNumber = -1;
    }
    else if (backtraceNumber == ' ' || backtraceNumber == '\t')
    {
        column++;
        backtraceNumber = -1;
        ch = fileStream.get();
    }
    else
    {
        fileStream.get();
    }

    if (lf)
    {
        column = 0;
        line++;
    }
    if (ch == '\n')
    {
        lf = true;
        column++;
    }
    else if (ch != -1)
    {
        column++;
        lf = false;
    }
    std::ofstream fileStream(log_file_path);
    if (!fileStream.is_open())
    {
        std::cerr << "Failed to open the file" << std::endl;
    }
    fileStream << "当前字符是：\""
               << showChar(ch) << '(' << ch << ')'
               << '[' << line << ':' << column << ']' << std::endl;
    fileStream.close();
    return ch;
}
std::string Lexer::showChar(int ch)
{
    if (ch == '\n')
    {
        return "\\n";
    }
    else if (ch == '\r')
    {
        return "\\r";
    }
    else
        return "" + (char)ch;
}

bool Lexer::isAlpha(int ch)
{
    return (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z');
}
bool Lexer::isDigit(int ch)
{
    return (ch >= '0' && ch <= '9');
}
bool Lexer::isBlank(int ch)
{
    return (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t');
}