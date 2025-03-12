#include "stmts/LogosAssignment.h"

#include "LogosInstance.h"
#include "LogosSelection.h"
#include "LogosVariable.h"
#include "stmts/LogosField.h"

#include <LogosStack.h>
#include <types/LogosInt.h>

Value* LogosAssignment::createIRValue(CodeGenMetadata* metadata) {
    if (const auto selection = dynamic_cast<LogosSelection*>(lvalue)) {
        const auto firstExprSymbol = metadata->logosStack.getSymbol(selection->exprs[0]->getName());
        switch (firstExprSymbol->type) {
        case VAR_DEC:
            if (const auto instance = dynamic_cast<LogosInstance*>(firstExprSymbol->varDec->expr)) {
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

LogosAssignment::~LogosAssignment() {
    delete lvalue;
    delete rvalue;
}
