#include "stmts/LgsAssignment.h"

#include "exprs/unary/LgsArrayIndex.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include <LgsStack.h>

void LgsAssignment::createIRStmt(CodeGenMetadata* metadata) {
    if (const auto selection = lvalue->asSelection()) {
        createIRFromSelection(metadata, selection);
        return;
    }
    if (const auto arrIndex = lvalue->asArrayIndex()) {
        createIRFromArrIndex(metadata, arrIndex);
        return;
    }
    assert(false);
}

void LgsAssignment::createIRFromSelection(CodeGenMetadata* metadata, const LgsSelection* selection) const {
    const auto lastExpr = selection->lastExpr();
    const auto beforeLastExpr = selection->exprs[selection->exprs.size() - 2];
    if (const auto var = lastExpr->asVariable()) {
        assert(var->ref);
        switch (var->ref->type) {
        case FIELD:
            var->ref->field->setFieldIRValue(metadata, rvalue, beforeLastExpr->getIRValue(metadata));
            return;
        case UNKNOWN:
        default:
            break;
        }
    }
    assert(false);
}

void LgsAssignment::createIRFromArrIndex(CodeGenMetadata* metadata, const LgsArrayIndex* arrIndex) const {
    const auto gep = arrIndex->getGEP(metadata);
    const auto rValue = rvalue->getIRValue(metadata);
    metadata->builder.CreateStore(rValue, gep);
}

LgsAssignment::~LgsAssignment() {
    delete lvalue;
    delete rvalue;
}
