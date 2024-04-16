#pragma once

#include "../../Util/ToStringUtils.h"

//符号基类
class Symbol : public ToStringUtils
{
public:
    TreeNode *getNode();
};
