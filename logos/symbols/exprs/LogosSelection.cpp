#include "LogosSelection.h"

Value* LogosSelection::getLLVMValue(CodeGenMetadata* metadata) {
    auto logosSymbol = metadata->theStack->getSymbol("obj");
    return LogosExpr::getLLVMValue(metadata);
}

LogosSelection::~LogosSelection() {
    for (const auto expr : exprs) {
        delete expr;
    }
}
