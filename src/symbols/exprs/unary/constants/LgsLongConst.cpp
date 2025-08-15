#include "exprs/unary/constants/LgsLongConst.h"


#include "utils/LgsUtils.h"


std::string LgsLongConst::prettyName() {
    return type->prettyName();
}

void LgsLongConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->i64(value);
}
