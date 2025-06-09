#include "stmts/LgsAssignment.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"

void LgsAssignment::createIRStmt(LgsRuntime* runtime) {
    if (const auto selection = lValue->asSelection()) {
        assignIRSelection(runtime, selection, rValue);
    } else if (const auto iterIndex = lValue->asIterIndex()) {
        assignIRIterIndex(runtime, iterIndex, rValue);
    } else {
        assert(false);
    }
}

void LgsAssignment::assignIRIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsExpr* value) const {
    if (const auto map = value->asHashMap()) {
        iterIndex->storeHashMap(runtime, map);
    } else if (const auto arr = value->asArrayExpr()) {
        iterIndex->storeArray(runtime, arr);
    } else {
        iterIndex->storeScalar(runtime, value);
    }
}

void LgsAssignment::assignIRSelection(LgsRuntime* runtime, const LgsSelection* selection, LgsExpr* expr) const {
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

LgsAssignment::~LgsAssignment() {
    delete lValue;
    delete rValue;
}
