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

