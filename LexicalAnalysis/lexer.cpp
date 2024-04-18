#include "lexer.h"

std::list<Token> LexerResult::getTokenList() { return tokenList; }
void LexerResult::setTokenList(std::list<Token> tokenList) { this->tokenList = tokenList; }

Lexer::Lexer(std::string filename)
{
    std::ofstream logFile(this->log_file_path, std::ios::app);
    if (!logFile.is_open())
    {
        std::cerr << "无法打开日志文件" << log_file_path << std::endl;
    }
    this->filename = filename;
    std::ifstream FS(this->filename);
    if (!FS.is_open())
    {
        logFile << "无法打开字符输入流" << std::endl;
    }else{
        this->fileStream = std::move(FS);
        FS.close();
    }
    logFile.close();
}
Lexer::~Lexer(){
    if (fileStream.is_open()){
        fileStream.close();
    }
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
    std::ofstream FS(log_file_path);
    if (!FS.is_open())
    {
        std::cerr << "Failed to open the file in getToken" << std::endl;
    }
    FS << "调用getToken方法" << std::endl;

    Lexer::StateEnum stateEnum = Lexer::StateEnum::NORMAL;
    std::string s;
    int dotLine = 0, dotColumn = 0;
    int ch = Lexer::getChar();
    while (ch != -1)
    {
        s.append(1, (char)ch);
        Token token;
        if (stateEnum == NORMAL)
        {

            FS << "进入Normal状态" << std::endl;
            if (isAlpha(ch))
            {
                stateEnum = Lexer::StateEnum::IN_ID;
            }
            else if (isDigit(ch))
            {
                stateEnum = Lexer::StateEnum::IN_NUM;
            }
            else if (isBlank(ch))
            {
                s.pop_back();
                stateEnum = Lexer::StateEnum::NORMAL;
            }
            else if (ch == '+')
            {
                return createToken(TokenType::PLUS, s, true);
            }
            else if (ch == '-')
            {
                return createToken(TokenType::MINUS, s, true);
            }
            else if (ch == '*')
            {
                return createToken(TokenType::MULTIPLE, s, true);
            }
            else if (ch == '/')
            {
                return createToken(TokenType::DIVISION, s, true);
            }
            else if (ch == '(')
            {
                return createToken(TokenType::L_BRACKET, s, true);
            }
            else if (ch == ')')
            {
                return createToken(TokenType::R_BRACKET, s, true);
            }
            else if (ch == ',')
            {
                return createToken(TokenType::COMMA, s, true);
            }
            else if (ch == ';')
            {
                return createToken(TokenType::SEMI, s, true);
            }
            else if (ch == '[')
            {
                return createToken(TokenType::L_S_BRACKETS, s, true);
            }
            else if (ch == ']')
            {
                return createToken(TokenType::R_S_BRACKET, s, true);
            }
            else if (ch == '=')
            {
                return createToken(TokenType::EQ, s, true);
            }
            else if (ch == '<')
            {
                return createToken(TokenType::LT, s, true);
            }
            else if (ch == ':')
            {
                stateEnum = StateEnum::IN_ASSIGN;
            }
            else if (ch == '{')
            {
                stateEnum = StateEnum::IN_COMMENT;
                s.pop_back();
            }
            else if (ch == '.')
            {
                stateEnum = StateEnum::IN_DOT;
            }
            else if (ch == '\'')
            {
                s.pop_back();
                stateEnum = StateEnum::IN_CHAR;
            }
            else
            {
                FS << "当前字符不在分析范围之内:" << showChar(ch) << '(' << ch << ")[" << this->line << "," << this->column << "]" << std::endl;
                stateEnum = StateEnum::ERROR;
            }
        }
        else if (stateEnum == IN_ID)
        {
            FS << "进入ID状态" << std::endl;
            if (isAlpha(ch) || isDigit(ch))
            {
                stateEnum = StateEnum::IN_ID;
            }
            else
            {
                FS << "当前字符已经不是标识符范围的了：" << showChar(ch) << "(" << ch << ")[" << line << ":" << column << "]" << std::endl;
                FS << "回溯字符：" << showChar(ch) << "(" << ch << ")[" << line << ":" << column << "]" << std::endl;
                backTrackChar(s.back());
                token = Token(this->line, this->column, TokenType::ID, s.substr(0, s.length() - 1), true);
                token.checkKeyWord();
                FS << "已识别token:" << token.toString() << std::endl;
                return token;
            }
        }
        else if (stateEnum == IN_NUM)
        {
            FS << "进入NUM状态" << std::endl;
            if (!isDigit(ch))
            {
                FS << "回溯字符：" << showChar(ch) << "(" << ch << ")[" << line << ":" << column << "]" << std::endl;
                backTrackChar(s.back());
                token = Token(this->line, this->column, TokenType::INTC, s.substr(0, s.length() - 1), true);
                FS << "已识别token:" << token.toString() << std::endl;
                return token;
            }
        }
        else if (stateEnum == IN_ASSIGN)
        {
            FS << "进入ASSIGN状态" << std::endl;
            if (ch == '=')
            {
                token = Token(line, column, TokenType::ASSIGN, s, true);
                FS << "已识别Token:" + token.toString() << std::endl;
                return token;
            }
            else
            {
                FS << "':'后面不是'='" << std::endl;
                stateEnum = StateEnum::ERROR;
            }
        }
        else if (stateEnum == IN_COMMENT)
        {
            FS << "进入COMMENT状态" << std::endl;
            int tmpLine = this->line;
            int tmpColumn = this->column - 1;
            s.pop_back();
            while (ch != '}' && ch != -1)
            {
                ch = Lexer::getChar();
            }
            stateEnum = StateEnum::NORMAL;
            if (ch != '}')
            {
                FS << "没有注释结束符，注释结束符在:[" << tmpLine << ',' << tmpColumn << ']' << std::endl;
                stateEnum = StateEnum::ERROR;
            }
        }
        else if (stateEnum == IN_DOT)
        {
            FS << "进入DOT状态" << std::endl;
            if (isAlpha(ch))
            { // record域中的点运算符
                FS << "record域中的点运算符" << std::endl;
                FS << "回溯字符：" << showChar(ch) << "(" << ch << ")[" << line << "," << column << "]" << std::endl;
                backTrackChar(ch); // 回溯多读的字符
                s.pop_back();
                token = Token(line, column, TokenType::DOT, s, true);
                FS << "已识别Token:" << token.toString() << std::endl;
                return token;
            }
            else if (ch == '.')
            { // 数组的下标运算符
                stateEnum = StateEnum::IN_RANGE;
                break;
            }
            dotLine = line;
            dotColumn = column - 1;
            while (isBlank(ch))
            {
                // 获取下一个字符
                ch = getChar();
            }
            if (ch == -1)
            { // 结束标志
                FS << "结束标志" << std::endl;
                token = Token(dotLine, dotColumn, TokenType::_EOF_, ".", true);
                FS << "已识别Token:" << token.toString() << std::endl;
                return token;
            }
            // 错误，回溯
            FS << "错误的点运算符" << std::endl;
            FS << "回溯字符：" << showChar(ch) << "(" << ch << ")[" << line << "," << column << "]" << std::endl;
            backTrackChar(ch);
            token = Token(line, column, TokenType::ERROR, s, true);
            FS << "已识别Token:" << token.toString() << std::endl;
        }
        else if (stateEnum == IN_RANGE)
        {
            FS << "进入RANGE状态" << std::endl;
            if (isDigit(ch))
            { // 如果是数组下标界限符，那么后面一定是数字
                FS << "回溯字符：" << showChar(ch) << "(" << ch << ")[" << line << "," << column << "]" << std::endl;
                backTrackChar(ch);
                s.pop_back();
                token = Token(line, column, TokenType::ARRAY_BOUNDS, s, true);
                FS << "已识别Token:" << token.toString() << std::endl;
                return token;
            }
            // 如果后面不是数字，那么error
            FS << "数组下标界限符后面不是数字" << std::endl;
            stateEnum = StateEnum::ERROR;
        }
        else if (stateEnum == IN_CHAR)
        {
            FS << "进入CHAR状态" << std::endl;
            if (isDigit(ch) || isAlpha(ch))
            {
                // 判断后面是否跟着字符结束标志'\''
                ch = getChar();
                if (ch == '\'')
                {
                    token = Token(line, column, TokenType::CHAR, s, true);
                    FS << "已识别Token:" << token.toString() << std::endl;
                    return token;
                }
            }
            // 其他符号，error
            FS << "没有字符结束标志" << std::endl;
            stateEnum = StateEnum::ERROR;
        }
        else if (stateEnum == ERROR)
        {
            FS << "[Error] Unrecognized token. near " << line << ":" << column << std::endl;
            FS << "回溯字符：" << showChar(ch) << "(" << ch << ")[" << line << "," << column << "]" << std::endl;
            backTrackChar(ch);
            s.pop_back();
            token = Token(line, column, TokenType::ERROR, s, true);
            return token;
        }
        else
        {
            stateEnum = ERROR;
            break;
        }
        ch = getchar();
    }
    if (stateEnum != NORMAL)
    {
        FS << "[错误]在" << line << "行" << column << "列" << std::endl;
    }
    FS.close();
    return new Token();
}
void Lexer::backTrackChar(int ch)
{
    backtraceNumber = ch;
    column--;
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
    std::ofstream FS(log_file_path);
    if (!FS.is_open())
    {
        std::cerr << "Failed to open the file" << std::endl;
    }
    FS << "当前字符是：\""
               << showChar(ch) << '(' << ch << ')'
               << '[' << line << ':' << column << ']' << std::endl;
    FS.close();
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

Token Lexer::createToken(TokenType type, const std::string &s, bool output)
{
    std::ofstream FS(log_file_path);
    if (!FS.is_open())
    {
        std::cerr << "Failed to open the file in createToken" << std::endl;
    }
    Token token(this->line, this->column, type, s, output);
    if (output)
    {
        FS << "已识别Token:" << token.toString() << std::endl;
    }
    FS.close();
    return token;
}
