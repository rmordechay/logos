#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"

std::string LgsStrConst::pname() {
    return type->pname();
}

Value* LgsStrConst::hash(LgsCodeGen* codeGen) {
    return codeGen->i32(hashStr(value.c_str()));
}

void LgsStrConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->getIRStr(value);
}

Value* LgsStrConst::addIR(LgsCodeGen* codeGen, LgsExpr* other) {
    if (const auto otherStrConst = other->asIntConst()) {
        return codeGen->getIRStr(this->value + std::to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asFloatConst()) {
        return codeGen->getIRStr(this->value + std::to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asStrConst()) {
        return codeGen->getIRStr(this->value + otherStrConst->value);
    }
    if (const auto otherBoolConst = other->asBoolConst()) {
        return codeGen->getIRStr(this->value + otherBoolConst->getValueAsString());
    }
    assert(0);
}

Value* LgsStrConst::eqIR(LgsCodeGen* codeGen, LgsExpr* other) {
    return nullptr;
}

LgsStrConst::~LgsStrConst() {
    if (formatedStr != "") {
        delete formatedStr.c_str();
    }
}
