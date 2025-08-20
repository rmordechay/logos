#include "stmts/LgsAssignment.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "types/LgsVec.h"

void LgsAssignment::createIRValue(LgsCodeGen* codeGen) {
    Value* results = nullptr;
    switch (assignmentType) {
    case ASSIGN:
        createIRAssignment(codeGen);
        return;
    case ASSIGN_ADD:
        results = lValue->addIR(codeGen, rValue);
        break;
    case ASSIGN_SUB:
        results = lValue->subIR(codeGen, rValue);
        break;
    case ASSIGN_MUL:
        results = lValue->mulIR(codeGen, rValue);
        break;
    case ASSIGN_DIV:
        results = lValue->divIR(codeGen, rValue);
        break;
    case ASSIGN_MOD:
        results = lValue->modIR(codeGen, rValue);
        break;
    case ASSIGN_AND:
        results = lValue->bitAndIR(codeGen, rValue);
        break;
    case ASSIGN_OR:
        results = lValue->bitOrIR(codeGen, rValue);
        break;
    case ASSIGN_XOR:
        results = lValue->bitXorIR(codeGen, rValue);
        break;
    case ASSIGN_LSHIFT:
        results = lValue->lshiftIR(codeGen, rValue);
        break;
    case ASSIGN_RSHIFT:
        results = lValue->rshiftIR(codeGen, rValue);
        break;
    }
    assert(results);
    codeGen->builder.CreateStore(results, lValue->getIRValue(codeGen));
}

void LgsAssignment::createIRAssignment(LgsCodeGen* codeGen) const {
    if (const auto selection = lValue->asSelection()) {
        assignToSelection(codeGen, selection, rValue);
    } else if (const auto iterIndex = lValue->asIterIndex()) {
        assignToIterIndex(iterIndex, rValue, codeGen);
    } else if (const auto var = lValue->asVariable()) {
        assignToVariable(codeGen, var, rValue);
    } else {
        assert(0);
    }
}

void LgsAssignment::assignToIterIndex(LgsIterIndex* iterIndex, LgsExpr* expr, LgsCodeGen* codeGen) {
    if (const auto map = expr->asHashMap()) {
        assignHashMapToIterIndex(codeGen, iterIndex, map);
    } else if (const auto arr = expr->asArrayExpr()) {
        assignArrayToIterIndex(codeGen, iterIndex, arr);
    } else {
        assignScalarToIterIndex(codeGen, iterIndex, expr);
    }
}

void LgsAssignment::assignArrayToIterIndex(LgsCodeGen* codeGen, const LgsIterIndex* iterIndex, const LgsArrayExpr* arr) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto IRType = baseExpr->type->getIRType(codeGen);
    const auto arrPtr = baseExpr->getIRValue(codeGen);

    // Flatten the indices and reverse them to use them as indices.
    std::vector<LgsIndex*> indices;
    while (iterIndex) {
        if (iterIndex->index) indices.push_back(iterIndex->index);
        iterIndex = baseExpr->asIterIndex();
    }
    reverse(indices.begin(), indices.end());

    std::vector<Value*> IRIndices = {codeGen->i32Zero()};
    for (const auto index : indices) {
        IRIndices.emplace_back(index->from->getIRValue(codeGen));
    }
    for (int i = 0; i < arr->initialElements.size(); ++i) {
        const auto element = arr->initialElements[i];
        const auto IRIndex = codeGen->i32(i);
        IRIndices.push_back(IRIndex);
        const auto gep = codeGen->builder.CreateGEP(IRType, arrPtr, IRIndices);
        const auto rValue = element->getIRValue(codeGen);
        codeGen->builder.CreateStore(rValue, gep);
        IRIndices.pop_back();
    }
}

void LgsAssignment::assignToSelection(LgsCodeGen* codeGen, LgsSelection* selection, LgsExpr* expr) {
    const auto rIR = expr->getIRValue(codeGen);
    const auto lastExprParent = selection->lastExprParent();
    if (lastExprParent->type->asVec()) {
        const auto vecTy = lastExprParent->type->getIRType(codeGen);
        const auto vec = codeGen->builder.CreateLoad(vecTy, lastExprParent->getIRValue(codeGen));
        const auto c = selection->lastExpr()->asVariable()->name;
        const auto i = codeGen->i32(LgsVec::getComponentIndex(c.front()));
        const auto insert = codeGen->builder.CreateInsertElement(vec, rIR, i);
        codeGen->builder.CreateStore(insert, lastExprParent->getIRValue(codeGen));
    } else {
        const auto lIR = selection->getIRValue(codeGen);
        codeGen->builder.CreateStore(rIR, lIR);
    }
}

void LgsAssignment::assignToVariable(LgsCodeGen* codeGen, LgsVariable* variable, LgsExpr* expr) {
    const auto variablePtr = variable->getIRValue(codeGen);
    const auto exprIRValue = expr->getIRValue(codeGen);
    codeGen->builder.CreateStore(exprIRValue, variablePtr);
}

void LgsAssignment::assignScalarToIterIndex(LgsCodeGen* codeGen, LgsIterIndex* iterIndex, LgsExpr* expr) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto rIRValue = expr->getIRValue(codeGen);
    const auto baseIRValue = baseExpr->getIRValue(codeGen);
    if (const auto arr = baseExpr->type->asDArray()) {
        const auto ptr = codeGen->builder.CreateAlloca(expr->type->getIRType(codeGen));
        codeGen->builder.CreateStore(rIRValue, ptr);
        arr->putFunc->callIR(codeGen, {baseIRValue, iterIndex->index->from->getIRValue(codeGen), ptr});
        return;
    }
    if (baseExpr->type->asSArray()) {
        codeGen->builder.CreateStore(rIRValue, iterIndex->loadFromSArray(codeGen));
        return;
    }
    if (const auto map = baseExpr->type->asMap()) {
        const auto key = iterIndex->index->from->getIRValue(codeGen);
        map->addFunc->callIR(codeGen, {baseIRValue, key, rIRValue});
    } else {
        const auto iterPtr = iterIndex->getIRValue(codeGen);
        codeGen->builder.CreateStore(rIRValue, iterPtr);
    }
}

void LgsAssignment::assignHashMapToIterIndex(LgsCodeGen* codeGen, LgsIterIndex* iterIndex, LgsHashMap* map) {
    assert(0);
}

json::value LgsAssignment::asJSON() {
    json::object obj;
    obj["lValue"] = lValue->asJSON();
    obj["rValue"] = rValue->asJSON();
    obj["assignmentType"] = assignmentType;
    return obj;
}

LgsAssignment::~LgsAssignment() {
    delete lValue;
    delete rValue;
}
