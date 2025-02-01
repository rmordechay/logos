#include "LogosSelection.h"

Value* LogosSelection::getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) {
    return LogosExpr::getLLVMValue(builder, stackFrame, module);
}

LogosSelection::~LogosSelection() {
    for (const auto expr : exprs) {
        delete expr;
    }
}
