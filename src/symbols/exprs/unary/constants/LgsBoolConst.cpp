#include "exprs/unary/constants/LgsBoolConst.h"


#include "utils/LgsUtils.h"

string LgsBoolConst::getValueAsString() const {
    return value ? LgsBool::trueLiteral : LgsBool::falseLiteral;
}

string LgsBoolConst::prettyName() {
    return type->prettyName();
}

Value* LgsBoolConst::createIRValue(LgsCodeGen* codeGen) {
    return codeGen->i1(value);
}

Value* LgsBoolConst::eqIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::neIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::ltIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::gtIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::geIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::leIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::andIR(LgsCodeGen* codeGen, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return codeGen->i1(value && otherBool->value);
    }
    assert(0);
}

Value* LgsBoolConst::orIR(LgsCodeGen* codeGen, LgsExpr* other) {
    if (const auto otherBool = other->asBoolConst()) {
        return codeGen->i1(value || otherBool->value);
    }
    assert(0);
}

Value* LgsBoolConst::bitAndIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::bitOrIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::bitXorIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::rshiftIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsBoolConst::lshiftIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}
