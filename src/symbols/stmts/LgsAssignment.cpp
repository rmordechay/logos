#include "stmts/LgsAssignment.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsSelection.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"
#include <LgsStack.h>

Value* LgsAssignment::createIRValue(CodeGenMetadata* metadata) {
    if (const auto selection = lvalue->asSelection()) {
        createIRFromSelection(metadata, selection);
    }
    return nullptr;
}

void LgsAssignment::createIRFromSelection(CodeGenMetadata* metadata, const LgsSelection* selection) const {
    const auto firstExprSymbol = metadata->lgsStack.getSymbol(selection->exprs[0]->getName());
    switch (firstExprSymbol->type) {
    case VAR_DEC:
        if (const auto instance = firstExprSymbol->varDec->expr->asInstance()) {
            const auto nextName = selection->exprs[1]->getName();
            const auto field = instance->obj->getField(nextName);
            field->setFieldIRValue(metadata, rvalue);
        }
        break;
    default:
        break;
    }
}

LgsAssignment::~LgsAssignment() {
    delete lvalue;
    delete rvalue;
}
