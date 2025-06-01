#include "stmts/LgsAssignment.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"

void LgsAssignment::createIRStmt(CodegenMetadata* metadata) {
    if (const auto selection = lValue->asSelection()) {
        assignIRSelection(metadata, selection, rValue);
    } else if (const auto iterIndex = lValue->asIterIndex()) {
        assignIRIterIndex(metadata, iterIndex, rValue);
    } else {
        assert(false);
    }
}

void LgsAssignment::assignIRIterIndex(CodegenMetadata* metadata, LgsIterIndex* iterIndex, LgsExpr* value) const {
    if (iterIndex->type->asMap()) {
        iterIndex->storeHashMap(metadata, value->asHashMap());
    } else if (iterIndex->type->asArray()) {
        iterIndex->storeArray(metadata, value->asArrayExpr());
    } else {
        iterIndex->storeScalar(metadata, value);
    }
}

void LgsAssignment::assignIRSelection(CodegenMetadata* metadata, const LgsSelection* selection, LgsExpr* expr) const {
    const auto beforeLastExpr = selection->exprs[selection->exprs.size() - 2];
    if (const auto var = selection->lastExpr()->asVariable()) {
        assert(var->ref);
        switch (var->ref->type) {
        case FIELD:
            var->ref->field->setFieldIRValue(metadata, expr, beforeLastExpr->getIRValue(metadata));
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
