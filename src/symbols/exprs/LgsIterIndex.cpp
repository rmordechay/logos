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
    if (baseExprType->asSArray()) {
        std::vector<Value*> indices;
        auto nestedIterIndex = this;
        while (true) {
            indices.push_back(nestedIterIndex->index.from->IRValue);
            if (const auto innerIterIndex = nestedIterIndex->baseExpr->asIterIndex()) {
                nestedIterIndex = innerIterIndex;
            } else {
                indices.push_back(cg.i32Zero());
                reverse(indices.begin(), indices.end());
                IRValue = cg.builder.CreateGEP(nestedIterIndex->baseExpr->type->getIRType(cg), nestedIterIndex->baseExpr->IRValue, indices);
                break;
            }
        }
    } else if (baseExprType->asStr()) {
        IRValue = cg.builder.CreateGEP(cg.i8Ty(), baseExprIR, {cg.i32Zero(), fromIR});
    } else if (inAssignment) {
        return;
    } else if (const auto map = baseExpr->type->asMap()) {
        IRValue = map->getIRElement(cg, baseExprIR, fromIR);
    } else if (const auto iter = baseExpr->type->asIterable()) {
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
