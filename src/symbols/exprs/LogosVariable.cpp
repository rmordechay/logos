#include "exprs/LogosVariable.h"

#include "object/LogosField.h"
#include "object/LogosObject.h"

#include <llvm/IR/Module.h>

Value* LogosVariable::getLLVMValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->theStack->getSymbol(name);
    switch (symbol->type) {
    case FIELD: {
        const auto expr = symbol->field->expr;
        if (expr) {
            return expr->getLLVMValue(metadata);
        }
        break;
    }
    case VAR_DEC: {
        return symbol->varDec->expr->getLLVMValue(metadata);
    }
    case OBJECT: {
        symbol->object->getLLVMType(metadata);
        break;
    }
    case FUNC: {
        return symbol->func->getLLVMValue(metadata);
    }
    }
    return nullptr;
}
