#include "types/LgsType.h"
#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

bool LgsType::equals(const LgsType& other) {
    return getName() == other.getName();
}

bool LgsType::isVoid() {
    return false;
}

bool LgsType::isIterable() {
    return false;
}

json LgsType::asJSON() const {
    assert(false);
}

LgsField* LgsType::getField(const string& name) {
    const auto it = fields.find(name);
    if (it != fields.end()) {
        return it->second;
    }
    return nullptr;
}

void LgsType::addMethod(LgsMethodImpl* method) {
    methods[method->signature.name].push_back(method);
}

LgsMethodImpl* LgsType::findMethod(const LgsFuncCall* funcCall) const {
    const auto overloads = getMethodsOverloads(funcCall->name);
    for (const auto& overload : overloads) {
        if (overload->equals(funcCall)) {
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

vector<LgsMethodImpl*> LgsType::getAllMethods() const {
    vector<LgsMethodImpl*> overloads;
    for (const auto& method : methods) {
        for (const auto& overload : method.second) {
            overloads.emplace_back(overload);
        }
    }
    return overloads;
}

void LgsType::setLocation(const antlr4::Token* ctx) {
    location.lineNumber = ctx->getLine();
    location.posInLine = ctx->getCharPositionInLine() + 1;
}

LgsObject* LgsType::asObject() {
    return dynamic_cast<LgsObject*>(this);
}

LgsInterface* LgsType::asInterface() {
    return dynamic_cast<LgsInterface*>(this);
}

LgsStr* LgsType::asStr() {
    return dynamic_cast<LgsStr*>(this);
}

Type* LgsUnknownType::getIRType() {
    assert(false);
}
