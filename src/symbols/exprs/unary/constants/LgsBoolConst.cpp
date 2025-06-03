#include "exprs/unary/constants/LgsBoolConst.h"

string LgsBoolConst::getValueAsString() const {
    return value ? LgsBool::trueLiteral : LgsBool::falseLiteral;
}

Value* LgsBoolConst::createIRValue(LgsRuntime* runtime) {
    return builder.getInt1(value);
}

Value* LgsBoolConst::eqIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::neIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::ltIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::gtIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::geIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::leIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::andIR(LgsRuntime* runtime, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return builder.getInt1(value && otherBool->value);
    }
    assert(false);
}

Value* LgsBoolConst::orIR(LgsRuntime* runtime, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return builder.getInt1(value || otherBool->value);
    }
    assert(false);
}

Value* LgsBoolConst::bitAndIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::bitOrIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::bitXorIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::rshiftIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::lshiftIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(false);
}
