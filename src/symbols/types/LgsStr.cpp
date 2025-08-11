#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"

#include "utils/LgsUtils.h"

Type* LgsStr::getIRBaseType(LgsCodeGen* codeGen) const {
    return ArrayType::get(baseType->getIRType(codeGen), initialLength);
}

Type* LgsStr::getIRType(LgsCodeGen* codeGen) {
    return codeGen->ptrTy();
}

size_t LgsStr::getSizeBytes() {
    return initialLength + 1;
}

string LgsStr::getName() {
    return name;
}

string LgsStr::prettyName() {
    return name;
}

LgsExpr* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

string LgsStr::strFormatPart() const {
    return "%s";
}

LgsType* LgsStr::getIndexType() {
    return &LGS_INT;
}

Value* LgsStr::IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return lenFunc.call(codeGen, {iterable});
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
