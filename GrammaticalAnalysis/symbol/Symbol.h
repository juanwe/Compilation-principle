#pragma once

#include "../../Util/ToStringUtils.h"
#include "../Tree/TreeNode.h"
//符号基类
class Symbol : public ToStringUtils
{
public:
    TreeNode *getNode();
};
