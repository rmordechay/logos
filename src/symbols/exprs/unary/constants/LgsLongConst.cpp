#include "exprs/unary/constants/LgsLongConst.h"


#include "utils/LgsUtils.h"


string LgsLongConst::prettyName() {
    return type->prettyName();
}

Value* LgsLongConst::createIRValue(LgsCodeGen* codeGen) {
    return codeGen->i64(value);
}
