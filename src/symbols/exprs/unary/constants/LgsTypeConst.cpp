#include "exprs/unary/constants/LgsTypeConst.h"
#include "analysis/AntlrConverter.h"

string LgsTypeConst::getExprName() {
    return type->prettyName();
}

Value* LgsTypeConst::createIRValue(LgsModule* module) {
    assert(0);
}
