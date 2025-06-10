#include "exprs/unary/constants/LgsTypeConst.h"
#include "analysis/AntlrConverter.h"

string LgsTypeConst::getName() {
    return type->prettyName();
}

Value* LgsTypeConst::createIRValue(LgsRuntime* runtime) {
    assert(0);
}
