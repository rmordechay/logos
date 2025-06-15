#include "exprs/unary/constants/LgsTypeConst.h"
#include "analysis/AntlrConverter.h"

string LgsTypeConst::getExprName() {
    return type->pName();
}

Value* LgsTypeConst::createIRValue(LgsRuntime* runtime) {
    assert(0);
}
