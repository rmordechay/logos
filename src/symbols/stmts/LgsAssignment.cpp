#include "stmts/LgsAssignment.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"

void LgsAssignment::createIRStmt(Module* module) {
    if (const auto selection = lValue->asSelection()) {
        assignIRSelection(module, selection, rValue);
    } else if (const auto iterIndex = lValue->asIterIndex()) {
        assignIRIterIndex(module, iterIndex, rValue);
    } else {
        assert(false);
    }
}

void LgsAssignment::assignIRIterIndex(Module* module, LgsIterIndex* iterIndex, LgsExpr* value) const {
    if (iterIndex->type->asMap()) {
        iterIndex->storeHashMap(module, value->asHashMap());
    } else if (iterIndex->type->asArray()) {
        iterIndex->storeArray(module, value->asArrayExpr());
    } else {
        iterIndex->storeScalar(module, value);
    }
}

void LgsAssignment::assignIRSelection(Module* module, const LgsSelection* selection, LgsExpr* expr) const {
    const auto beforeLastExpr = selection->exprs[selection->exprs.size() - 2];
    if (const auto var = selection->lastExpr()->asVariable()) {
        assert(var->ref);
        switch (var->ref->type) {
        case FIELD:
            var->ref->field->setFieldIRValue(module, expr, beforeLastExpr->getIRValue(module));
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
