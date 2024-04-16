#include "TreeNode.h"

TreeNode::TreeNode(){}
TreeNode::TreeNode(std::string value) {
    this->value = value;
}

bool TreeNode::hasChild(){
    return children != nullptr;
}
bool TreeNode::hasSiblings(){
    return siblings != nullptr;
}
TreeNode *TreeNode::getSiblings()
{
    return siblings;
}
void TreeNode::setSiblings(TreeNode *sib)
{
    this->siblings = sib;
}
TreeNode *TreeNode::getChildren()
{
    return children;
}
void TreeNode::setChildren(TreeNode *child)
{
    this->children = child;
}
std::string TreeNode::getValue()
{
    return value;
}
void TreeNode::setValue(const std::string &val)
{
    this->value = val;
}
std::string TreeNode::toString()
{
    std::ostringstream ss;
    ss << this->value << " " << (this->siblings ? siblings->value : "");
    return ss.str();
}