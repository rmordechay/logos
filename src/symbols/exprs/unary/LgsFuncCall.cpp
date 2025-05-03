#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"

string LgsFuncCall::getName() {
    return name;
}

string LgsFuncCall::format(string& indentStr) {
    return indentStr + name + "()";
}

string LgsFuncCall::getSignatureText(const bool withType) const {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = isMethodCall; i < args.size(); ++i) {
        strStream << args[i]->type->getName();
        if (i != args.size() - 1) strStream << ", ";
    }
    if (withType) {
        strStream << "): " << type->getName();
    } else {
        strStream << ")";
    }
    return strStream.str();
}

void LgsFuncCall::createIRStmt(CodeGenMetadata* metadata) {
    call(metadata, args);
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    return call(metadata, args);
}

void LgsFuncCall::free(CodeGenMetadata* metadata) {
    assert(false);
}

Value* LgsFuncCall::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    vector<Value*> argValues;
    const auto objRtPtr = setIRArgs(metadata, argValues, args);
    Value* IRFunc = nullptr;
    if (ref) {
        if (ref->type == PARAM) {
            assert(ref->param->IRValue);
            IRFunc = ref->param->IRValue;
        }
    } else {
        IRFunc = funcType->getIRFunc(metadata);
    }
    assert(IRFunc);
    const auto funcCall = metadata->builder.CreateCall(funcType->getIRFuncType(metadata), IRFunc, argValues);
    if (objRtPtr) return objRtPtr;
    return funcCall;
}

Value* LgsFuncCall::setIRArgs(CodeGenMetadata* metadata, vector<Value*>& argValues, const vector<LgsExpr*>& args) {
    Value* objRtPtr = nullptr;
    if (const auto obj = funcType->type->asObject()) {
        objRtPtr = metadata->builder.CreateAlloca(obj->getIRType(), nullptr);
        argValues.push_back(objRtPtr);
    }
    auto iterSize = 0;
    if (const auto method = dynamic_cast<LgsMethodImpl*>(this)) {
        iterSize = method->isStatic;
    }
    for (int i = iterSize; i < args.size(); ++i) {
        const auto arg = args[i];
        const auto argValue = arg->getIRValue(metadata);
        argValues.emplace_back(argValue);
    }
    if (objRtPtr) return objRtPtr;
    return nullptr;
}

LgsFuncCall::~LgsFuncCall() {
    // First arg of method is not freed here
    const auto indexStart = !!dynamic_cast<LgsMethodImpl*>(func);
    for (int i = indexStart; i < args.size(); ++i) {
        delete args[i];
    }
}
