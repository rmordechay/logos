#include "exprs/LgsFuncCall.h"

#include "data/LgsDefinitions.h"
#include "exprs/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

bool LgsFuncCall::equals(const LgsFuncType* other) const {
    if (other->hasDefaults) return equalsDefaultParams(other);
    if (other->isVariadic) return equalsVariadic(other);
    if (other->params.size() - other->isMethod != args.size()) return false;
    if (other->params.size() == 0 && args.size() == 0) return true;
    if (other->isLambda) return true;
    for (size_t i = other->isMethod; i < other->params.size(); ++i) {
        const auto param = other->params[i];
        const auto paramType = param.type;
        const auto arg = args[i - other->isMethod];
        const auto argType = arg->type;
        if (!paramType || !argType) return false;
        if (arg->isNull) continue;
        if (paramType->asFuncType()) {
            arg->completeType(paramType);
        }
        if (!param.isOwner && arg->owner) return false;
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
    const auto rv = cg.getPtrFromVtable(selfPtr, keyIR);
    func->setIRValue(rv);
}

std::string LgsFuncCall::pname() {
    std::stringstream str;
    str << name << '(';
    for (size_t i = isMethodCall; i < args.size(); ++i) {
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
