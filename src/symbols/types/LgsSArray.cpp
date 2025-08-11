#include "types/LgsSArray.h"
#include "builtins/LgsBuiltins.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "types/primitives/LgsInt.h"

Type* LgsSArray::getIRType(LgsCodeGen* codeGen) {
    if (IRType) return IRType;
    const auto innerIRType = baseType->getIRType(codeGen);
    IRType = ArrayType::get(innerIRType, initialLength);
    return IRType;
}

size_t LgsSArray::getSizeBytes() {
    return baseType->getSizeBytes() * initialLength;
}

LgsExpr* LgsSArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

LgsType* LgsSArray::getIndexType() {
    return &LGS_INT;
}

string LgsSArray::getStrFormatPart() const {
    return "%p";
}

string LgsSArray::prettyName() {
    return baseType->prettyName() + '[' + (initialLength == 0 ? "" : to_string(initialLength)) + "]!";
}

bool LgsSArray::equals(LgsType* other) {
    const auto otherArr = other->asDArray();
    if (!otherArr) return false;
    if (!baseType->equals(otherArr->baseType)) return false;
    return sizeExpr->type->equals(otherArr->sizeExpr->type);;
}

string LgsSArray::getName() {
    return name;
}

Value* LgsSArray::IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return sizeExpr->getIRValue(codeGen);
}

Value* LgsSArray::IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    assert(0);
}

Value* LgsSArray::IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    assert(0);
}

LgsSArray::~LgsSArray() {
    delete sizeExpr;
}
