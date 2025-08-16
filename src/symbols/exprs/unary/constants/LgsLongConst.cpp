#include "exprs/unary/constants/LgsLongConst.h"


#include "utils/LgsUtils.h"


std::string LgsLongConst::pname() {
    return type->pname();
}

void LgsLongConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->i64(value);
}
