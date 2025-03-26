#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"

string LgsFuncCall::getName() {
    return name;
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    assert(func && composedName != "");
    return func->call(metadata, args);
}

void LgsFuncCall::setComposedName() {
    vector<string> argTypeNames;
    for (const auto& arg : args) {
        argTypeNames.emplace_back(arg->type->getName());
    }
    composedName = LgsFunc::getComposedName(name, argTypeNames);
}

LgsFuncCall::~LgsFuncCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
