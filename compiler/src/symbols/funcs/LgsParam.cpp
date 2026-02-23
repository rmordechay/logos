#include "funcs/LgsParam.h"

#include <assert.h>

#include "LgsType.h"

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
