#include "exprs/unary/constants/LgsTypeConst.h"
#include "AntlrConverter.h"

string LgsTypeConst::getName() {
    return type->prettyName();
}

Value* LgsTypeConst::createIRValue(CodeGenMetadata* metadata) {
    assert(false);
}
