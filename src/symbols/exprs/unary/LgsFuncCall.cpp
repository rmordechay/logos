#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

Value* LgsFuncCall::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) const {
    if (!ref) return func->call(metadata, args);
    if (ref->type == PARAM) {
        func->setIRValue(ref->param->IRValue);
    } else if (ref->type == VAR_DEC) {
        func->setIRValue(ref->varDec->IRValue);
    } else if (ref->type == FUNC) {
        assert(false);
    }
    return func->call(metadata, args);
}

string LgsFuncCall::getIRName() const {
    vector<string> paramTypeNames;
    for (const auto& arg : args) {
        paramTypeNames.emplace_back(arg->type->getIRName());
    }
    return LgsFuncType::getComposedName(name, "", paramTypeNames);
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

string LgsFuncCall::getText() const {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = isMethodCall; i < args.size(); ++i) {
        strStream << args[i]->type->prettyName();
        if (i != args.size() - 1) strStream << ", ";
    }
    strStream << ")";
    return strStream.str();
}

LgsFuncCall::~LgsFuncCall() {
    // First arg of method is not freed here
    const auto indexStart = !!dynamic_cast<LgsMethodImpl*>(func);
    for (int i = indexStart; i < args.size(); ++i) {
        delete args[i];
    }
}
