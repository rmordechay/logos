#include "exprs/LogosVariable.h"

#include "funcs/LogosFunc.h"
#include "object/LogosField.h"
#include "object/LogosObject.h"

#include <llvm/IR/Module.h>

string LogosVariable::getName() {
    return name;
}

LogosSymbolType LogosVariable::getSymbolType() {
    return VARIABLE;
}

Value* LogosVariable::getLLVMValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->theStack->getSymbol(name);
    switch (symbol->type) {
    case FIELD: {
        const auto expr = symbol->field->expr;
        if (expr) {
            llvmValue = expr->getLLVMValue(metadata);
            return llvmValue;
        }
        break;
    }
    // case VAR_DEC: {
    //     llvmValue = symbol->varDec->expr->getLLVMValue(metadata);
    //     return llvmValue;
    // }
    case FUNC: {
        llvmValue = symbol->func->getLLVMValue(metadata);
        return llvmValue;
    }
    default: break;
    }
    return nullptr;
}

LogosVariable* LogosVariable::asVariable() {
    return this;
}