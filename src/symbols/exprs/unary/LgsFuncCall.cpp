#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "types/LgsVoid.h"

string LgsFuncCall::getName() {
    return name;
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    return func->call(metadata, args);
}

string LgsFuncCall::getArgsTypeStr() const {
    std::ostringstream result;
    if (args.empty()) {
        result << LgsVoid::name;
        return result.str();
    }
    const auto isMethod = parentName != "";
    for (size_t i = isMethod; i < args.size(); ++i) {
        result << args[i]->type->getName();
        if (i != args.size() - 1) result << ", ";
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
