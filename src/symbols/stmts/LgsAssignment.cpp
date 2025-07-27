#include "stmts/LgsAssignment.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "utils/LgsIRUtils.h"

void LgsAssignment::createIRStmt(LgsModule* module) {
    Value* results = nullptr;
    switch (assignmentType) {
    case ASSIGN:
        createIRAssign(module);
        return;
    case ASSIGN_ADD:
        results = lValue->addIR(module, rValue);
        break;
    case ASSIGN_SUB:
        results = lValue->subIR(module, rValue);
        break;
    case ASSIGN_MUL:
        results = lValue->mulIR(module, rValue);
        break;
    case ASSIGN_DIV:
        results = lValue->divIR(module, rValue);
        break;
    case ASSIGN_MOD:
        results = lValue->modIR(module, rValue);
        break;
    case ASSIGN_AND:
        results = lValue->bitAndIR(module, rValue);
        break;
    case ASSIGN_OR:
        results = lValue->bitOrIR(module, rValue);
        break;
    case ASSIGN_XOR:
        results = lValue->bitXorIR(module, rValue);
        break;
    case ASSIGN_LSHIFT:
        results = lValue->lshiftIR(module, rValue);
        break;
    case ASSIGN_RSHIFT:
        results = lValue->rshiftIR(module, rValue);
        break;
    }
    assert(results);
    module->builder.CreateStore(results, lValue->getIRValue(module));
}

void LgsAssignment::createIRAssign(LgsModule* module) const {
    if (const auto selection = lValue->asSelection()) {
        assignToSelection(module, selection, rValue);
    } else if (const auto iterIndex = lValue->asIterIndex()) {
        assignToIterIndex(module, iterIndex, rValue);
    } else if (const auto var = lValue->asVariable()) {
        assignToVariable(module, var, rValue);
    } else {
        assert(0);
    }
}

void LgsAssignment::assignToIterIndex(LgsModule* module, LgsIterIndex* iterIndex, LgsExpr* expr) const {
    if (const auto map = expr->asHashMap()) {
        storeHashMapInIterIndex(module, iterIndex, map);
    } else if (const auto arr = expr->asArrayExpr()) {
        storeArrayInIterIndex(module, iterIndex, arr);
    } else {
        storeScalarInIterIndex(module, iterIndex, expr);
    }
}

void LgsAssignment::assignToSelection(LgsModule* module, LgsSelection* selection, LgsExpr* expr) {
    const auto selectionIRValue = selection->resolveSelection(module);
    const auto var = selection->lastExpr()->asVariable();
    var->ref.field->storeIRValue(module, selectionIRValue, expr);
}

void LgsAssignment::assignToVariable(LgsModule* module, LgsVariable* variable, LgsExpr* expr) {
    const auto variablePtr = variable->getIRValue(module);
    const auto exprIRValue = expr->getIRValue(module);
    module->builder.CreateStore(exprIRValue, variablePtr);
}

void LgsAssignment::storeHashMapInIterIndex(LgsModule* module, LgsIterIndex* iterIndex, LgsHashMap* map) {
    assert(0);
}

void LgsAssignment::storeScalarInIterIndex(LgsModule* module, LgsIterIndex* iterIndex, LgsExpr* expr) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto rIRValue = expr->getIRValue(module);
    const auto baseIRValue = baseExpr->getIRValue(module);
    if (const auto arr = baseExpr->type->asDArray()) {
        const auto ptr = module->builder.CreateAlloca(expr->type->getIRType(module));
        module->builder.CreateStore(rIRValue, ptr);
        arr->putFunc.callIR(module, {baseIRValue, iterIndex->index->from->getIRValue(module), ptr});
        return;
    }
    if (baseExpr->type->asSArray()) {
        module->builder.CreateStore(rIRValue, iterIndex->getArrGEP(module));
        return;
    }
    if (const auto map = baseExpr->type->asMap()) {
        const auto key = iterIndex->index->from->getIRValue(module);
        const auto keyIRType = key->getType();
        const auto keyPtr = module->builder.CreateAlloca(keyIRType);
        module->builder.CreateStore(key, keyPtr);
        const auto keyLoad = module->builder.CreateLoad(keyIRType, keyPtr);
        map->addFunc.callIR(module, {baseIRValue, keyLoad, rIRValue});
    } else {
        const auto iterPtr = iterIndex->getIRValue(module);
        module->builder.CreateStore(rIRValue, iterPtr);
    }
}

void LgsAssignment::storeArrayInIterIndex(LgsModule* module, const LgsIterIndex* iterIndex, const LgsArrayExpr* arr) const {
    const auto baseExpr = iterIndex->baseExpr;
    const auto IRType = baseExpr->type->getIRType(module);
    const auto arrPtr = baseExpr->getIRValue(module);
    vector IRIndices = {i32(module, 0)};
    vector<LgsIndex*> indices;
    setIterIndices(iterIndex, indices);
    for (const auto index : indices) {
        IRIndices.emplace_back(index->from->getIRValue(module));
    }
    for (int i = 0; i < arr->initialElements.size(); ++i) {
        const auto element = arr->initialElements[i];
        const auto IRIndex = i32(module, i);
        IRIndices.push_back(IRIndex);
        const auto gep = module->builder.CreateGEP(IRType, arrPtr, IRIndices);
        const auto rValue = element->getIRValue(module);
        module->builder.CreateStore(rValue, gep);
        IRIndices.pop_back();
    }
}

void LgsAssignment::setIterIndices(const LgsIterIndex* iterIndex, vector<LgsIndex*>& indices) {
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
