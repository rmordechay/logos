#include "types/LgsType.h"
#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"

bool LgsType::equals(const LgsType& other) {
    return getName() == other.getName();
}

void LgsType::setLocation(const antlr4::Token* ctx) {
    location.lineNumber = ctx->getLine();
    location.posInLine = ctx->getCharPositionInLine() + 1;
}

LgsObject* LgsType::asObject() {
    return dynamic_cast<LgsObject*>(this);
}

bool LgsType::isVoid() {
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

LgsMethodImpl* LgsType::findMethod(const LgsFuncCall* funcCall) const {
    const auto overloads = getMethodsOverloads(funcCall->name);
    for (const auto& overload : overloads) {
        if (overload->isEqual(funcCall)) {
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

Type* LgsUnknownType::getIRType() {
    assert(false);
}