#include "exprs/unary/constants/LgsBoolConst.h"

Value* LgsBoolConst::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.getInt1(value);
}

Value* LgsBoolConst::andIR(CodeGenMetadata* metadata, LgsExpr* right) {
    if (const auto otherBool = right->asBoolConst()) {
        return metadata->builder.getInt1(value && otherBool->value);
    }
    assert(false);
}
