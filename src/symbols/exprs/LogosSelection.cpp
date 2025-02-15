#include "exprs/LogosSelection.h"

#include "LogosUtils.h"
#include "exprs/LogosFuncCall.h"

LogosExpr* f(LogosUnaryExpr* expr);

void resolveSymbol(CodeGenMetadata* metadata, const LogosSymbol* currentSymbol) {
    switch (currentSymbol->type) {
    case FIELD: {
        currentSymbol->field->expr->writeLLVMValue(metadata);
        break;
    }
    case VAR_DEC: {
        currentSymbol->varDec->expr->writeLLVMValue(metadata);
        break;
    }
    case OBJECT: {
        currentSymbol->object->getLLVMType();
        break;
    }
    case FUNC: {
        currentSymbol->func->writeLLVMValue(metadata);
        break;
    }
    }
}

Value* LogosSelection::writeLLVMValue(CodeGenMetadata* metadata) {
    // 1. Get next element
    // 2. Resolve
    // 3. Find type
    // 4. Apply (func=call; varDec=execute expr; constructor=instantiate)
    // 5. If last value, return, if not, continue
    // 6. If next selection in the returned values, repeat until exhaustion

    // Unary - func, variable, constructor
    // obj = MyObject()
    // obj.add()

    for (int i = 0; i < exprs.size(); ++i) {
        const auto expr = exprs[i];
        expr->writeLLVMValue(metadata);
    }
    return nullptr;
}

LogosSelection::~LogosSelection() {
    for (const auto expr : exprs) {
        delete expr;
    }
}
