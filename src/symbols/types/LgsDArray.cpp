#include "types/LgsDArray.h"
#include "builtins/LgsBuiltins.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "types/primitives/LgsInt.h"

Type* LgsDArray::getIRType(LgsCodeGen* codeGen) {
    if (IRType) return IRType;
    return getArrStruct(codeGen);
}

size_t LgsDArray::getSizeBytes() {
    return sizeof(size_t) + sizeof(size_t) + sizeof(size_t) + sizeof(void*);
}

LgsExpr* LgsDArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

LgsType* LgsDArray::getIndexType() {
    return &LGS_INT;
}

string LgsDArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

string LgsDArray::prettyName() {
    return baseType->prettyName() + "[]";
}

bool LgsDArray::equals(LgsType* other) {
    const auto otherArr = other->asDArray();
    if (!otherArr) return false;
    return baseType->equals(otherArr->baseType);
}

void LgsDArray::freeValue(LgsCodeGen* codeGen, Value* value) {
    freeFunc.callIR(codeGen, {value});
}

string LgsDArray::getName() {
    return name;
}

Value* LgsDArray::IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return lenFunc.call(codeGen, {iterable});
}

Value* LgsDArray::IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isEmptyFunc.call(codeGen, {iterable});
}

Value* LgsDArray::IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isNotEmptyFunc.call(codeGen, {iterable});
}

StructType* LgsDArray::getArrStruct(LgsCodeGen* codeGen) {
    if (arrStruct) return arrStruct;
    arrStruct = codeGen->getStructType({codeGen->i64Ty(), codeGen->i64Ty(), codeGen->i64Ty(), codeGen->ptrTy()}, name);
    return arrStruct;
}

Value* LgsArrayAddFunc::call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) {
    const auto arr = args[0];
    const auto exprToAdd = args[1];
    const auto exprIR = exprToAdd->getIRValue(codeGen);
    const auto arrPtr = arr->getIRValue(codeGen);
    const auto exprTy = exprToAdd->type;
    if (exprTy->asBool()) return addBoolFunc.callIR(codeGen, {arrPtr, exprIR});
    if (exprTy->asChar()) return addByteFunc.callIR(codeGen, {arrPtr, exprIR});
    if (exprTy->asShort()) return addShortFunc.callIR(codeGen, {arrPtr, exprIR});
    if (exprTy->asInt()) return addIntFunc.callIR(codeGen, {arrPtr, exprIR});
    if (exprTy->asLong()) return addLongFunc.callIR(codeGen, {arrPtr, exprIR});
    return callIR(codeGen, {arrPtr, exprIR});
}

LgsDArray::~LgsDArray() {
    delete sizeExpr;
}
