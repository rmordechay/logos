#include "stmts/LgsAssignment.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"

void LgsAssignment::createIRStmt(LgsRuntime* runtime) {
    Value* results = nullptr;
    switch (assignmentType) {
    case ASSIGN:
        createIRAssign(runtime);
        return;
    case ASSIGN_ADD:
        results = lValue->addIR(runtime, rValue);
        break;
    case ASSIGN_SUB:
        results = lValue->subIR(runtime, rValue);
        break;
    case ASSIGN_MUL:
        results = lValue->mulIR(runtime, rValue);
        break;
    case ASSIGN_DIV:
        results = lValue->divIR(runtime, rValue);
        break;
    case ASSIGN_MOD:
        results = lValue->modIR(runtime, rValue);
        break;
    case ASSIGN_AND:
        results = lValue->bitAndIR(runtime, rValue);
        break;
    case ASSIGN_OR:
        results = lValue->bitOrIR(runtime, rValue);
        break;
    case ASSIGN_XOR:
        results = lValue->bitXorIR(runtime, rValue);
        break;
    case ASSIGN_LSHIFT:
        results = lValue->lshiftIR(runtime, rValue);
        break;
    case ASSIGN_RSHIFT:
        results = lValue->rshiftIR(runtime, rValue);
        break;
    }
    assert(results);
    runtime->builder.CreateStore(results, lValue->getIRValue(runtime));
}

void LgsAssignment::createIRAssign(LgsRuntime* runtime) const {
    if (const auto selection = lValue->asSelection()) {
        assignToSelection(runtime, selection, rValue);
    } else if (const auto iterIndex = lValue->asIterIndex()) {
        assignToIterIndex(runtime, iterIndex, rValue);
    } else if (const auto var = lValue->asVariable()) {
        assignToVariable(runtime, var, rValue);
    } else {
        assert(0);
    }
}

void LgsAssignment::assignToIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsExpr* expr) const {
    if (const auto map = expr->asHashMap()) {
        storeHashMapInIterIndex(runtime, iterIndex, map);
    } else if (const auto arr = expr->asArrayExpr()) {
        storeArrayInIterIndex(runtime, iterIndex, arr);
    } else {
        storeScalarInIterIndex(runtime, iterIndex, expr);
    }
}

void LgsAssignment::assignToSelection(LgsRuntime* runtime, const LgsSelection* selection, LgsExpr* expr) const {
    selection->resolveSelection(runtime);
    const auto lastExpr = selection->lastExpr();
    const auto parentExpr = selection->exprs[selection->exprs.size() - 2];
    if (const auto var = lastExpr->asVariable()) {
        assert(var->ref.symbolType != UNKNOWN);
        switch (var->ref.symbolType) {
        case FIELD: {
            const auto parentIRValue = parentExpr->getIRValue(runtime);
            var->ref.field->storeIRValue(runtime, parentExpr->type->getIRType(), parentIRValue, expr);
            return;
        }
        case UNKNOWN: default:
            break;
        }
    }
    assert(0);
}

void LgsAssignment::assignToVariable(LgsRuntime* runtime, LgsVariable* variable, LgsExpr* expr) const {
    const auto variablePtr = variable->getIRValue(runtime);
    const auto exprIRValue = expr->getIRValue(runtime);
    runtime->builder.CreateStore(exprIRValue, variablePtr);
}

void LgsAssignment::storeHashMapInIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsHashMap* map) const {
    assert(0);
}

void LgsAssignment::storeScalarInIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsExpr* expr) const {
    const auto baseExpr = iterIndex->baseExpr;
    const auto rIRValue = expr->getIRValue(runtime);
    const auto baseIRValue = baseExpr->getIRValue(runtime);
    if (const auto arr = baseExpr->type->asArray()) {
        if (!arr->isStatic) {
            const auto ptr = runtime->builder.CreateAlloca(expr->type->getIRType());
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
    if (!arr->arrType->isStatic) {
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

void LgsAssignment::setIterIndices(const LgsIterIndex* iterIndex, vector<LgsIndex*>& indices) const {
    while (iterIndex) {
        if (iterIndex->index) {
            indices.push_back(iterIndex->index);
        }
        iterIndex = iterIndex->baseExpr->asIterIndex();
    }
    reverse(indices.begin(), indices.end());
}

LgsAssignment::~LgsAssignment() {
    delete lValue;
    delete rValue;
}
