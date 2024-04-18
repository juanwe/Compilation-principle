#include"LL1Parse.h"

SyntaxTree* LL1Parse::syntaxParse(){
    fileStream << "=========================语法分析开始=============================" << std::endl;
    std::stack<Symbol*> s;
    NonTerminal start("Program");
    TreeNode* root = start.getNode();
    s.push(&start);
    Symbol* symbol;
    while(!s.empty()){
        symbol = s.top();
        s.pop();
        if (dynamic_cast<Terminal *>(symbol) != nullptr)
        {
            fileStream << " symbol是终结符: <" << TokenTypeToString[dynamic_cast<Terminal *>(symbol)->getToken()->getType()] << ">" << std::endl;
            Terminal *terminal = dynamic_cast<Terminal *>(symbol);
            if (terminal != nullptr)
            {
                TokenType tokenType = terminal->getToken()->getType();
                std::string str(TokenTypeToString[tokenType]);
                TreeNode match(str);
                symbol->getNode()->setValue(match.getValue());
                fileStream << "##########终结符识别完毕：<" << symbol->getNode()->getValue() << "> ###########" << std::endl;
            }
        }
        else
        {
            // 输出符号是非终结符
            fileStream << "symbol是非终结符: <" << dynamic_cast<NonTerminal *>(symbol)->getValue() << ">" << std::endl;
            // 查预测分析表，将 symbol 替换成右端生成式
            std::vector<std::shared_ptr<Symbol> > symbols = find(*dynamic_cast<NonTerminal *>(symbol));
            fileStream << "预测分析表返回：";
            for (const auto &symbol : symbols)
            {
                symbol->toString();
                fileStream <<" ";
            }
            fileStream << std::endl;

            if (!symbols.empty())
            {
                // 右端生成式为 symbol 的 children
                int size = symbols.size();
                auto it = symbols.begin();
                Symbol *prevSymbol = (*it).get();
                ++it;
                for (; it != symbols.end(); ++it)
                {
                    (*it)->getNode()->setSiblings((prevSymbol)->getNode());
                    prevSymbol = (*it).get();
                }
                symbol->getNode()->setChildren(symbols.front()->getNode());
                fileStream << "构建" << dynamic_cast<NonTerminal *>(symbol)->getValue() << "的子树："
                           << symbol->getNode()->getChildren() << std::endl;

                // 右端生成式逆序入栈
                for (auto it = symbols.rbegin(); it != symbols.rend(); ++it)
                {
                    Symbol *item = (*it).get();
                    if (dynamic_cast<Terminal *>(item) || !(dynamic_cast<NonTerminal *>(item))->isBlank())
                        s.push(item);
                }
            }
            else
            {
                std::cerr << "预测分析表查询失败" << std::endl;
                return nullptr;
            }
        }
        // }else{
        //    fileStream<<"未识别的字符，出现了不应该出现的字符：[ " << symbol->getNode()->getValue() << " ]"<<std::endl;
        // }
    }
    this->syntaxTree = new SyntaxTree(root);
    return this->syntaxTree;
}