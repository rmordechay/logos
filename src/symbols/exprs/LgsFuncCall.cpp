#include "exprs/LgsFuncCall.h"
#include "data/LgsDefinitions.h"
#include "exprs/LgsHashMap.h"
#include "exprs/LgsVariable.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"

bool LgsFuncCall::equals(LgsExpr* other) {
    const auto otherFuncCall = other->asFuncCall();
    if (!otherFuncCall) return false;
    return name == otherFuncCall->name;
}

bool LgsFuncCall::equals(const LgsFuncType* other) const {
    if (other->hasDefaults()) return equalsDefaultParams(other);
    if (other->isVariadic) return equalsVariadic(other);
    for (size_t i = 0; i < other->params.size(); ++i) {
        const auto arg = args[i];
        const auto param = other->params[i];
        const auto argType = arg->type;
        const auto paramType = param.type;
        if (!paramType || !argType) return false;
        if (arg->isNull && !paramType->isNullable()) return false;
        if (param.isOwner != !!arg->owner) return false;
        if (!argType->canCastTo(paramType)) return false;
    }
    return true;
}

bool LgsFuncCall::equalsVariadic(const LgsFuncType* funcType) const {
    return true;
}

bool LgsFuncCall::equalsDefaultParams(const LgsFuncType* funcType) const {
    const auto argsSize = args.size();
    for (size_t i = funcType->isMethod; i < funcType->params.size(); ++i) {
        const auto param = funcType->params[i];
        if (i >= argsSize) continue;
        const auto arg = args[i];
        if (!param.type->canCastTo(arg->type)) return false;
    }
    return true;
}

void LgsFuncCall::resolveVirtualFunc(LgsLLVMGen& cg) const {
    const auto self = args[0];
    const auto keyIR = cg.getIRStr(func->funcType->getName());
    const auto selfPtr = self->IRValue;
    func->IRValue = cg.callLgsFunc("vtable_get", cg.getFT(cg.ptrTy(), {cg.ptrTy(), cg.ptrTy()}), {selfPtr, keyIR});;
}

void LgsFuncCall::completeType(LgsType* toType) {
    const auto otherFuncType = toType->asFuncType();
    if (!otherFuncType) return;
    if (args.size() != otherFuncType->params.size()) return;
    for (size_t i = otherFuncType->isMethod; i < otherFuncType->params.size(); ++i) {
        args[i]->completeType(otherFuncType->params[i].type);
    }
}

std::string LgsFuncCall::pname() {
    std::stringstream str;
    str << name << '(';
    for (size_t i = 0; i < args.size(); ++i) {
        const auto arg = args[i];
        if (arg->owner) {
            str << "owner ";
        }
        str << (arg->type ? arg->type->pname() : LGS_UNKNOWN_TYPE);
        if (i == args.size() - 1) continue;
        str << ", ";
    }
    if (type && !type->isUnknown()) {
        str << "): " << type->pname();
    } else {
        str << ')';
    }
    return str.str();
}

json::value LgsFuncCall::asJSON() {
    json::object jsonObj;
    jsonObj["name"] = name;
    jsonObj["type"] = type->asJSON();
    json::array jsonArgs;
    for (const auto& arg : args) {
        jsonArgs.emplace_back(arg->asJSON());
    }
    return jsonObj;
}

LgsFuncCall::~LgsFuncCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
