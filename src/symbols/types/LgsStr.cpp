#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"

#include "utils/LgsUtils.h"

size_t LgsStr::getSizeBytes() {
    return initialLength + 1;
}

string LgsStr::getName() {
    return name;
}

Type* LgsStr::getIRType(LgsCodeGen* codeGen) {
    return ArrayType::get(baseType->getIRType(codeGen), initialLength);
}

string LgsStr::prettyName() {
    return name;
}

LgsExpr* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

string LgsStr::getStrFormatPart() const {
    return "%s";
}

LgsType* LgsStr::getIndexType() {
    return &LGS_INT;
}

LgsType* LgsStr::getValueType() {
    return baseType;
}

Value* LgsStr::getLength(LgsExpr* expr) {
    return lenFunc.call(codeGen, {expr});
}

Value* LgsStr::getLoopLength(LgsExpr* expr) {
    const auto lenPtr = codeGen->builder.CreateAlloca(codeGen->i64Ty());
    codeGen->builder.CreateStore(getLength(expr), lenPtr);
    return codeGen->builder.CreateLoad(codeGen->i64Ty(), lenPtr);
}

Value* LgsStr::isEmpty(LgsExpr* expr) {
    return isEmptyFunc.call(codeGen, {expr});
}

Value* LgsStr::isNotEmpty(LgsExpr* expr) {
    return isNotEmptyFunc.call(codeGen, {expr});
}

bool LgsStr::equals(LgsType* other) {
    assert(other);
    if (other->getName() == LgsAny::name) return true;
    return name == other->getName();
}
