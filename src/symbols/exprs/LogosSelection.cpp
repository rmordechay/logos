#include "exprs/LogosSelection.h"

#include "LogosUtils.h"
#include "exprs/LogosFuncCall.h"

LogosExpr* f(LogosUnaryExpr* expr);

void resolveSymbol(CodeGenMetadata* metadata, const LogosSymbol* currentSymbol) {
    switch (currentSymbol->type) {
    case FIELD: {
        currentSymbol->field->expr->getLLVMValue(metadata);
        break;
    }
    case VAR_DEC: {
        currentSymbol->varDec->expr->getLLVMValue(metadata);
        break;
    }
    case OBJECT: {
        currentSymbol->object->getLLVMType();
        break;
    }
    case FUNC: {
        currentSymbol->func->getLLVMValue(metadata);
        break;
    }
    }
}

void resolveSelection(const CodeGenMetadata* metadata, LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr) {
    const auto symbol = metadata->theStack->getSymbol(previousExpr->getName());
    switch (symbol->type) {
    case FIELD:
        break;
    case VAR_DEC:
        break;
    case OBJECT:
        break;
    case FUNC:
        break;
    }
}

Value* LogosSelection::getLLVMValue(CodeGenMetadata* metadata) {
    auto previous = exprs[0];
    for (int i = 1; i < exprs.size(); ++i) {
        const auto next = exprs[i];
        resolveSelection(metadata, previous, next);
        previous = next;
    }
    return nullptr;
}

LogosSelection::~LogosSelection() {
    for (const auto expr : exprs) {
        delete expr;
    }
}
