#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"

size_t LgsStr::getSizeBytes() {
    return initialLength + 1;
}

string LgsStr::getName() {
    return name;
}

Type* LgsStr::getIRType(LgsModule* module) {
    return ArrayType::get(baseType->getIRType(module), initialLength);
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

Value* LgsStr::getLength(LgsModule* module, LgsExpr* expr) {
    return lenFunc.call(module, {expr});
}

Value* LgsStr::getLoopLength(LgsModule* module, LgsExpr* expr) {
    const auto i32Ty = module->builder.getInt64Ty();
    const auto lenPtr = module->builder.CreateAlloca(i32Ty);
    module->builder.CreateStore(getLength(module, expr), lenPtr);
    return module->builder.CreateLoad(i32Ty, lenPtr);
}

Value* LgsStr::isEmpty(LgsModule* module, LgsExpr* expr) {
    return isEmptyFunc.call(module, {expr});
}

Value* LgsStr::isNotEmpty(LgsModule* module, LgsExpr* expr) {
    return isNotEmptyFunc.call(module, {expr});
}

bool LgsStr::equals(LgsType* other) {
    assert(other);
    if (other->getName() == LgsAny::name) return true;
    return name == other->getName();
}
