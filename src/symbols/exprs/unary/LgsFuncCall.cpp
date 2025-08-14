#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

Value* LgsFuncCall::createIRValue(LgsCodeGen* codeGen) {
    if (callback) {
        func->setIRValue(getCallback(codeGen));
    } else if (func->funcType->isVirtual) {
        resolveVirtualFunc(codeGen);
    }
    return func->call(codeGen, args);
}

void LgsFuncCall::createIRStmt(LgsCodeGen* codeGen) {
    createIRValue(codeGen);
}

Value* LgsFuncCall::getCallback(LgsCodeGen* codeGen) const {
    switch (callback->symbolType) {
    case VAR_DEC:
        return callback->varDec->expr->getIRValue(codeGen);
    case PARAM:
        return callback->param->IRValue;
    case ENUM_FIELD:
        return callback->field->IRValue;
    default:
        break;
    }
    assert(0);
}

void LgsFuncCall::resolveVirtualFunc(LgsCodeGen* codeGen) const {
    auto& builder = codeGen->builder;
    const auto self = args[0];
    const auto keyIR = codeGen->getIRStr(func->funcType->getName());
    const auto selfPtr = self->getIRValue(codeGen);
    const auto vtable = self->type->asObject()->vtable;
    const auto vtableMap = vtable->type->asMap();
    const auto mapType = vtable->type->getIRType(codeGen);
    const auto mapPtr = builder.CreateGEP(mapType, selfPtr, {codeGen->i32Zero()});
    auto rv = vtableMap->getFunc.callIR(codeGen, {mapPtr, keyIR});
    rv = builder.CreateLoad(codeGen->ptrTy(), rv);
    func->setIRValue(rv);
}

bool LgsFuncCall::equals(const LgsFuncType* funcType) const {
    if (funcType->hasDefaults) return equalsDefaultParams(funcType);
    if (funcType->isVariadic) return equalsVariadic(funcType);
    if (funcType->name != "" && name != funcType->name) return false;
    if (funcType->params.size() != args.size()) return false;
    if (funcType->params.size() == 0 && args.size() == 0) return true;
    for (size_t i = funcType->isStatic; i < funcType->params.size(); ++i) {
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

std::string LgsFuncCall::prettyName() {
    std::stringstream strStream;
    strStream << name << '(';
    for (size_t i = isMethodCall; i < args.size(); ++i) {
        strStream << args[i]->type->prettyName();
        if (i != args.size() - 1) strStream << ", ";
    }
    if (type && !type->isUnknown) {
        strStream << "): " << type->prettyName();
    } else {
        strStream << ')';
    }
    return strStream.str();
}

std::string LgsFuncCall::format(std::string& indentStr) {
    return indentStr + name + "()";
}
