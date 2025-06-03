#include "exprs/unary/LgsFuncCall.h"
#include "builtin/LgsPrint.h"
#include "exprs/unary/LgsVariable.h"
#include "funcs/LgsFunc.h"

#include "stmts/LgsVarDec.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

Value* LgsFuncCall::call(LgsRuntime* runtime) const {
    if (callback) {
        func->setIRValue(getCallback(runtime));
    } else if (func->funcType.isVirtual) {
        const auto virtualFunc = resolveVirtualFunc(runtime);
        func->setIRValue(virtualFunc);
    }
    return func->call(runtime, args);
}

Value* LgsFuncCall::getCallback(LgsRuntime* runtime) const {
    switch (callback->type) {
    case VAR_DEC:
        return callback->varDec->expr->getIRValue(runtime);
    case PARAM:
        return callback->param->IRValue;
    case FIELD:
        return callback->field->IRValue;
    default:
        break;
    }
    assert(false);
}

Value* LgsFuncCall::createIRValue(LgsRuntime* runtime) {
    return call(runtime);
}

void LgsFuncCall::createIRStmt(LgsRuntime* runtime) {
    call(runtime);
}

bool LgsFuncCall::equals(const LgsFuncType* funcType) const {
    if (funcType->hasDefaultParams) return equalsDefaultParams(funcType);
    if (funcType->isVariadic) return equalsVariadic(funcType);
    return equalsRaw(funcType);
}

bool LgsFuncCall::equalsRaw(const LgsFuncType* funcType) const {
    if (!funcType->isAnonymous && name != funcType->name) return false;
    if (funcType->params.size() != args.size()) return false;
    if (funcType->params.size() == 0 && args.size() == 0) return true;
    for (size_t i = 0; i < funcType->params.size(); ++i) {
        const auto paramType = funcType->params[i]->type;
        const auto argType = args[i]->type;
        if (!paramType->equals(argType)) return false;
    }
    return true;
}

bool LgsFuncCall::equalsDefaultParams(const LgsFuncType* funcType) const {
    const auto argsSize = args.size();
    for (size_t i = funcType->isMethod; i < funcType->params.size(); ++i) {
        const auto param = funcType->params[i];
        if (i >= argsSize) continue;
        const auto arg = args[i];
        if (!param->type->equals(arg->type)) return false;
    }
    return true;
}

bool LgsFuncCall::equalsVariadic(const LgsFuncType* funcType) const {
    return true;
}

Value* LgsFuncCall::resolveVirtualFunc(LgsRuntime* runtime) const {
    const auto parent = args[0];
    const auto type = parent->type;
    const auto interface = type->asInterface();
    const auto parentIRValue = parent->getIRValue(runtime);
    const auto func = callback->func;
    const auto keyIR = getIRStr(runtime, func->funcType.getIRName());
    const auto mapPtr = runtime->builder.CreateLoad(ptrTy, parentIRValue);
    const auto rv = interface->vtable.mapType.get.callIR(runtime, {mapPtr, keyIR});
    const auto getValuePtr = runtime->builder.CreateAlloca(ptrTy);
    runtime->builder.CreateStore(rv, getValuePtr);
    return runtime->builder.CreateLoad(ptrTy, runtime->builder.CreateLoad(ptrTy, getValuePtr));
}

string LgsFuncCall::getName() {
    return name;
}

string LgsFuncCall::format(string& indentStr) {
    return indentStr + name + "()";
}

string LgsFuncCall::prettyName() {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = 0; i < args.size(); ++i) {
        strStream << args[i]->type->prettyName();
        if (i != args.size() - 1) strStream << ", ";
    }
    strStream << ')';
    return strStream.str();
}