#include "stmts/LgsAssignment.h"

#include "LgsInstance.h"
#include "LgsSelection.h"
#include "LgsVariable.h"
#include "stmts/LgsField.h"

#include <LgsStack.h>
#include <types/LgsInt.h>

Value* LgsAssignment::createIRValue(CodeGenMetadata* metadata) {
    if (const auto selection = dynamic_cast<LgsSelection*>(lvalue)) {
        const auto firstExprSymbol = metadata->logosStack.getSymbol(selection->exprs[0]->getName());
        switch (firstExprSymbol->type) {
        case VAR_DEC:
            if (const auto instance = dynamic_cast<LgsInstance*>(firstExprSymbol->varDec->expr)) {
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
