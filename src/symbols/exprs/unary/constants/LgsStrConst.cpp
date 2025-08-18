#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"

std::string LgsStrConst::pname() {
    return type->pname();
}

Value* LgsStrConst::hash(LgsCodeGen* codeGen) {
    return codeGen->i32(hashStr(value.c_str()));
}

json::value_ref LgsStrConst::asJSON() {
    json::object obj;
    return obj;
}

void LgsStrConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->getIRStr(value);
}

Value* LgsStrConst::addIR(LgsCodeGen* codeGen, LgsExpr* other) {
    if (const auto otherStrConst = other->asIntConst()) {
        return codeGen->getIRStr(this->value + std::to_string(otherStrConst->value));
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
