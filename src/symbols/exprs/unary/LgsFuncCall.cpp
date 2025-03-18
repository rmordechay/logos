#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"

string LgsFuncCall::getName() {
    return name;
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    assert(composedName != "");
    return func->call(metadata, args);
}

vector<string> LgsFuncCall::getArgTypeNames() const {
    vector<string> names;
    for (const auto& arg : args) {
        names.emplace_back(arg->type->getName());
    }
    return names;
}

void LgsFuncCall::setComposedName() {
    composedName = LgsFunc::getComposedName(name, getArgTypeNames());
}

LgsFuncCall::~LgsFuncCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
