#include "LogosSelection.h"

#include "LogosConstructor.h"
#include "object/LogosObject.h"

Value* LogosSelection::getLLVMValue(CodeGenMetadata* metadata) {
    const auto logosSymbol = metadata->theStack->getSymbol(names[0])->varDec->expr;
    const auto name = dynamic_cast<LogosConstructor*>(logosSymbol)->name;
    const auto obj = metadata->theStack->getSymbol(name)->object;
    auto basicString = names[1];
    for (const auto func : obj->funcs) {
        if (func->name == name) {
            // TODO functions are added full like add(1, 2). Change string to expr
            auto functionCallee = func->getFuncCallee(metadata);
        }
    }
    return LogosExpr::getLLVMValue(metadata);
}

