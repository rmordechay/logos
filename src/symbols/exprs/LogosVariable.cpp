#include "exprs/LogosVariable.h"

#include "object/LogosField.h"
#include "object/LogosObject.h"

#include <llvm/IR/Module.h>

Value* LogosVariable::writeLLVMValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->theStack->getSymbol(name);
    switch (symbol->type) {
    case FIELD: {
        const auto expr = symbol->field->expr;
        if (expr) {
            llvmValue = expr->writeLLVMValue(metadata);
            return llvmValue;
        }
        break;
    }
    case VAR_DEC: {
        llvmValue = symbol->varDec->expr->writeLLVMValue(metadata);
        return llvmValue;
    }
    case OBJECT: {
        symbol->object->writeLLVMType(metadata);
        break;
    }
    case FUNC: {
        llvmValue = symbol->func->writeLLVMValue(metadata);
        return llvmValue;
    }
    }
    return nullptr;
}

