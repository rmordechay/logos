#include "exprs/unary/constants/LgsBoolConst.h"

string LgsBoolConst::getValueAsString() const {
    return value ? LgsBool::trueLiteral : LgsBool::falseLiteral;
}

Value* LgsBoolConst::createIRValue(CodegenMetadata* metadata) {
    return metadata->builder.getInt1(value);
}

Value* LgsBoolConst::eqIR(CodegenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::neIR(CodegenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::ltIR(CodegenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::gtIR(CodegenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::geIR(CodegenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::leIR(CodegenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::andIR(CodegenMetadata* metadata, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return metadata->builder.getInt1(value && otherBool->value);
    }
    assert(false);
}

Value* LgsBoolConst::orIR(CodegenMetadata* metadata, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return metadata->builder.getInt1(value || otherBool->value);
    }
    assert(false);
}

Value* LgsBoolConst::bitAndIR(CodegenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::bitOrIR(CodegenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::bitXorIR(CodegenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::rshiftIR(CodegenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsBoolConst::lshiftIR(CodegenMetadata* metadata, LgsExpr* other) {
    assert(false);
}
