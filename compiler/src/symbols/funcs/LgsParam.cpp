#include "funcs/LgsParam.h"
#include "LgsType.h"
#include "codegen/LgsCodeGen.h"

void LgsParam::setType(LgsType* newType) {
    if (type && type != newType) freeType(type);
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
