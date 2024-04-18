#include"LexParse.h"

LexParse::LexParse(){
    std::ofstream logFile(this->log_file_path, std::ios::app);
    if (!logFile.is_open())
    {
        std::cerr << "无法打开日志文件" << log_file_path << std::endl;
    }
    else{
        this->fileStream = std::move(logFile);
    }
}
LexParse::~LexParse(){
    if(fileStream.is_open()){
        fileStream.close();
    }
}
void LexParse::lexParse(std::string inPath){

    Lexer lexer(inPath);
    LexerResult result = lexer.getResult(); // 对文件流进行词法分析
    // 处理词法分析结果
    this->tokenList = result.getTokenList();
    fileStream << "=========================词法分析结束============================" << std::endl;
}
TreeNode LexParse::match(TokenType type){
    Token t = this->popToken();
    TreeNode node;
    if(t.isValidObject()){
        if(t.getType()==type){
            node = TreeNode(t.getValue());
            fileStream << "已匹配" << t.toString() << std::endl;
        }else{
            fileStream << "未成功匹配：[" << TokenTypeToString[type] << "]和" << t.toString() << std::endl;
        }
    }else{
        fileStream << "输入流已空" << std::endl;
    }
    return node;
}
std::vector<std::shared_ptr<Symbol>> LexParse::find(NonTerminal symbol)
{
    Token token = this->peekToken();
    std::string value = symbol.getValue();
    fileStream << "查询预测分析表：[ 非终结符：" + value + " ] [ 输入符号：" + token.getValue() + " ]" << std::endl;
    NonTerminalEnum n(stringToNON_TERMINAL(value));
    fileStream << "NON_TERMINAL: <" << value << ">" << std::endl;
    return n.predict(token);
}
Token LexParse::popToken(){
    Token token;
    if(currentIndex<tokenList.size()){
        auto it = tokenList.begin();
        std::advance(it, currentIndex++);
        token = *it;
        fileStream << "获取下一个Token: " << token.toString() << std::endl;
    }else{
        fileStream << "输入流已空" << std::endl;
    }
    return token;
}
Token LexParse::peekToken(){
    Token token;
    if(currentIndex<tokenList.size()){
        auto it = tokenList.begin();
        std::advance(it, currentIndex++);
        token = *it;
        fileStream << "当前Token是: " << token.toString() << std::endl;
    }
    else
    {
        fileStream << "输入流已空" << std::endl;
    }
    return token;
}