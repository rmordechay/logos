#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"

string LgsFuncCall::getName() {
    return name;
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
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

void LgsFuncCall::free(CodeGenMetadata* metadata) {

}

LgsFuncCall::~LgsFuncCall() {
    const auto iterStart = parentName == "" ? 0 : 1;
    for (int i = iterStart; i < args.size(); ++i) {
        delete args[i];
    }
}
