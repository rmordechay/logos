#include "exprs/LgsIterIndex.h"
#include "funcs/LgsFunc.h"
#include <exprs/LgsArrayExpr.h>
#include "types/iterables/LgsMap.h"
#include "types/iterables/LgsVec.h"
#include "LgsUtils.h"
#include "types/iterables/LgsMatrix.h"

#include <sstream>
#include <llvm/IR/Module.h>

Value* LgsIterIndex::loadIR(LgsCgModule& cg) {
    const auto baseExprType = baseExpr->type;
    if (baseExprType->asMap() || baseExprType->asDArray() || baseExprType->asSet()) {
        const auto arr = baseExpr->type->asIterable();
        const auto valueTy = arr->baseType->getIRType(cg);
        return cg.builder.CreateLoad(valueTy, IRValue);
    }
    if (baseExprType->asStr()) {
        return cg.builder.CreateLoad(cg.i8Ty(), IRValue);
    }
    if (baseExprType->asMatrix()) {
        assert(0);
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

void LgsIterIndex::setIRElementPtr(LgsCgModule& cg, const bool assign) {
    auto fromIR = index.from->IRValue;
    assert(baseExpr->IRValue);
    // SArray
    if (const auto sArr = baseExpr->type->asSArray()) {
        const auto ty = type->getIRType(cg);
        cg.createBoundsGuard(sArr->size->IRValue, fromIR);
        IRValue = cg.builder.CreateInBoundsGEP(ty, baseExpr->IRValue, fromIR);
        if (ty->isPointerTy()) {
            IRValue = cg.builder.CreateLoad(cg.ptrTy(), IRValue);
        }
        return;
    }

    // String
    if (baseExpr->type->asStr()) {
        IRValue = cg.builder.CreateInBoundsGEP(cg.i8Ty(), baseExpr->IRValue, fromIR);
        return;
    }
    if (assign) return;

    // Map
    if (const auto map = baseExpr->type->asMap()) {
        IRValue = map->getIRElement(cg, baseExpr->IRValue, fromIR);
        return;
    }

    // Matrix
    if (const auto matrix = baseExpr->type->asMatrix()) {
        cg.createBoundsGuard(cg.i32(matrix->rows), fromIR);
        IRValue = matrix->getIRElement(cg, baseExpr->IRValue, fromIR);
        return;
    }

    // Fallback
    if (const auto iter = baseExpr->type->asIterable()) {
        fromIR = cg.builder.CreateZExt(fromIR, cg.i64Ty());
        IRValue = iter->getIRElement(cg, baseExpr->IRValue, fromIR);
    }
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

Value* LgsIterIndex::castIR(LgsCgModule& cg, LgsType* toType) {
    assert(0);
}

void LgsIterIndex::setIRRangePtr(LgsCgModule& cg, bool assign) {
    assert(!assign);
    const auto fromIR = index.from->IRValue;
    const auto toIR = index.to->IRValue;
    assert(baseExpr->IRValue && fromIR && toIR);
    if (type->asStr()) {
        const auto size = cg.builder.CreateSub(toIR, fromIR);
        const auto sizeWithNull = cg.builder.CreateAdd(size, cg.i32(1));
        IRValue = cg.builder.CreateAlloca(cg.i8Ty(), sizeWithNull);
        const auto src = cg.builder.CreateInBoundsGEP(cg.i8Ty(), baseExpr->IRValue, {fromIR});
        cg.callMemCpy(IRValue, src, size);
        cg.addNullTerminate(IRValue, size);
    } else if (const auto sArray = type->asSArray()) {
        const auto size = cg.builder.CreateSub(toIR, fromIR);
        const auto ty = sArray->baseType->getIRType(cg);
        IRValue = cg.builder.CreateAlloca(ty, size);
        const auto src = cg.builder.CreateInBoundsGEP(ty, baseExpr->IRValue, fromIR);
        const auto elementSize = cg.IRModule->getDataLayout().getTypeAllocSize(ty);
        const auto elementSizeVal = cg.builder.getInt32(elementSize);
        const auto sizeInBytes = cg.builder.CreateMul(size, elementSizeVal);
        cg.callMemCpy(IRValue, src, sizeInBytes);
    } else {
        assert(0);
    }
}

void LgsIterIndex::assign(LgsCgModule& cg, LgsExpr* expr) {
    const auto rIRValue = expr->IRValue;
    const auto baseIRValue = baseExpr;
    auto indexIR = index.from->IRValue;
    if (baseExpr->type->asDArray() || baseExpr->type->asSet()) {
        const auto args = {baseIRValue->IRValue, indexIR, cg.getPtrTo(rIRValue)};
        cg.callLgsFunc("put", cg.voidTy(), {cg.ptrTy(), cg.i32Ty(), cg.ptrTy()}, args);
    } else if (const auto map = baseExpr->type->asMap()) {
        map->addFunc->callIR(cg, {baseExpr->IRValue, indexIR, expr->IRValue});
    } else {
        cg.builder.CreateStore(rIRValue, IRValue);
    }
}

void LgsIterIndex::assignScalar(LgsCgModule& cg, LgsExpr* expr) const {
    const auto rIRValue = expr->IRValue;
    const auto baseIRValue = baseExpr;
    auto indexIR = index.from->IRValue;
    if (baseExpr->type->asDArray() || baseExpr->type->asSet()) {
        const auto args = {baseIRValue->IRValue, indexIR, cg.getPtrTo(rIRValue)};
        cg.callLgsFunc("put", cg.voidTy(), {cg.ptrTy(), cg.i32Ty(), cg.ptrTy()}, args);
    } else if (const auto map = baseExpr->type->asMap()) {
        map->addFunc->callIR(cg, {baseExpr->IRValue, indexIR, expr->IRValue});
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

Type* LgsIterIndex::getSArrayType(LgsCgModule& cg) const {
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
    // TODO free baseExpr
    // freeExpr(baseExpr);
    freeExpr(index.from);
    freeExpr(index.to);
    baseExpr = nullptr;
    index.from = nullptr;
    index.to = nullptr;
}
