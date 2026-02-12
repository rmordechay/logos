#include "funcs/LgsParam.h"
#include "LgsType.h"
#include "codegen/LgsCodeGen.h"

LgsType* LgsParam::getType() {
    return type;
}

void LgsParam::setType(LgsType* newType) {
    if (type && type != newType) freeType(type);
    type = newType;
}

void LgsParam::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}
