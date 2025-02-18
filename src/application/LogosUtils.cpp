#include "application/LogosUtils.h"

#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstant.h"
#include "exprs/LogosFuncCall.h"
#include "exprs/LogosSelection.h"
#include "object/LogosField.h"

#include <LogosDefinitions.h>
#include <exprs/LogosArray.h>
#include <exprs/LogosArrayIndex.h>
#include <exprs/LogosVariable.h>
#include <llvm/Support/FileSystem.h>

using namespace std;

bool Utils::isLogosFile(const filesystem::directory_entry& filePath) {
    return filePath.is_regular_file() && filePath.path().extension().string() == LOGOS_EXTENSION;
}

bool Utils::isMainFile(const filesystem::directory_entry& filePath) {
    return filePath.path().stem().string() == LOGOS_MAIN_FILE;
}

LogosSymbol Utils::createSymbol(LogosExpr* expr) {
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
    case FIELD:
        return LogosSymbol(type, dynamic_cast<LogosField*>(expr));
    case OBJECT:
        return LogosSymbol(type, dynamic_cast<LogosObject*>(expr));
    case FUNC:
        return LogosSymbol(type, dynamic_cast<LogosFunc*>(expr));
    case BINARY_EXPR:
        return LogosSymbol(type, dynamic_cast<LogosBinaryExpr*>(expr));
    case SELECTION:
        return LogosSymbol(type, dynamic_cast<LogosSelection*>(expr));
    case ARRAY:
        return LogosSymbol(type, dynamic_cast<LogosArray*>(expr));
    case ARRAY_INDEX:
        return LogosSymbol(type, dynamic_cast<LogosArrayIndex*>(expr));
    }
    return LogosSymbol();
}
