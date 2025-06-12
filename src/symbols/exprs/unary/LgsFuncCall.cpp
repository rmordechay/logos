#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

Value* LgsFuncCall::call(LgsRuntime* runtime) const {
    if (callback) {
        func->setIRValue(getCallback(runtime));
    } else if (func->funcType->hasFlag(VIRTUAL)) {
        resolveVirtualFunc(runtime);
    }
    return func->call(runtime, args);
}

Value* LgsFuncCall::getCallback(LgsRuntime* runtime) const {
    switch (callback->symbolType) {
    case VAR_DEC:
        return callback->varDec->expr->getIRValue(runtime);
    case PARAM:
        return callback->param->IRValue;
    case FIELD:
        return callback->field->IRValue;
    default:
        break;
    }
    assert(0);
}

Value* LgsFuncCall::createIRValue(LgsRuntime* runtime) {
    return call(runtime);
}

void LgsFuncCall::createIRStmt(LgsRuntime* runtime) {
    call(runtime);
}

bool LgsFuncCall::equals(const LgsFuncType* other) const {
    if (other->hasFlag(HAS_DEFAULTS)) return equalsDefaultParams(other);
    if (other->hasFlag(VARIADIC)) return equalsVariadic(other);
    if (!other->hasFlag(ANONYMOUS) && name != other->name) return false;
    if (other->params.size() != args.size()) return false;
    if (other->params.size() == 0 && args.size() == 0) return true;
    for (size_t i = 0; i < other->params.size(); ++i) {
        const auto paramType = other->params[i].type;
        const auto argType = args[i]->type;
        if (!paramType->equals(argType)) return false;
    }
    return true;
}

bool LgsFuncCall::equalsDefaultParams(const LgsFuncType* funcType) const {
    const auto argsSize = args.size();
    for (size_t i = funcType->hasFlag(METHOD); i < funcType->params.size(); ++i) {
        const auto param = funcType->params[i];
        if (i >= argsSize) continue;
        const auto arg = args[i];
        if (!param.type->equals(arg->type)) return false;
    }
    return true;
}

bool LgsFuncCall::equalsVariadic(const LgsFuncType* funcType) const {
    return true;
}

void LgsFuncCall::resolveVirtualFunc(LgsRuntime* runtime) const {
    auto& builder = runtime->builder;
    const auto parent = args[0];
    const auto type = parent->type;
    const auto ptrTy = builder.getPtrTy();
    const auto parentIRValue = parent->getIRValue(runtime);
    const auto keyIR = getIRStr(runtime, func->funcType->getIRName());
    const auto mapPtr = builder.CreateLoad(ptrTy, parentIRValue);
    const auto valuePtr = builder.CreateAlloca(ptrTy);
    const auto rv = type->vtable->type->asMap()->getFunc.callIR(runtime, {mapPtr, keyIR});
    builder.CreateStore(rv, valuePtr);
    const auto vfunc = builder.CreateLoad(ptrTy, builder.CreateLoad(ptrTy, valuePtr));
    func->setIRValue(vfunc);
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
    if (type) {
        strStream << "): " << type->prettyName();
    } else {
        strStream << ')';
    }
    return strStream.str();
}