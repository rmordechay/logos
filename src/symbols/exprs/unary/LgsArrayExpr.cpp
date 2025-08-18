#include "exprs/unary/LgsArrayExpr.h"
#include "cli/LgsCli.h"
#include "exprs/unary/LgsIterIndex.h"

#include <llvm/IR/Module.h>

std::string LgsArrayExpr::pname() {
    return type->pname();
}

json::object LgsArrayExpr::asJSON() {
    json::object obj;
    return obj;
}

void LgsArrayExpr::createIRValue(LgsCodeGen* codeGen) {
    if (type->asSArray()) IRValue = createConstArray(codeGen);
    else if (type->asDArray()) IRValue = createDynamicArray(codeGen);
    else assert(0);
}

Value* LgsArrayExpr::createDynamicArray(LgsCodeGen* codeGen) {
    const auto arr = type->asDArray();
    const auto dl = codeGen->IRModule->getDataLayout();
    const auto size = dl.getTypeAllocSize(arr->baseType->getIRType(codeGen));
    const auto elementSize = codeGen->i64(size);
    const auto arrSize = codeGen->typeSize(arr->getArrStruct(codeGen));
    IRValue = codeGen->callMalloc(arrSize.getFixedValue());
    arr->initFunc->callIR(codeGen, {IRValue, elementSize});
    return IRValue;
}

bool LgsArrayExpr::castTo(LgsType* toType) {
    return true;
}

Value* LgsArrayExpr::createConstArray(LgsCodeGen* codeGen) const {
    auto& builder = codeGen->builder;
    const auto arr = type->asSArray();
    const auto baseType = arr->baseType;
    const auto baseIRType = baseType->getIRType(codeGen);
    const auto arrIRType = ArrayType::get(baseIRType, arr->sizeExpr->getConstInt());
    const auto arrIRPtr = builder.CreateAlloca(arrIRType);
    if (initialElements.empty()) return arrIRPtr;
    for (int i = 0; i < initialElements.size(); ++i) {
        const auto gep = builder.CreateGEP(arrIRType, arrIRPtr, {codeGen->i32Zero(), codeGen->i32(i)});
        const auto val = initialElements[i]->getIRValue(codeGen);
        builder.CreateStore(val, gep);
    }
    return arrIRPtr;
}
