#include "stmts/LgsAssignment.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "utils/LgsUtils.h"

void LgsAssignment::createIRStmt(LgsRuntime* runtime) {
    if (const auto selection = lValue->asSelection()) {
        assignToSelection(runtime, selection, rValue);
    } else if (const auto iterIndex = lValue->asIterIndex()) {
        assignToIterIndex(runtime, iterIndex, rValue);
    } else {
        assert(false);
    }
}

void LgsAssignment::assignToIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsExpr* value) const {
    if (const auto map = value->asHashMap()) {
        storeHashMapInIterIndex(runtime, iterIndex, map);
    } else if (const auto arr = value->asArrayExpr()) {
        storeArrayInIterIndex(runtime, iterIndex, arr);
    } else {
        storeScalarInIterIndex(runtime, iterIndex, value);
    }
}

void LgsAssignment::assignToSelection(LgsRuntime* runtime, const LgsSelection* selection, LgsExpr* expr) const {
    const auto beforeLastExpr = selection->exprs[selection->exprs.size() - 2];
    if (const auto var = selection->lastExpr()->asVariable()) {
        assert(var->ref.symbolType != UNKNOWN);
        switch (var->ref.symbolType) {
        case FIELD:
            var->ref.field->setFieldIRValue(runtime, expr, beforeLastExpr->getIRValue(runtime));
            return;
        case UNKNOWN:
        default:
            break;
        }
    }
    assert(false);
}

void LgsAssignment::storeHashMapInIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsHashMap* map) const {
    assert(false);
}

void LgsAssignment::storeScalarInIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsExpr* value) const {
    const auto baseExpr = iterIndex->baseExpr;
    const auto rIRValue = value->getIRValue(runtime);
    const auto baseIRValue = baseExpr->getIRValue(runtime);
    if (const auto arr = baseExpr->type->asArray()) {
        if (!arr->isStatic) {
            const auto ptr = runtime->builder.CreateAlloca(value->type->getIRType());
            runtime->builder.CreateStore(rIRValue, ptr);
            arr->putFunc.callIR(runtime, {baseIRValue, iterIndex->index->from->getIRValue(runtime), ptr});
        } else {
            runtime->builder.CreateStore(rIRValue, iterIndex->getGEP(runtime));
        }
        return;
    }
    if (const auto map = baseExpr->type->asMap()) {
        const auto key = iterIndex->index->from->getIRValue(runtime);
        const auto keyIRType = key->getType();
        const auto keyPtr = runtime->builder.CreateAlloca(keyIRType);
        runtime->builder.CreateStore(key, keyPtr);
        const auto keyLoad = runtime->builder.CreateLoad(keyIRType, keyPtr);
        map->addFunc.callIR(runtime, {baseIRValue, keyLoad, rIRValue});
    } else {
        const auto iterPtr = iterIndex->getIRValue(runtime);
        runtime->builder.CreateStore(rIRValue, iterPtr);
    }
}

void LgsAssignment::storeArrayInIterIndex(LgsRuntime* runtime, const LgsIterIndex* iterIndex, const LgsArrayExpr* arr) const {
    if (!arr->type->asArray()->isStatic) {
        return;
    }
    const auto baseExpr = iterIndex->baseExpr;
    const auto IRType = baseExpr->type->getIRType();
    const auto arrPtr = baseExpr->getIRValue(runtime);
    vector<Value*> IRIndices = {runtime->builder.getInt32(0)};
    vector<LgsIndex*> indices;
    setIterIndices(iterIndex, indices);
    for (const auto index : indices) {
        IRIndices.emplace_back(index->from->getIRValue(runtime));
    }
    for (int i = 0; i < arr->initialElements.size(); ++i) {
        const auto element = arr->initialElements[i];
        const auto IRIndex = runtime->builder.getInt32(i);
        IRIndices.push_back(IRIndex);
        const auto gep = runtime->builder.CreateGEP(IRType, arrPtr, IRIndices);
        const auto rValue = element->getIRValue(runtime);
        runtime->builder.CreateStore(rValue, gep);
        IRIndices.pop_back();
    }
}

LgsAssignment::~LgsAssignment() {
    delete lValue;
    delete rValue;
}
