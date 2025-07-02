#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"
#include <exprs/unary/LgsArrayExpr.h>
#include "types/LgsMap.h"
#include "utils/LgsUtils.h"

Value* LgsIterIndex::createIRValue(LgsModule* module) {
    const auto baseExprType = baseExpr->type;
    if (const auto arr = baseExprType->asArray()) {
        return getIRFromArray(module, arr);
    }
    if (const auto map = baseExprType->asMap()) {
        return getIRFromMap(module, map);
    }
    if (const auto str = baseExprType->asStr()) {
        return getIRFromStr(module, str);
    }
    assert(0);
}

Value* LgsIterIndex::getIRFromStr(LgsModule* module, LgsStr* str) const {
    if (index->to) return getStrSlice(module, str);
    if (str->isStatic) return getStrGEP(module);
    const auto baseExprIRValue = baseExpr->getIRValue(module);
    const auto baseExprIRType = baseExpr->type->getIRType(module->context);
    if (str->isStatic) {
        const auto ty = str->getIRType(module->context);
        const auto valueFrom = index->from->getIRValue(module);
        return module->builder.CreateGEP(ty, baseExprIRValue, {module->builder.getInt32(0), valueFrom});
    }
    const auto ptr = module->builder.CreateAlloca(baseExprIRType);
    const auto vaArgInst = module->builder.CreateVAArg(baseExprIRValue, baseExprIRType);
    module->builder.CreateStore(vaArgInst, ptr);
    return module->builder.CreateLoad(baseExprIRType, ptr);
}

Value* LgsIterIndex::getIRFromArray(LgsModule* module, LgsArray* arr) const {
    if (arr->isStatic) return getArrGEP(module);
    auto& builder = module->builder;
    const auto arrPtr = baseExpr->getIRValue(module);
    auto indexIRValue = index->from->getIRValue(module);
    indexIRValue = builder.CreateZExt(indexIRValue, builder.getInt64Ty());
    return arr->getFunc.callIR(module, {arrPtr, indexIRValue});
}

Value* LgsIterIndex::getIRFromMap(LgsModule* module, LgsMap* map) const {
    const auto mapPtr = baseExpr->getIRValue(module);
    const auto key = index->from->getIRValue(module);
    const auto keyIRType = key->getType();
    const auto keyPtr = module->builder.CreateAlloca(keyIRType);
    module->builder.CreateStore(key, keyPtr);
    const auto keyLoad = module->builder.CreateLoad(keyIRType, keyPtr);
    return map->getFunc.callIR(module, {mapPtr, keyLoad});
}

Value* LgsIterIndex::getStrSlice(LgsModule* module, const LgsStr* str) const {
    if (str->isStatic) {
        const auto intFrom = index->from->asIntConst();
        const auto intTo = index->to->asIntConst();
        const auto strConst = baseExpr->getConstStr();
        return getIRStr(module, strConst.substr(intFrom->value, intTo->value));
    }
    assert(0);
}

Value* LgsIterIndex::getStrGEP(LgsModule* module) const {
    const auto ty = baseExpr->type->getIRType(module->context);
    const auto value = baseExpr->getIRValue(module);
    const auto iValue = index->from->getIRValue(module);
    return module->builder.CreateGEP(ty, value, {module->builder.getInt32(0), iValue});
}

Value* LgsIterIndex::getArrGEP(LgsModule* module) const {
    vector<Value*> IRIndices = {};
    Type* ty = nullptr;
    Value* ptr = nullptr;
    auto iterIndex = this;
    while (true) {
        auto irValue = iterIndex->index->from->getIRValue(module);
        IRIndices.push_back(irValue);
        const auto innerIterIndex = iterIndex->baseExpr->asIterIndex();
        if (innerIterIndex) {
            iterIndex = innerIterIndex;
        } else {
            ptr = iterIndex->baseExpr->getIRValue(module);
            ty = iterIndex->baseExpr->type->getIRType(module->context);
            IRIndices.push_back(module->builder.getInt32(0));
            break;
        }
    }
    reverse(IRIndices.begin(), IRIndices.end());
    return module->builder.CreateGEP(ty, ptr, IRIndices);
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
