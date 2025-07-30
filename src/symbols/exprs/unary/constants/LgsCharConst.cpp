#include "exprs/unary/constants/LgsCharConst.h"


#include "utils/LgsUtils.h"


string LgsCharConst::prettyName() {
    return type->prettyName();
}

Value* LgsCharConst::createIRValue(LgsCodeGen* codeGen) {
    return codeGen->i8(value);
}
