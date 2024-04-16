#pragma once

#include<string>
#include<sstream>

//树节点定义
class TreeNode
{
private:
    TreeNode *siblings;
    TreeNode *children;
    std::string value;

public:
    TreeNode();
    TreeNode(std::string value);
    bool hasChild();
    bool hasSiblings();

    TreeNode *getSiblings();
    void setSiblings(TreeNode *siblings);
    TreeNode *getChildren();
    void setChildren(TreeNode *children);
    std::string getValue();
    void setValue(const std::string &val);

    std::string toString();
};