#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

Value* LgsFuncCall::call(LgsModule* module) const {
    if (callback) {
        func->setIRValue(getCallback(module));
    } else if (func->funcType->isVirtual) {
        resolveVirtualFunc(module);
    }
    return func->call(module, args);
}

Value* LgsFuncCall::getCallback(LgsModule* module) const {
    switch (callback->symbolType) {
    case VAR_DEC:
        return callback->varDec->expr->getIRValue(module);
    case PARAM:
        return callback->param->IRValue;
    case FIELD:
        return callback->field->IRValue;
    default:
        break;
    }
    assert(0);
}

Value* LgsFuncCall::createIRValue(LgsModule* module) {
    return call(module);
}

void LgsFuncCall::createIRStmt(LgsModule* module) {
    call(module);
}

bool LgsFuncCall::equals(const LgsFuncType* funcType) const {
    if (funcType->hasDefaults) return equalsDefaultParams(funcType);
    if (funcType->isVariadic) return equalsVariadic(funcType);
    if (!funcType->isAnonymous && name != funcType->name) return false;
    if (funcType->params.size() != args.size()) return false;
    if (funcType->params.size() == 0 && args.size() == 0) return true;
    for (size_t i = funcType->isStaticMethod; i < funcType->params.size(); ++i) {
        const auto paramType = funcType->params[i].type;
        const auto argType = args[i]->type;
        if (args[i]->isNull) continue;
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
        if (!param.type->equals(arg->type)) return false;
    }
    return true;
}

bool LgsFuncCall::equalsVariadic(const LgsFuncType* funcType) const {
    return true;
}

void LgsFuncCall::resolveVirtualFunc(LgsModule* module) const {
    auto& builder = module->builder;
    const auto self = args[0];
    const auto keyIR = getIRStr(module, func->funcType->getIRName());
    const auto vtablePtr = self->getIRValue(module);
    const auto vtable = self->type->vtable;
    const auto vtableIRType = vtable->type->getIRType(module);
    const auto gep = builder.CreateStructGEP(vtableIRType, vtablePtr, 0);
    const auto mapValue = builder.CreateLoad(ptrTy(module), gep);
    const auto rv = vtable->type->asMap()->getFunc.callIR(module, {mapValue, keyIR});
    func->setIRValue(rv);
}

string LgsFuncCall::getExprName() {
    return name;
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

string LgsFuncCall::format(string& indentStr) {
    return indentStr + name + "()";
}
