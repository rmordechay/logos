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

Value* LgsStr::IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return lenFunc.call(codeGen, {iterable});
}

Value* LgsStr::getLoopLength(LgsCodeGen* codeGen, LgsExpr* iterable) {
    const auto lenPtr = codeGen->builder.CreateAlloca(codeGen->i64Ty());
    codeGen->builder.CreateStore(IRLength(codeGen, iterable), lenPtr);
    return codeGen->builder.CreateLoad(codeGen->i64Ty(), lenPtr);
}

Value* LgsStr::IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isEmptyFunc.call(codeGen, {iterable});
}

Value* LgsStr::IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isNotEmptyFunc.call(codeGen, {iterable});
}

bool LgsStr::equals(LgsType* other) {
    assert(other);
    if (other->getName() == LgsAny::name) return true;
    return name == other->getName();
}
