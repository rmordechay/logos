#include "funcs/LgsParam.h"
#include "LgsType.h"

Value* LgsParam::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsParam::asText() {
    return name;
}

void LgsParam::setType(LgsType* newType) {
    type = newType;
}