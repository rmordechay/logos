#include "types/LgsSArray.h"
#include "builtin/LgsBuiltins.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "types/primitives/LgsInt.h"

Type* LgsSArray::getIRType(LLVMContext& context) {
    if (IRType) return IRType;
    const auto innerIRType = baseType->getIRType(context);
    IRType = ArrayType::get(innerIRType, iterLen);
    return IRType;
}

size_t LgsSArray::getSizeBytes() {
    return baseType->getSizeBytes() * iterLen;
}

LgsExpr* LgsSArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

LgsType* LgsSArray::getIndexType() {
    return &LGS_INT;
}

LgsType* LgsSArray::getValueType() {
    return baseType;
}

string LgsSArray::getStrFormatPart() const {
    return "%p";
}

string LgsSArray::prettyName() const {
    return baseType->prettyName() + '[' + (iterLen == 0 ? "" : to_string(iterLen)) + "]!";
}

bool LgsSArray::equals(LgsType* other) {
    const auto otherArr = other->asDArray();
    if (!otherArr) return false;
    if (!baseType->equals(otherArr->baseType)) return false;
    return sizeExpr->type->equals(otherArr->sizeExpr->type);;
}

string LgsSArray::getIRName() {
    return name;
}

Value* LgsSArray::getLength(LgsModule* module, LgsExpr* expr) {
    return sizeExpr->getIRValue(module);
}

Value* LgsSArray::getLoopLength(LgsModule* module, LgsExpr* expr) {
    return getLength(module, expr);
}

Value* LgsSArray::isEmpty(LgsModule* module, LgsExpr* expr) {
    assert(0);
}

Value* LgsSArray::isNotEmpty(LgsModule* module, LgsExpr* expr) {
    assert(0);
}

LgsSArray::~LgsSArray() {
    delete sizeExpr;
}
