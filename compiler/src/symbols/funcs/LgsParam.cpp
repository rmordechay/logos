#include "funcs/LgsParam.h"
#include "LgsType.h"
#include "codegen/LgsCgModule.h"

Value* LgsParam::loadIR(LgsCgModule& cg) {
    return IRValue;
}

void LgsParam::setType(LgsType* newType) {
    type = newType;
}

void LgsParam::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

std::string LgsParam::getName() {
    return name;
}

LgsType* LgsParam::getType() {
    return type;
}
