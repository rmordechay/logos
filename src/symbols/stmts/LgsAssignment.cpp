#include "stmts/LgsAssignment.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "types/LgsVec.h"

void LgsAssignment::createIRAssignment(LgsLLVM& codeGen) const {
    if (const auto selection = lValue->asSelection()) {
        assignToSelection(&codeGen, selection, rValue);
    } else if (const auto iterIndex = lValue->asIterIndex()) {
        assignToIterIndex(iterIndex, rValue, &codeGen);
    } else if (const auto var = lValue->asVariable()) {
        assignToVariable(&codeGen, var, rValue);
    } else {
        assert(0);
    }
}

void LgsAssignment::assignToIterIndex(LgsIterIndex* iterIndex, LgsExpr* expr, LgsLLVM* codeGen) {
    if (const auto map = expr->asHashMap()) {
        assignHashMapToIterIndex(codeGen, iterIndex, map);
    } else if (const auto arr = expr->asArrayExpr()) {
        assignArrayToIterIndex(codeGen, iterIndex, arr);
    } else {
        assignScalarToIterIndex(*codeGen, iterIndex, expr);
    }
}

void LgsAssignment::assignArrayToIterIndex(LgsLLVM* codeGen, const LgsIterIndex* iterIndex, const LgsArrayExpr* arr) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto IRType = baseExpr->type->getIRType(*codeGen);
    const auto arrPtr = baseExpr->IRValue;

    // Flatten the indices and reverse them to use them as indices.
    std::vector<LgsIndex*> indices;
    while (iterIndex) {
        if (iterIndex->index) indices.push_back(iterIndex->index);
        iterIndex = baseExpr->asIterIndex();
    }
    reverse(indices.begin(), indices.end());

    std::vector<Value*> IRIndices = {codeGen->i32Zero()};
    for (const auto index : indices) {
        IRIndices.emplace_back(index->from->IRValue);
    }
    for (int i = 0; i < arr->initialElements.size(); ++i) {
        const auto element = arr->initialElements[i];
        const auto IRIndex = codeGen->i32(i);
        IRIndices.push_back(IRIndex);
        const auto gep = codeGen->builder.CreateGEP(IRType, arrPtr, IRIndices);
        const auto rValue = element->IRValue;
        codeGen->builder.CreateStore(rValue, gep);
        IRIndices.pop_back();
    }
}

void LgsAssignment::assignToSelection(LgsLLVM* codeGen, LgsSelection* selection, LgsExpr* expr) {
    const auto rIR = expr->IRValue;
    const auto lastExprParent = selection->lastExprParent();
    if (lastExprParent->type->asVec()) {
        const auto vecTy = lastExprParent->type->getIRType(*codeGen);
        const auto vec = codeGen->builder.CreateLoad(vecTy, lastExprParent->IRValue);
        const auto c = selection->lastExpr()->asVariable()->name;
        const auto i = codeGen->i32(LgsVec::getComponentIndex(c.front()));
        const auto insert = codeGen->builder.CreateInsertElement(vec, rIR, i);
        codeGen->builder.CreateStore(insert, lastExprParent->IRValue);
    } else {
        const auto lIR = selection->IRValue;
        codeGen->builder.CreateStore(rIR, lIR);
    }
}

void LgsAssignment::assignToVariable(LgsLLVM* codeGen, LgsVariable* variable, LgsExpr* expr) {
    const auto variablePtr = variable->IRValue;
    const auto exprIRValue = expr->IRValue;
    codeGen->builder.CreateStore(exprIRValue, variablePtr);
}

void LgsAssignment::assignScalarToIterIndex(LgsLLVM& codeGen, LgsIterIndex* iterIndex, LgsExpr* expr) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto rIRValue = expr->IRValue;
    const auto baseIRValue = baseExpr->IRValue;
    if (const auto arr = baseExpr->type->asDArray()) {
        const auto ptr = codeGen.builder.CreateAlloca(expr->type->getIRType(codeGen));
        codeGen.builder.CreateStore(rIRValue, ptr);
        arr->putFunc->callIR(codeGen, {baseIRValue, iterIndex->index->from->IRValue, ptr});
        return;
    }
    if (baseExpr->type->asSArray()) {
        codeGen.builder.CreateStore(rIRValue, iterIndex->loadFromSArray(codeGen));
        return;
    }
    if (const auto map = baseExpr->type->asMap()) {
        const auto key = iterIndex->index->from->IRValue;
        map->addFunc->callIR(codeGen, {baseIRValue, key, rIRValue});
    } else {
        const auto iterPtr = iterIndex->IRValue;
        codeGen.builder.CreateStore(rIRValue, iterPtr);
    }
}

void LgsAssignment::assignHashMapToIterIndex(LgsLLVM* codeGen, LgsIterIndex* iterIndex, LgsHashMap* map) {
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
