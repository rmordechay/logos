#include "exprs/constants/LgsUIntConst.h"

#include "exprs/constants/LgsStrConst.h"

std::string LgsUIntConst::getName() {
    return std::to_string(value);
}