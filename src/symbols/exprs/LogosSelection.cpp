#include "exprs/LogosSelection.h"

#include "LogosUtils.h"
#include "exprs/LogosFuncCall.h"
#include "funcs/LogosUserFunc.h"

Value *resolveSelection(CodeGenMetadata* metadata, LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr) {
    const auto symbol = metadata->theStack->getSymbol(previousExpr->getName());
    switch (symbol->type) {
    case FIELD:
        break;
    case CONSTRUCTOR: {
        const auto obj = symbol->constructor->obj;
        const auto funcCall = obj->funcs[nextExpr->getName()];
        funcCall->getLLVMValue(metadata);
        metadata->theStack->addGlobalSymbol(LOGOS_THIS, LogosSymbol(OBJECT, obj));
        break;
    }
    case FUNC_CALL: {
        const auto funcCall = symbol->funcCall;
        funcCall->getLLVMValue(metadata);
        break;
    }
    case VARIABLE:
        break;
    case CONSTANT:
        break;
    default:
        break;
    }
    return nullptr;
}

Value* LogosSelection::getLLVMValue(CodeGenMetadata* metadata) {
    if (llvmValue) return llvmValue;
    Value* v = nullptr;
    for (size_t i = 0; i < exprs.size() - 1; ++i) {
        const auto previousExpr = exprs[i];
        const auto nextExpr = exprs[i + 1];
        v = resolveSelection(metadata, previousExpr, nextExpr);
    }
    llvmValue = v;
    return llvmValue;
}

LogosSymbolType LogosSelection::getSymbolType() {
    return SELECTION;
}

LogosSelection::~LogosSelection() {
    for (const auto expr : exprs) {
        delete expr;
    }
}
