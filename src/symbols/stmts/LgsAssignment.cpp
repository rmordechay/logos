#include "stmts/LgsAssignment.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include <LgsStack.h>

Value* LgsAssignment::createIRValue(CodeGenMetadata* metadata) {
    if (const auto selection = lvalue->asSelection()) {
        createIRFromSelection(metadata, selection);
    }
    return nullptr;
}

void LgsAssignment::createIRFromSelection(CodeGenMetadata* metadata, const LgsSelection* selection) const {
    const auto lastExpr = selection->lastExpr();
    const auto beforeLastExpr = selection->exprs[selection->exprs.size() - 2];
    if (const auto var = lastExpr->asVariable()) {
        assert(var->ref);
        switch (var->ref->type) {
        case FIELD:
            var->ref->field->setFieldIRValue(metadata, rvalue, beforeLastExpr->getIRValue(metadata));
            break;
        case UNKNOWN:
            assert(false);
        default:
            break;
        }
    } else if (const auto funcCall = lastExpr->asFuncCall()) {
        assert(false);
    }
}

LgsAssignment::~LgsAssignment() {
    delete lvalue;
    delete rvalue;
}
