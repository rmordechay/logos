#include "LogosSymbol.h"
#include <exprs/LogosExpr.h>
#include <exprs/LogosArray.h>
#include <exprs/LogosArrayIndex.h>
#include <exprs/LogosBinaryExpr.h>
#include <exprs/LogosConstant.h>
#include <exprs/LogosFuncCall.h>
#include <exprs/LogosInstance.h>
#include <exprs/LogosSelection.h>
#include <exprs/LogosVariable.h>

LogosSymbol LogosSymbol::createSymbol(LogosExpr* expr) {
    const auto type = expr->getSymbolType();
    switch (type) {
    case INSTANCE:
        return LogosSymbol(type, dynamic_cast<LogosInstance*>(expr));
    case FUNC_CALL:
        return LogosSymbol(type, dynamic_cast<LogosFuncCall*>(expr));
    case VARIABLE:
        return LogosSymbol(type, dynamic_cast<LogosVariable*>(expr));
    case CONSTANT:
        return LogosSymbol(type, dynamic_cast<LogosConstant*>(expr));
    case BINARY_EXPR:
        return LogosSymbol(type, dynamic_cast<LogosBinaryExpr*>(expr));
    case SELECTION:
        return LogosSymbol(type, dynamic_cast<LogosSelection*>(expr));
    case ARRAY:
        return LogosSymbol(type, dynamic_cast<LogosArray*>(expr));
    case ARRAY_INDEX:
        return LogosSymbol(type, dynamic_cast<LogosArrayIndex*>(expr));
    default:
        break;
    }
    return LogosSymbol();
}