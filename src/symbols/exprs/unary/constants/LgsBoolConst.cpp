#include "exprs/unary/constants/LgsBoolConst.h"


#include "utils/LgsUtils.h"

std::string LgsBoolConst::getValueAsString() const {
    return value ? LgsBool::trueLiteral : LgsBool::falseLiteral;
}

std::string LgsBoolConst::prettyName() {
    return type->prettyName();
}

void LgsBoolConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->i1(value);
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

