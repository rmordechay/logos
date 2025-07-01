#include "exprs/unary/constants/LgsBoolConst.h"

string LgsBoolConst::getValueAsString() const {
    return value ? LgsBool::trueLiteral : LgsBool::falseLiteral;
}

Value* LgsBoolConst::createIRValue(LgsModule* runtime) {
    return runtime->builder.getInt1(value);
}

Value* LgsBoolConst::eqIR(LgsModule* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::neIR(LgsModule* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::ltIR(LgsModule* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::gtIR(LgsModule* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::geIR(LgsModule* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::leIR(LgsModule* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::andIR(LgsModule* runtime, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return runtime->builder.getInt1(value && otherBool->value);
    }
    assert(0);
}

Value* LgsBoolConst::orIR(LgsModule* runtime, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return runtime->builder.getInt1(value || otherBool->value);
    }
    assert(0);
}

Value* LgsBoolConst::bitAndIR(LgsModule* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::bitOrIR(LgsModule* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::bitXorIR(LgsModule* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::rshiftIR(LgsModule* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::lshiftIR(LgsModule* runtime, LgsExpr* other) {
    assert(0);
}
