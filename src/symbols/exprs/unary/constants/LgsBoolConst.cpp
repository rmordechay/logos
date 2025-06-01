#include "exprs/unary/constants/LgsBoolConst.h"

string LgsBoolConst::getValueAsString() const {
    return value ? LgsBool::trueLiteral : LgsBool::falseLiteral;
}

Value* LgsBoolConst::createIRValue(Module* module) {
    return builder.getInt1(value);
}

Value* LgsBoolConst::eqIR(Module* module, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::neIR(Module* module, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::ltIR(Module* module, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::gtIR(Module* module, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::geIR(Module* module, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::leIR(Module* module, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::andIR(Module* module, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return builder.getInt1(value && otherBool->value);
    }
    assert(false);
}

Value* LgsBoolConst::orIR(Module* module, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return builder.getInt1(value || otherBool->value);
    }
    assert(false);
}

Value* LgsBoolConst::bitAndIR(Module* module, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::bitOrIR(Module* module, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::bitXorIR(Module* module, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::rshiftIR(Module* module, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::lshiftIR(Module* module, LgsExpr* other) {
    assert(false);
}
