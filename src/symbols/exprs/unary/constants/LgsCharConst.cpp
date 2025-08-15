#include "exprs/unary/constants/LgsCharConst.h"


#include "utils/LgsUtils.h"


std::string LgsCharConst::prettyName() {
    return type->prettyName();
}

void LgsCharConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->i8(value);
}
