#include "types/LgsDArray.h"
#include "builtins/LgsPrint.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "types/primitives/LgsInt.h"

Value* LgsDArray::callAdd(LgsCodeGen& codeGen, const std::vector<LgsExpr*>& args) const {
    const auto arr = args[0];
    const auto exprToAdd = args[1];
    const auto exprIR = exprToAdd->IRValue;
    const auto arrPtr = arr->IRValue;
    const auto exprTy = exprToAdd->type;
    const auto ptr = codeGen.builder.CreateAlloca(exprTy->getIRType(codeGen));
    codeGen.builder.CreateStore(exprIR, ptr);
    return addFunc->callIR(codeGen, {arrPtr, ptr});
}

Type* LgsDArray::getIRType(LgsCodeGen& codeGen) {
    if (IRType) return IRType;
    return getArrStruct(&codeGen);
}

std::string LgsDArray::getName() {
    return name;
}

std::string LgsDArray::pname() {
    assert(baseType);
    return baseType->pname() + "[]";
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

uint16_t LgsDArray::getUnpackCount() const {
    return 1;
}

std::string LgsDArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

StructType* LgsDArray::getArrStruct(LgsCodeGen* codeGen) {
    if (arrStruct) return arrStruct;
    arrStruct = codeGen->getStructType({codeGen->i64Ty(), codeGen->i64Ty(), codeGen->i64Ty(), codeGen->ptrTy()}, name);
    return arrStruct;
}

void LgsDArray::freeValue(LgsCodeGen& codeGen, Value* value) {
    freeFunc->callIR(codeGen, {value});
}

Value* LgsDArray::IRLength(LgsCodeGen& codeGen, LgsExpr* iterable) {
    return lenFunc->call(codeGen, {iterable});
}

Value* LgsDArray::IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isEmptyFunc->call(*codeGen, {iterable});
}

Value* LgsDArray::IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isNotEmptyFunc->call(*codeGen, {iterable});
}

bool LgsDArray::canCastTo(LgsType* other) {
    const auto otherArr = other->asDArray();
    if (!otherArr) return false;
    if (!baseType) return true;
    return baseType->canCastTo(otherArr->baseType);
}

json::value LgsDArray::asJSON() {
    json::object jsonObj;
    jsonObj["name"] = name;
    return jsonObj;
}
