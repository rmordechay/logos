#include "exprs/LgsIterIndex.h"
#include <exprs/LgsArrayExpr.h>
#include "types/iterables/LgsMap.h"
#include "types/iterables/LgsVec.h"
#include "LgsUtils.h"
#include <sstream>
#include <llvm/IR/Module.h>

#include "codegen/LgsCodeGen.h"

Value* LgsIterIndex::getIRRangePtr(LgsCodeGen& cg) const {
    const auto fromIR = index.from->IRValue;
    const auto toIR = index.to->IRValue;
    assert(baseExpr->IRValue && fromIR && toIR);
    Value* v = nullptr;
    if (type->asStr()) {
        const auto size = cg.builder.CreateSub(toIR, fromIR);
        const auto sizeWithNull = cg.builder.CreateAdd(size, cg.i32(1));
        v = cg.builder.CreateAlloca(cg.i8Ty(), sizeWithNull);
        const auto src = cg.builder.CreateInBoundsGEP(cg.i8Ty(), baseExpr->IRValue, {fromIR});
        cg.callMemcpy(IRValue, src, size);
    } else if (const auto sArray = type->asSArray()) {
        const auto size = cg.builder.CreateSub(toIR, fromIR);
        const auto ty = sArray->baseType->getIRType(cg);
        v = cg.builder.CreateAlloca(ty, size);
        const auto src = cg.builder.CreateInBoundsGEP(ty, baseExpr->IRValue, fromIR);
        const auto elementSize = cg.getTypeSize(ty);
        const auto sizeInBytes = cg.builder.CreateMul(size, elementSize);
        cg.callMemcpy(IRValue, src, sizeInBytes);
    } else {
        assert(0);
    }
    return v;
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

void LgsIterIndex::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsExpr* LgsIterIndex::clone() {
    const auto newIterIndex = new LgsIterIndex(baseExpr->clone());
    newIterIndex->index.from = index.from->clone();
    if (index.to) {
        newIterIndex->index.to = index.to->clone();
    }
    return newIterIndex;
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
