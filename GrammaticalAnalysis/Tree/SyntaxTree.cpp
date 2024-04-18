#include "SyntaxTree.h"

SyntaxTree::SyntaxTree() : root(nullptr) {} // 默认构造函数定义

SyntaxTree::SyntaxTree(TreeNode *root) : root(root) {} // 带参数构造函数定义

// std::ostream& SyntaxTree::getOut()
// {
//     return out;
// }

// void SyntaxTree::setOut(std::ostream& out)
// {
//     this->out = out;
// }

void SyntaxTree::preOrderRecursive()
{
    int b[100] = {0}; // 初始化 b 数组为全 0
    preOrderRecursiveCore(root, 0, 0, b);
}

void SyntaxTree::preOrderRecursiveCore(TreeNode *node, int level, int cnt, int *b)
{
    if (node == nullptr)
        return;

    for (int i = 0; i < level - 1; i++)
    {
        if (b[i] == 1)
        {
            std::cout << "|  ";
            // out << "|  ";
        }
        else
        {
            std::cout << "   ";
            // out << "   ";
        }
    }

    if (node == root)
    {
        std::cout << node->getValue() << std::endl;
        // out << node->getValue() << std::endl;
    }
    else
    {
        std::cout << "|__" << node->getValue() << std::endl;
        // out << "|__" << node->getValue() << std::endl;
    }

    if (node->hasChild())
    {
        if (node->hasSiblings())
        {
            if (level > 0)
                b[level - 1] = 1;
            preOrderRecursiveCore(node->getChildren(), level + 1, cnt + 1, b);
        }
        else
        {
            if (level > 0)
                b[level - 1] = 0;
            preOrderRecursiveCore(node->getChildren(), level + 1, cnt, b);
        }
    }

    if (node->hasSiblings())
    {
        preOrderRecursiveCore(node->getSiblings(), level, cnt, b);
    }
}
