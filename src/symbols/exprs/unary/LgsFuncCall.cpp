#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"

string LgsFuncCall::getName() {
    return signature.name;
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    assert(func && signature.composedName != "");
    return func->call(metadata, args);
}

void LgsFuncCall::setComposedName() {
    for (const auto& arg : args) {
        signature.argTypeNames.emplace_back(arg->type->getName());
    }
    signature.setComposedName();
}

string LgsFuncCall::getArgsTypeStr() const {
    std::ostringstream result;
    for (size_t i = 0; i < args.size(); ++i) {
        if (i > 0) result << ", ";
        result << args[i]->type->getName();
    }
    return result.str();
}

LgsFuncCall::~LgsFuncCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
