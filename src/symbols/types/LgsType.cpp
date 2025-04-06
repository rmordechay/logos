#include "types/LgsType.h"

#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsMethodImpl.h"

#include "stmts/LgsField.h"

LgsField* LgsType::getField(const string& name) {
    const auto it = fields.find(name);
    if (it != fields.end()) {
        return it->second;
    }
    return nullptr;
}

LgsMethodImpl* LgsType::getMethod(const LgsFuncCall* funcCall) const {
    assert(funcCall->composedName != "");
    const auto overloads = getMethodsOverloads(funcCall->name);
    for (const auto& overload : overloads) {
        if (overload->signature.composedName == funcCall->composedName) {
            return overload;
        }
    }
    return nullptr;
}

bool LgsType::equals(const LgsType& other) {
    return getName() == other.getName();
}

LgsMethodImpl* LgsType::getMethod(const LgsFuncSignature* signature) const {
    assert(signature->composedName != "");
    const auto overloads = getMethodsOverloads(signature->name);
    for (const auto& overload : overloads) {
        if (overload->signature.composedName == signature->composedName) {
            return overload;
        }
    }
    return nullptr;
}

vector<LgsMethodImpl*> LgsType::getMethodsOverloads(const string& funcName) const {
    const auto method = methods.find(funcName);
    if (method != methods.end()) {
        return method->second;
    }
    return {};
}

Type* LgsType::getIRType() {
    assert(false);
}

Type* LgsType::getIRType(int size) {
    assert(false);
}