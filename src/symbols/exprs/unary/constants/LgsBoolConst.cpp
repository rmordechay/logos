#include "exprs/unary/constants/LgsBoolConst.h"

string LgsBoolConst::getValueAsString() const {
    return value ? LgsBool::trueLiteral : LgsBool::falseLiteral;
}

Value* LgsBoolConst::createIRValue(LgsRuntime* runtime) {
    return runtime->builder.getInt1(value);
}

Value* LgsBoolConst::eqIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::neIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::ltIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::gtIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::geIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::leIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::andIR(LgsRuntime* runtime, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return runtime->builder.getInt1(value && otherBool->value);
    }
    assert(0);
}

Value* LgsBoolConst::orIR(LgsRuntime* runtime, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return runtime->builder.getInt1(value || otherBool->value);
    }
    assert(0);
}

Value* LgsBoolConst::bitAndIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::bitOrIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::bitXorIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::rshiftIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::lshiftIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(0);
}
