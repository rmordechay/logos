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
        const auto indexIR = index.from->IRValue;
        const auto ptr = dyn_cast<GetElementPtrInst>(IRValue);
        const auto ty = baseExpr->type->getIRType(cg);
        const auto gep = cg.builder.CreateGEP(ty, ptr, {cg.i32Zero(), indexIR});
        return cg.builder.CreateLoad(type->getIRType(cg), gep);
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

void LgsIterIndex::assign(LgsLLVMGen& cg, LgsExpr* expr) {
    const auto rIRValue = expr->IRValue;
    const auto baseIRValue = baseExpr;
    auto indexIR = index.from->IRValue;
    if (baseExpr->type->asDArray() || baseExpr->type->asSet()) {
        const auto args = {baseIRValue->IRValue, indexIR, cg.getPtr(rIRValue)};
        cg.callLgsFunc("put", cg.voidTy(), {cg.ptrTy(), cg.i32Ty(), cg.ptrTy()}, args);
    } else if (const auto map = baseExpr->type->asMap()) {
        map->getAddFunc()->callIR(cg, {baseExpr->IRValue, indexIR, expr->IRValue});
    } else {
        cg.builder.CreateStore(rIRValue, IRValue);
    }
}

void LgsIterIndex::assignScalar(LgsLLVMGen& cg, LgsExpr* expr) const {
    const auto rIRValue = expr->IRValue;
    const auto baseIRValue = baseExpr;
    auto indexIR = index.from->IRValue;
    if (baseExpr->type->asDArray() || baseExpr->type->asSet()) {
        const auto args = {baseIRValue->IRValue, indexIR, cg.getPtr(rIRValue)};
        cg.callLgsFunc("put", cg.voidTy(), {cg.ptrTy(), cg.i32Ty(), cg.ptrTy()}, args);
    } else if (const auto map = baseExpr->type->asMap()) {
        map->getAddFunc()->callIR(cg, {baseExpr->IRValue, indexIR, expr->IRValue});
    } else {
        cg.builder.CreateStore(rIRValue, IRValue);
    }
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
