#include "exprs/unary/constants/LgsBoolConst.h"

string LgsBoolConst::getValueAsString() const {
    return value ? LgsBool::trueLiteral : LgsBool::falseLiteral;
}

Value* LgsBoolConst::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.getInt1(value);
}

Value* LgsBoolConst::eqIR(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::neIR(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::ltIR(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::gtIR(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::geIR(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::leIR(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::andIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return metadata->builder.getInt1(value && otherBool->value);
    }
    assert(false);
}

Value* LgsBoolConst::orIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return metadata->builder.getInt1(value || otherBool->value);
    }
    assert(false);
}

Value* LgsBoolConst::bitAndIR(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::bitOrIR(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::bitXorIR(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::rshiftIR(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::lshiftIR(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false);
}
