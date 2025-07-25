#include "exprs/unary/constants/LgsBoolConst.h"

#include "utils/LgsUtils.h"

string LgsBoolConst::getValueAsString() const {
    return value ? LgsBool::trueLiteral : LgsBool::falseLiteral;
}

Value* LgsBoolConst::createIRValue(LgsModule* module) {
    return i1(module, value);
}

Value* LgsBoolConst::eqIR(LgsModule* module, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::neIR(LgsModule* module, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::ltIR(LgsModule* module, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::gtIR(LgsModule* module, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::geIR(LgsModule* module, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::leIR(LgsModule* module, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::andIR(LgsModule* module, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return i1(module, value && otherBool->value);
    }
    assert(0);
}

Value* LgsBoolConst::orIR(LgsModule* module, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return i1(module, value || otherBool->value);
    }
    assert(0);
}

Value* LgsBoolConst::bitAndIR(LgsModule* module, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::bitOrIR(LgsModule* module, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::bitXorIR(LgsModule* module, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::rshiftIR(LgsModule* module, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::lshiftIR(LgsModule* module, LgsExpr* other) {
    assert(0);
}
