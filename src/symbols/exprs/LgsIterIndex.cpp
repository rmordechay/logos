#include "exprs/LgsIterIndex.h"
#include "exprs/LgsVariable.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsVoid.h"
#include <exprs/LgsArrayExpr.h>
#include "types/iterables/LgsMap.h"
#include "types/iterables/LgsVec.h"

Value* LgsIterIndex::loadIR(LgsLLVMGen& cg) {
    const auto baseExprType = baseExpr->type;
    if (baseExprType->asMap() || baseExprType->asDArray() || baseExprType->asSet()) {
        const auto arr = baseExpr->type->asIterable();
        const auto valueTy = arr->baseType->getIRType(cg);
        return cg.builder.CreateLoad(valueTy, IRValue);
    }
    if (baseExprType->asSArray()) {
        return loadFromSArray(cg);
    }
    if (baseExprType->asVec()) {
        const auto vec = cg.builder.CreateLoad(baseExpr->type->getIRType(cg), IRValue);
        const auto i = index.from->IRValue;
        return cg.builder.CreateExtractElement(vec, i);
    }
    if (baseExprType->asStr()) {
        if (index.to) assert(0);
        return cg.builder.CreateLoad(cg.i8Ty(), IRValue);
    }
    assert(0);
}

void LgsIterIndex::setIRElementPtr(LgsLLVMGen& cg) {
    const auto baseExprType = baseExpr->type;
    auto indexIRValue = index.from->IRValue;
    if (const auto sArr = baseExprType->asSArray()) {
        IRValue = cg.builder.CreateGEP(sArr->baseType->getIRType(cg), baseExpr->IRValue, index.from->IRValue);
    } else if (const auto dArr = baseExpr->type->asDArray()) {
        indexIRValue = cg.builder.CreateZExt(indexIRValue, cg.i64Ty());
        IRValue = dArr->getIRElement(cg, baseExpr->IRValue, indexIRValue);
    } else if (const auto set = baseExpr->type->asSet()) {
        indexIRValue = cg.builder.CreateZExt(indexIRValue, cg.i64Ty());
        IRValue = set->getIRElement(cg, baseExpr->IRValue, indexIRValue);
    } else if (const auto vec = baseExprType->asVec()) {
        indexIRValue = cg.builder.CreateZExt(indexIRValue, cg.i64Ty());
        IRValue = vec->getIRElement(cg, baseExpr->IRValue, indexIRValue);
    } else if (const auto map = baseExpr->type->asMap()) {
        const auto key = index.from->IRValue;
        IRValue = map->getIRElement(cg, baseExpr->IRValue, key);
    } else if (baseExprType->asStr()) {
        if (index.to) {
            const auto intFrom = index.from->asIntConst();
            const auto intTo = index.to->asIntConst();
            const auto strConst = baseExpr->getConstStr();
            IRValue = cg.getIRStr(strConst.substr(intFrom->value, intTo->value));
        } else {
            IRValue = cg.builder.CreateGEP(cg.i8Ty(), baseExpr->IRValue, {cg.i32Zero(), index.from->IRValue});
        }
    }
    assert(IRValue);
}

Value* LgsIterIndex::loadFromSArray(LgsLLVMGen& cg) const {
    std::vector<Value*> IRIndices;
    Type* ty = nullptr;
    Value* ptr = nullptr;
    auto iterIndex = this;
    while (true) {
        auto indexIR = iterIndex->index.from->IRValue;
        IRIndices.push_back(indexIR);
        const auto innerIterIndex = iterIndex->baseExpr->asIterIndex();
        if (innerIterIndex) {
            iterIndex = innerIterIndex;
        } else {
            ptr = iterIndex->IRValue;
            ty = iterIndex->baseExpr->type->getIRType(cg);
            IRIndices.push_back(cg.i32Zero());
            break;
        }
    }
    reverse(IRIndices.begin(), IRIndices.end());
    const auto gep = cg.builder.CreateGEP(ty, ptr, IRIndices);
    return cg.builder.CreateLoad(type->getIRType(cg), gep);
}

void LgsIterIndex::assign(LgsLLVMGen& cg, LgsExpr* expr) {
    if (const auto map = expr->asHashMap()) {
        assignHashMap(cg, map);
    } else if (const auto arr = expr->asArrayExpr()) {
        assignArray(cg, arr);
    } else {
        assignScalar(cg, expr);
    }
}

void LgsIterIndex::assignScalar(LgsLLVMGen& cg, LgsExpr* expr) const {
    const auto rIRValue = expr->IRValue;
    const auto baseIRValue = baseExpr;
    if (const auto arr = baseExpr->type->asDArray()) {
        const auto ptr = cg.builder.CreateAlloca(expr->type->getIRType(cg));
        cg.builder.CreateStore(rIRValue, ptr);
        LgsFunc putFunc("put", &LGS_VOID, {arr, &LGS_INT, &LGS_ANY}, BUILTIN | METHOD);
        putFunc.callIR(cg, {baseIRValue->IRValue, index.from->IRValue, ptr});
        return;
    }
    if (baseExpr->type->asSArray()) {
        cg.builder.CreateStore(rIRValue, loadFromSArray(cg));
        return;
    }
    if (const auto map = baseExpr->type->asMap()) {
        map->getAddFunc()->callIR(cg, {baseExpr->IRValue, index.from->IRValue, expr->IRValue});
    } else {
        cg.builder.CreateStore(rIRValue, IRValue);
    }
}

void LgsIterIndex::assignArray(LgsLLVMGen& cg, const LgsArrayExpr* arr) const {
    assert(0);
}

void LgsIterIndex::assignHashMap(LgsLLVMGen& cg, LgsHashMap* map) {
    assert(0);
}

std::string LgsIterIndex::getName() {
    std::stringstream str;
    str << baseExpr->getName();
    if (index.to) {
        str << '[' << index.from->getName() << ':' << index.to->getName() << ']';
    } else {
        str << '[' << index.from->getName() << ']';
    }
    return str.str();
}

json::value LgsIterIndex::asJsonStr() {
    json::object jsonObj;
    jsonObj["exprType"] = "iterIndex";
    jsonObj["from"] = index.from->asJsonStr();
    if (index.to) jsonObj["to"] = index.to->asJsonStr();
    jsonObj["baseExpr"] = baseExpr->asJsonStr();
    return jsonObj;
}

LgsIterIndex::~LgsIterIndex() {
    if (!baseExpr->asVariable()) {
        freeExpr(baseExpr);
    }
    freeExpr(index.from);
    freeExpr(index.to);
    baseExpr = nullptr;
    index.from = nullptr;
    index.to = nullptr;
}
