#include "funcs/LgsParam.h"
#include "LgsType.h"
#include "codegen/LgsCodeGen.h"

Value* LgsParam::loadIR(LgsCodeGen& cg) {
    return IRValue;
}

void LgsParam::setType(LgsType* newType) {
    type = newType;
}

void LgsParam::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsParam::getName() {
    return name;
}

LgsType* LgsParam::getType() {
    return type;
}
