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
    if (iterIndex->type->asMap()) {
        iterIndex->storeHashMap(runtime, value->asHashMap());
    } else if (iterIndex->type->asArray()) {
        iterIndex->storeArray(runtime, value->asArrayExpr());
    } else {
        iterIndex->storeScalar(runtime, value);
    }
}

void LgsAssignment::assignIRSelection(LgsRuntime* runtime, const LgsSelection* selection, LgsExpr* expr) const {
    const auto beforeLastExpr = selection->exprs[selection->exprs.size() - 2];
    if (const auto var = selection->lastExpr()->asVariable()) {
        assert(var->ref);
        switch (var->ref->type) {
        case FIELD:
            var->ref->field->setFieldIRValue(runtime, expr, beforeLastExpr->getIRValue(runtime));
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
