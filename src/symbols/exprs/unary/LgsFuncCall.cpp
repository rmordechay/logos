#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"

Value* LgsFuncCall::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) const {
    if (!ref) {
        return func->call(metadata, args);
    }
    Value* IRFunc = nullptr;
    if (ref->type == PARAM) {
        IRFunc = ref->param->IRValue;
    }
    assert(IRFunc);
    return func->call(metadata, args, IRFunc);
}

string LgsFuncCall::getName() {
    return name;
}

string LgsFuncCall::format(string& indentStr) {
    return indentStr + name + "()";
}

void LgsFuncCall::createIRStmt(CodeGenMetadata* metadata) {
    call(metadata, args);
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    return call(metadata, args);
}

string LgsFuncCall::getSignatureText(const bool withType) const {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = isMethodCall; i < args.size(); ++i) {
        strStream << args[i]->type->getPrettyName();
        if (i != args.size() - 1) strStream << ", ";
    }
    if (withType) {
        strStream << "): " << type->getPrettyName();
    } else {
        strStream << ")";
    }
    return strStream.str();
}

LgsFuncCall::~LgsFuncCall() {
    // First arg of method is not freed here
    const auto indexStart = !!dynamic_cast<LgsMethodImpl*>(func);
    for (int i = indexStart; i < args.size(); ++i) {
        delete args[i];
    }
}