#include "exprs/LgsFuncCall.h"

#include "configs/LgsDefinitions.h"
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
        const auto otherParamType = other->params[i].type;
        const auto arg = args[i - other->isMethod];
        const auto argType = arg->type;
        if (!otherParamType || !argType) return false;
        if (arg->isNull) continue;
        if (otherParamType->asFuncType()) {
            arg->completeType(otherParamType);
        }
        if (!argType->canCastTo(otherParamType)) return false;
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
    std::stringstream strStream;
    strStream << name << '(';
    for (size_t i = isMethodCall; i < args.size(); ++i) {
        strStream << (args[i]->type ? args[i]->type->pname() : LGS_UNKNOWN_TYPE);
        if (i != args.size() - 1) strStream << ", ";
    }
    if (type && !type->isUnknown()) {
        strStream << "): " << type->pname();
    } else {
        strStream << ')';
    }
    return strStream.str();
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
