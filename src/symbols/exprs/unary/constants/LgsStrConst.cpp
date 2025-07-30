#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"

#include "utils/LgsUtils.h"

extern "C" {
    size_t Str_hash(const char* key);
}

string LgsStrConst::prettyName() {
    return type->prettyName();
}

Value* LgsStrConst::hashValue(LgsCodeGen* codeGen) {
    return codeGen->i32(Str_hash(value.c_str()));
}

Value* LgsStrConst::createIRValue(LgsCodeGen* codeGen) {
    return codeGen->getIRStr(value);
}

Value* LgsStrConst::addIR(LgsCodeGen* codeGen, LgsExpr* other) {
    if (const auto otherStrConst = other->asIntConst()) {
        return codeGen->getIRStr(this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asFloatConst()) {
        return codeGen->getIRStr(this->value + to_string(otherStrConst->value));
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
