#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "types/map/LgsMap.h"
#include <exprs/unary/LgsArrayExpr.h>

Value* LgsIterIndex::createIRValue(CodegenMetadata* metadata) {
    const auto baseExprType = baseExpr->type;
    if (const auto arr = baseExprType->asArray()) {
        if (arr->isStatic) return getGEP(metadata);
        return getIRFromDynArray(metadata, arr);
    }
    if (const auto map = baseExprType->asMap()) {
        return getIRFromMap(metadata, map);
    }
    if (baseExprType->asStr()) {
        return getIRFromStr(metadata);
    }
    assert(false);
}

// ; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
// define i32 @main() #0 {
//   %2 = alloca %struct.Array, align 8
//   %3 = alloca %struct.Array, align 8
//   %4 = alloca ptr, align 8
//   %5 = alloca i32, align 4
//   %6 = alloca i32, align 4
//   %7 = alloca ptr, align 8
//   %8 = alloca ptr, align 8
//   call void @Array_init(ptr noundef %2, i32 noundef 2, i64 noundef 8)
//   call void @Array_init(ptr noundef %3, i32 noundef 2, i64 noundef 4)
//   store ptr %3, ptr %4, align 8
//   call void @Array_add(ptr noundef %2, ptr noundef %4)
//   store i32 43, ptr %5, align 4
//   call void @Array_add(ptr noundef %3, ptr noundef %5)
//   store i32 234, ptr %6, align 4
//   call void @Array_add(ptr noundef %3, ptr noundef %6)
//   %9 = call ptr @Array_get(ptr noundef %2, i32 noundef 0)
//   store ptr %9, ptr %7, align 8
//   %10 = load ptr, ptr %7, align 8
//   %11 = load ptr, ptr %10, align 8
//   %12 = call ptr @Array_get(ptr noundef %11, i32 noundef 1)
//   store ptr %12, ptr %8, align 8
//   %13 = load ptr, ptr %8, align 8
//   %14 = load i32, ptr %13, align 4
//   %15 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %14)
//   ret i32 0
// }

Value* LgsIterIndex::getIRFromDynArray(CodegenMetadata* metadata, LgsArray* arr) const {
    const auto arrPtr = baseExpr->getIRValue(metadata);
    const auto indexIRValue = index->from->getIRValue(metadata);
    const auto rv = arr->get.callIR(metadata, {arrPtr, indexIRValue});
    return metadata->builder.CreateLoad(ptrTy, rv);
}

Value* LgsIterIndex::getIRFromMap(CodegenMetadata* metadata, LgsMap* map) const {
    const auto mapPtr = baseExpr->getIRValue(metadata);
    const auto indexIRValue = index->from->getIRValue(metadata);
    return map->get.callIR(metadata, {mapPtr, indexIRValue});
}

Value* LgsIterIndex::getIRFromStr(CodegenMetadata* metadata) const {
    const auto baseExprIRValue = baseExpr->getIRValue(metadata);
    const auto baseExprIRType = baseExpr->type->getIRType();
    if (const auto global = dyn_cast<GlobalVariable>(baseExprIRValue)) {
        const auto ty = global->getValueType();
        const auto value = index->from->getIRValue(metadata);
        return metadata->builder.CreateGEP(ty, baseExprIRValue, {i32Zero, value});
    }
    const auto p = metadata->builder.CreateAlloca(baseExprIRType);
    const auto vaArgInst = metadata->builder.CreateVAArg(baseExprIRValue, baseExprIRType);
    metadata->builder.CreateStore(vaArgInst, p);
    return metadata->builder.CreateLoad(baseExprIRType, p);
}

void LgsIterIndex::storeHashMap(CodegenMetadata* metadata, LgsHashMap* hashMap) const {
    assert(false);
}

void LgsIterIndex::storeScalar(CodegenMetadata* metadata, LgsExpr* value) {
    const auto rValue = value->getIRValue(metadata);
    if (const auto arr = baseExpr->type->asArray()) {
        if (!arr->isStatic) {
            const auto ptr = metadata->builder.CreateAlloca(value->type->getIRType());
            metadata->builder.CreateStore(rValue, ptr);
            arr->put.callIR(metadata, {baseExpr->getIRValue(metadata), index->from->getIRValue(metadata), ptr});
            return;
        }
    }
    const auto iterPtr = getIRValue(metadata);
    metadata->builder.CreateStore(rValue, iterPtr);
}

void LgsIterIndex::storeArray(CodegenMetadata* metadata, const LgsArrayExpr* arr) const {
    if (!arr->arrType.isStatic) assert(false);
    const auto IRType = baseExpr->type->getIRType();
    const auto arrPtr = baseExpr->getIRValue(metadata);
    vector IRIndices = {i32Zero};
    vector<LgsIndex*> indices;
    setIterIndices(this, indices);
    for (const auto index : indices) {
        IRIndices.emplace_back(index->from->getIRValue(metadata));
    }
    for (int i = 0; i < arr->initialElements.size(); ++i) {
        const auto element = arr->initialElements[i];
        const auto IRIndex = metadata->builder.getInt32(i);
        IRIndices.push_back(IRIndex);
        const auto gep = metadata->builder.CreateGEP(IRType, arrPtr, IRIndices);
        const auto rValue = element->getIRValue(metadata);
        metadata->builder.CreateStore(rValue, gep);
        IRIndices.pop_back();
    }
}

Value* LgsIterIndex::getGEP(CodegenMetadata* metadata) const {
    vector<Value*> IRIndices = {};
    Type* ty = nullptr;
    Value* ptr = nullptr;
    auto iterIndex = this;
    while (true) {
        auto irValue = iterIndex->index->from->getIRValue(metadata);
        IRIndices.push_back(irValue);
        const auto innerIterIndex = iterIndex->baseExpr->asIterIndex();
        if (innerIterIndex) {
            iterIndex = innerIterIndex;
        } else {
            ptr = iterIndex->baseExpr->getIRValue(metadata);
            ty = iterIndex->baseExpr->type->getIRType();
            IRIndices.push_back(i32Zero);
            break;
        }
    }
    reverse(IRIndices.begin(), IRIndices.end());
    return metadata->builder.CreateGEP(ty, ptr, IRIndices);
}

Value* LgsIterIndex::getLength(CodegenMetadata* metadata) {
    assert(false);
}

string LgsIterIndex::getName() {
    return baseExpr->getName();
}

string LgsIterIndex::prettyName() {
    stringstream str;
    str << baseExpr->prettyName();
    str << '[' << index->from->prettyName() << ']';
    return str.str();
}

LgsIterIndex::~LgsIterIndex() {
    delete baseExpr;
    delete index->from;
    delete index->to;
    delete index;
}
