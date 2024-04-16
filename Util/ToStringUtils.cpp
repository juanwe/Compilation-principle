#include "ToStringUtils.h"
#include <sstream>

std::string ToStringUtils::toString() const
{
    std::ostringstream ss;
    ss << *this;
    return ss.str();
}