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

bool LgsFuncCall::equals(const LgsFuncType* module) const {
    if (module->hasDefaults) return equalsDefaultParams(module);
    if (module->isVariadic) return equalsVariadic(module);
    if (!module->isAnonymous && name != module->name) return false;
    if (module->params.size() != args.size()) return false;
    if (module->params.size() == 0 && args.size() == 0) return true;
    for (size_t i = module->isStaticMethod; i < module->params.size(); ++i) {
        const auto paramType = module->params[i].type;
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
    const auto parent = args[0];
    const auto type = parent->type;
    const auto ptrTy = builder.getPtrTy();
    const auto parentIRValue = parent->getIRValue(module);
    const auto keyIR = getIRStr(module, func->funcType->getIRName());
    const auto mapPtr = builder.CreateLoad(ptrTy, parentIRValue);
    const auto valuePtr = builder.CreateAlloca(ptrTy);
    const auto rv = type->vtable->type->asMap()->getFunc.callIR(module, {mapPtr, keyIR});
    builder.CreateStore(rv, valuePtr);
    const auto vfunc = builder.CreateLoad(ptrTy, builder.CreateLoad(ptrTy, valuePtr));
    func->setIRValue(vfunc);
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
