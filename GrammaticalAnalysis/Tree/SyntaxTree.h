#pragma once

#include<iostream>
#include "TreeNode.h"

class SyntaxTree{
private:
    TreeNode* root;
    std::ostream& out;
public:
    SyntaxTree();
    SyntaxTree(TreeNode* root);

    // std::ostream &getOut();         
    // void setOut(std::ostream &out);

    void preOrderRecursive();                                               
    void preOrderRecursiveCore(TreeNode *node, int level, int cnt, int *b); // 前序递归遍历
};