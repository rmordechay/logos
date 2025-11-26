#include "types/iterables/LgsIterable.h"
#include "exprs/LgsIterIndex.h"
#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"
#include "LgsUtils.h"
#include "types/iterables/LgsMap.h"

size_t LgsIterable::getDimension() const {
    size_t dim = 1;
    auto nestedIter = this;
    while (true) {
        if (const auto innerIter = nestedIter->baseType->asIterable()) {
            nestedIter = innerIter;
            if (innerIter->asVec() || innerIter->asStr()) continue;
            dim++;
        } else {
            break;
        }
    }
    return dim;
}

LgsType* LgsIterable::getIndexType() {
    return &LGS_INT;
}

LgsType* LgsIterable::getValueType() {
    return baseType;
}

bool LgsIterable::unpackLoopVarsTypes(LgsForeachLoop* loop) const {
    if (loop->loopVars.size() != 1) return false;
    const auto iterIndex = new LgsIterIndex(loop->iterExpr, LGS_SIZE.getZeroValue());
    assert(baseType);
    iterIndex->setType(baseType);
    loop->loopVars[0]->expr = iterIndex;
    loop->loopVars[0]->setType(iterIndex->type);
    return true;
}

void LgsIterable::unpackLoopIR(LgsLLVMGen& cg, LgsForeachLoop* loop) const {
    const auto iterIndex = loop->loopVars[0]->expr->asIterIndex();
    iterIndex->index.from->IRValue = loop->iValue;
    iterIndex->setIRElementPtr(cg);
    loop->loopVars[0]->IRValue = iterIndex->IRValue;
}

LgsIterable::~LgsIterable() {
    if (size) {
        freeExpr(size);
        size = nullptr;
    }
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
