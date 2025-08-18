#include "types/LgsSArray.h"
#include "builtins/LgsBuiltins.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "types/primitives/LgsInt.h"

Type* LgsSArray::getIRType(LgsCodeGen* codeGen) {
    if (IRType) return IRType;
    const auto innerIRType = baseType->getIRType(codeGen);
    IRType = ArrayType::get(innerIRType, sizeExpr->getConstInt());
    return IRType;
}

size_t LgsSArray::getSizeBytes() {
    return baseType->getSizeBytes() * sizeExpr->getConstInt();
}

uint16_t LgsSArray::getUnpackCount() const {
    return 1;
}

LgsExpr* LgsSArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

LgsType* LgsSArray::getIndexType() {
    return &LGS_INT;
}

std::string LgsSArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

json::object LgsSArray::asJSON() {
    json::object obj;
    return obj;
}

std::string LgsSArray::pname() {
    const auto index = sizeExpr->getConstInt() == 0 ? "" : std::to_string(sizeExpr->getConstInt());
    const auto ty = baseType ? baseType->pname() : "";
    return ty + '[' + index + "]!";
}

bool LgsSArray::equals(LgsType* other) {
    const auto otherArr = other->asSArray();
    if (!otherArr) return false;
    return baseType->equals(otherArr->baseType);
}

std::string LgsSArray::getName() {
    return name;
}

Value* LgsSArray::IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return sizeExpr->getIRValue(codeGen);
}

Value* LgsSArray::IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return codeGen->builder.getFalse();
}

Value* LgsSArray::IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return codeGen->builder.getTrue();
}

LgsSArray::~LgsSArray() {
    delete sizeExpr;
}
