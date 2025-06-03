#include "exprs/unary/constants/LgsFloatConst.h"

Value* LgsFloatConst::createIRValue(LgsRuntime* runtime) {
    return ConstantFP::get(builder.getFloatTy(), value);
}
