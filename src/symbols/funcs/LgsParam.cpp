#include "funcs/LgsParam.h"

#include "LgsType.h"
#include "utils/LgsUtils.h"

Value* LgsParam::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsParam::asText() {
    return name;
}