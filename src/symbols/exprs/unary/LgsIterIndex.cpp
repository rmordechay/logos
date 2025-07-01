#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"
#include <exprs/unary/LgsArrayExpr.h>
#include "types/LgsMap.h"
#include "utils/LgsUtils.h"

Value* LgsIterIndex::createIRValue(LgsModule* runtime) {
    const auto baseExprType = baseExpr->type;
    if (const auto arr = baseExprType->asArray()) {
        return getIRFromArray(runtime, arr);
    }
    if (const auto map = baseExprType->asMap()) {
        return getIRFromMap(runtime, map);
    }
    if (const auto str = baseExprType->asStr()) {
        return getIRFromStr(runtime, str);
    }
    assert(0);
}

Value* LgsIterIndex::getIRFromStr(LgsModule* runtime, LgsStr* str) const {
    if (index->to) return getStrSlice(runtime, str);
    if (str->isStatic) return getStrGEP(runtime);
    const auto baseExprIRValue = baseExpr->getIRValue(runtime);
    const auto baseExprIRType = baseExpr->type->getIRType(runtime->context);
    if (str->isStatic) {
        const auto ty = str->getIRType(runtime->context);
        const auto valueFrom = index->from->getIRValue(runtime);
        return runtime->builder.CreateGEP(ty, baseExprIRValue, {runtime->builder.getInt32(0), valueFrom});
    }
    const auto ptr = runtime->builder.CreateAlloca(baseExprIRType);
    const auto vaArgInst = runtime->builder.CreateVAArg(baseExprIRValue, baseExprIRType);
    runtime->builder.CreateStore(vaArgInst, ptr);
    return runtime->builder.CreateLoad(baseExprIRType, ptr);
}

Value* LgsIterIndex::getIRFromArray(LgsModule* runtime, LgsArray* arr) const {
    if (arr->isStatic) return getArrGEP(runtime);
    auto& builder = runtime->builder;
    const auto arrPtr = baseExpr->getIRValue(runtime);
    auto indexIRValue = index->from->getIRValue(runtime);
    indexIRValue = builder.CreateZExt(indexIRValue, builder.getInt64Ty());
    return arr->getFunc.callIR(runtime, {arrPtr, indexIRValue});
}

Value* LgsIterIndex::getIRFromMap(LgsModule* runtime, LgsMap* map) const {
    const auto mapPtr = baseExpr->getIRValue(runtime);
    const auto key = index->from->getIRValue(runtime);
    const auto keyIRType = key->getType();
    const auto keyPtr = runtime->builder.CreateAlloca(keyIRType);
    runtime->builder.CreateStore(key, keyPtr);
    const auto keyLoad = runtime->builder.CreateLoad(keyIRType, keyPtr);
    return map->getFunc.callIR(runtime, {mapPtr, keyLoad});
}

Value* LgsIterIndex::getStrSlice(LgsModule* runtime, const LgsStr* str) const {
    if (str->isStatic) {
        const auto intFrom = index->from->asIntConst();
        const auto intTo = index->to->asIntConst();
        const auto strConst = baseExpr->getConstStr();
        return getIRStr(runtime, strConst.substr(intFrom->value, intTo->value));
    }
    assert(0);
}

Value* LgsIterIndex::getStrGEP(LgsModule* runtime) const {
    const auto ty = baseExpr->type->getIRType(runtime->context);
    const auto value = baseExpr->getIRValue(runtime);
    const auto iValue = index->from->getIRValue(runtime);
    return runtime->builder.CreateGEP(ty, value, {runtime->builder.getInt32(0), iValue});
}

Value* LgsIterIndex::getArrGEP(LgsModule* runtime) const {
    vector<Value*> IRIndices = {};
    Type* ty = nullptr;
    Value* ptr = nullptr;
    auto iterIndex = this;
    while (true) {
        auto irValue = iterIndex->index->from->getIRValue(runtime);
        IRIndices.push_back(irValue);
        const auto innerIterIndex = iterIndex->baseExpr->asIterIndex();
        if (innerIterIndex) {
            iterIndex = innerIterIndex;
        } else {
            ptr = iterIndex->baseExpr->getIRValue(runtime);
            ty = iterIndex->baseExpr->type->getIRType(runtime->context);
            IRIndices.push_back(runtime->builder.getInt32(0));
            break;
        }
    }
    reverse(IRIndices.begin(), IRIndices.end());
    return runtime->builder.CreateGEP(ty, ptr, IRIndices);
}

string LgsIterIndex::getExprName() {
    return baseExpr->getExprName();
}

string LgsIterIndex::prettyName() {
    stringstream str;
    str << baseExpr->prettyName();
    if (index->to) {
        str << '[' << index->from->prettyName() << ':' << index->to->prettyName() << ']';
    } else {
        str << '[' << index->from->prettyName() << ']';
    }
    return str.str();
}

LgsIterIndex::~LgsIterIndex() {
    delete baseExpr;
    delete index->from;
    delete index->to;
    delete index;
}
