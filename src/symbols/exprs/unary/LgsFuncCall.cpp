#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsMethodImpl.h"
#include "types/LgsVoid.h"

string LgsFuncCall::getName() {
    return name;
}

string LgsFuncCall::format(string& indentStr) {
    return indentStr + name + "()";
}

string LgsFuncCall::getSignatureText() const {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = 0; i < args.size(); ++i) {
        strStream << args[i]->type->getName();
        if (i != args.size() - 1) strStream << ", ";
    }
    strStream << ')';
    if (type) {
        strStream << ": " << type->getName();
    }
    return strStream.str();
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    return func->call(metadata, args);
}

void LgsFuncCall::free(CodeGenMetadata* metadata) {

}

LgsFuncCall::~LgsFuncCall() {
    // First arg of method is not freed here
    const auto indexStart = !!dynamic_cast<LgsMethodImpl*>(func);
    for (int i = indexStart; i < args.size(); ++i) {
        delete args[i];
    }
}
