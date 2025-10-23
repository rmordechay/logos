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
    if (baseExprType->asStr()) {
        return cg.builder.CreateLoad(cg.i8Ty(), IRValue);
    }
    if (baseExprType->asSArray()) {
        const auto indexIR = index.from->IRValue;
        const auto ty = baseExpr->type->getIRType(cg);
        const auto gep = cg.builder.CreateGEP(ty, IRValue, {cg.i32Zero(), indexIR});
        return cg.builder.CreateLoad(type->getIRType(cg), gep);
    }
    if (baseExprType->asVec()) {
        const auto vec = cg.builder.CreateLoad(baseExpr->type->getIRType(cg), IRValue);
        const auto i = index.from->IRValue;
        return cg.builder.CreateExtractElement(vec, i);
    }
    assert(0);
}

LgsExpr* LgsIterIndex::getBaseExpr() const {
    auto nestedIterIndex = this;
    while (true) {
        if (const auto innerIterIndex = nestedIterIndex->baseExpr->asIterIndex()) {
            nestedIterIndex = innerIterIndex;
        } else {
            return nestedIterIndex->baseExpr;
        }
    }
}

void LgsIterIndex::setIRElementPtr(LgsLLVMGen& cg, const bool inAssignment) {
    auto fromIR = index.from->IRValue;
    const auto baseExprType = baseExpr->type;
    const auto baseExprIR = baseExpr->IRValue;
    const auto baseTyIR = baseExprType->getIRType(cg);
    assert(baseExprIR);
    if (baseExprType->asSArray()) {
        IRValue = cg.builder.CreateInBoundsGEP(baseTyIR, baseExprIR, fromIR);
        if (type->getIRType(cg)->isPointerTy()) {
            IRValue = cg.builder.CreateLoad(cg.ptrTy(), IRValue);
        }
        return;
    }
    if (baseExprType->asStr()) {
        IRValue = cg.builder.CreateInBoundsGEP(cg.i8Ty(), baseExprIR, fromIR);
        return;
    }
    if (inAssignment) return;
    if (const auto map = baseExprType->asMap()) {
        IRValue = map->getIRElement(cg, baseExprIR, fromIR);
    } else if (const auto iter = baseExprType->asIterable()) {
        fromIR = cg.builder.CreateZExt(fromIR, cg.i64Ty());
        IRValue = iter->getIRElement(cg, baseExprIR, fromIR);
    }
    assert(IRValue);
}

void LgsIterIndex::assign(LgsLLVMGen& cg, LgsExpr* expr) {
    const auto rIRValue = expr->IRValue;
    const auto baseIRValue = baseExpr;
    auto indexIR = index.from->IRValue;
    if (baseExpr->type->asDArray() || baseExpr->type->asSet()) {
        const auto args = {baseIRValue->IRValue, indexIR, cg.getPtrTo(rIRValue)};
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
        const auto args = {baseIRValue->IRValue, indexIR, cg.getPtrTo(rIRValue)};
        cg.callLgsFunc("put", cg.voidTy(), {cg.ptrTy(), cg.i32Ty(), cg.ptrTy()}, args);
    } else if (const auto map = baseExpr->type->asMap()) {
        map->getAddFunc()->callIR(cg, {baseExpr->IRValue, indexIR, expr->IRValue});
    } else {
        cg.builder.CreateStore(rIRValue, IRValue);
    }
}

std::string LgsIterIndex::asText() {
    std::stringstream str;
    str << baseExpr->asText();
    if (index.to) {
        str << '[' << index.from->asText() << ':' << index.to->asText() << ']';
    } else {
        str << '[' << index.from->asText() << ']';
    }
    return str.str();
}

Type* LgsIterIndex::getSArrayType(LgsLLVMGen& cg) const {
    auto current = this;
    while (true) {
        if (const auto nextIndex = current->baseExpr->asIterIndex()) {
            current = nextIndex;
        } else {
            return current->baseExpr->type->getIRType(cg);
        }
    }
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
