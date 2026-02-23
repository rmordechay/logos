#include "exprs/LgsIterIndex.h"

#include <__ostream/basic_ostream.h>
#include <assert.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <sstream>

#include "LgsRTTIndices.h"
#include "codegen/LgsCodeGen.h"
#include "LgsType.h"
#include "Lgs_Exprs.h"
#include "types/iterables/LgsSArray.h"
#include "types/iterables/LgsStr.h"

namespace llvm {
class Value;
}

Value* LgsIterIndex::getIRRangePtr(LgsCodeGen& cg) const {
    const auto fromIR = index.from->IRValue;
    const auto toIR = index.to->IRValue;
    assert(baseExpr->IRValue && fromIR && toIR);
    Value* v = nullptr;
    if (type->asStr()) {
        const auto size = cg.builder.CreateSub(toIR, fromIR);
        const auto sizeWithNull = cg.builder.CreateAdd(size, cg.i32(1));
        const auto data = cg.heapAllocSize(sizeWithNull, cg.currentLevel, false);
        const auto baseData = LgsStr::loadIRData(cg, baseExpr->IRValue);
        const auto src = cg.builder.CreateInBoundsGEP(cg.i8Ty(), baseData, {fromIR});
        cg.callMemcpy(data, src, size);
        v = cg.heapAllocSize(cg.usize(sizeof(Lgs_StrExpr)), cg.currentLevel, true);
        cg.storeField(LgsStr::getStrStruct(cg), v, LgsStrIndices::data, data);
    } else if (const auto sArray = type->asSArray()) {
        const auto size = cg.builder.CreateSub(toIR, fromIR);
        const auto ty = sArray->baseType->getIRType(cg);
        v = cg.builder.CreateAlloca(ty, size);
        const auto src = cg.builder.CreateInBoundsGEP(ty, baseExpr->IRValue, fromIR);
        const auto elementSize = cg.getTypeSize(ty);
        const auto sizeInBytes = cg.builder.CreateMul(size, elementSize);
        cg.callMemcpy(v, src, sizeInBytes);
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
