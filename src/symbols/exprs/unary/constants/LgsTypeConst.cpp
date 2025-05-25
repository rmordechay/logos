#include "exprs/unary/constants/LgsTypeConst.h"
#include "analysis/AntlrConverter.h"

string LgsTypeConst::getName() {
    return type->prettyName();
}

Value* LgsTypeConst::createIRValue(CodeGenMetadata* metadata) {
    assert(false);
}
