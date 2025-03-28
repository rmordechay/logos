#include "stmts/LgsAssignment.h"

#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"

#include <LgsStack.h>
#include <types/LgsInt.h>

Value* LgsAssignment::createIRValue(CodeGenMetadata* metadata) {
    if (const auto selection = lvalue->asSelection()) {
        const auto firstExprSymbol = metadata->logosStack.getSymbol(selection->exprs[0]->getName());
        switch (firstExprSymbol->type) {
        case VAR_DEC:
            if (const auto instance = firstExprSymbol->varDec->expr->asInstance()) {
                const auto nextName = selection->exprs[1]->getName();
                const auto field = instance->obj->getField(nextName);
                field->setFieldIRValue(metadata, rvalue, instance);
            }
            break;
        default:
            break;;
        }
    }
    return nullptr;
}

LgsAssignment::~LgsAssignment() {
    delete lvalue;
    delete rvalue;
}
