#include "types/LgsType.h"
#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"
#include "types/primitives/LgsInt.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/array/LgsArray.h"
#include "types/map/LgsMap.h"
#include "types/LgsUnknownType.h"
#include "types/primitives/LgsBool.h"

bool LgsType::equals(LgsType& other) {
    return getIRName() == other.getIRName();
}

bool LgsType::canIndexTo(LgsType* indexType) {
    return false;
}

size_t LgsType::getSize() {
    assert(false);
}

json LgsType::asJSON() const {
    assert(false);
}

LgsField* LgsType::getField(const string& name) {
    const auto field = fields.find(name);
    if (field != fields.end()) {
        return field->second;
    }
    return nullptr;
}

void LgsType::addMethod(LgsMethodImpl* method) {
    methods[method->funcType.name].push_back(method);
}

LgsMethodImpl* LgsType::findMethod(LgsFuncCall* funcCall) const {
    const auto overloads = getMethodOverloads(funcCall->name);
    for (const auto& overload : overloads) {
        if (overload->funcType.equals(funcCall)) {
            return overload;
        }
    }
    return nullptr;
}

vector<LgsMethodImpl*> LgsType::getMethodOverloads(const string& funcName) const {
    const auto method = methods.find(funcName);
    if (method != methods.end()) {
        return method->second;
    }
    return {};
}

// TODO remove this func due to double iterations
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

LgsBool* LgsType::asBool() { return dynamic_cast<LgsBool*>(this); }
LgsObject* LgsType::asObject() { return dynamic_cast<LgsObject*>(this); }
LgsInterface* LgsType::asInterface() { return dynamic_cast<LgsInterface*>(this); }
LgsIterable* LgsType::asIterable() { return dynamic_cast<LgsIterable*>(this); }
LgsArray* LgsType::asArray() { return dynamic_cast<LgsArray*>(this); }
LgsFuncType* LgsType::asFuncType() { return dynamic_cast<LgsFuncType*>(this); }
LgsStr* LgsType::asStr() { return dynamic_cast<LgsStr*>(this); }
LgsInt* LgsType::asInt() { return dynamic_cast<LgsInt*>(this); }
LgsMap* LgsType::asMap() { return dynamic_cast<LgsMap*>(this); }
bool LgsType::isUnknown() { return dynamic_cast<LgsUnknownType*>(this); }
