#include "application/LogosUtils.h"

#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstant.h"
#include "exprs/LogosFuncCall.h"
#include "exprs/LogosSelection.h"

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
    case CONSTRUCTOR:
        return LogosSymbol(type, dynamic_cast<LogosConstructor*>(expr));
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
    }
    return LogosSymbol();
}

Module* Utils::createLLVMModuleFromFile(const string& filePath, LLVMContext& context, const TargetMachine& tm) {
    SMDiagnostic err;
    auto module = parseIRFile(filePath, err, context);
    module->setDataLayout(tm.createDataLayout());
    return module.release();
}

void Utils::emitLLVMFile(const string& filePath, const Module* const module) {
    error_code EC;
    raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
}


