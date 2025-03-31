#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"

string LgsFuncCall::getName() {
    return signature.name;
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    assert(func && signature.composedName != "");
    return func->call(metadata, args);
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
    const auto iterStart = signature.parentName == "" ? 0 : 1;
    for (int i = iterStart; i < args.size(); ++i) {
        delete args[i];
    }
}
