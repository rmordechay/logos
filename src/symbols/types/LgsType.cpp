#include "types/LgsType.h"
#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"
#include "types/primitives/LgsInt.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "../../../include/symbols/types/LgsArray.h"
#include "../../../include/symbols/types/LgsMap.h"
#include "types/LgsUnknownType.h"
#include "types/primitives/LgsBool.h"

bool LgsType::equals(LgsType& other) {
    return getIRName() == other.getIRName();
}

size_t LgsType::getSize() {
    assert(false);
}

json LgsType::asJSON() const {
    assert(false);
}

string LgsType::getStrFormatPart() const {
    assert(false);
}

LgsType* LgsType::clone() {
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
    methods[method->funcType.name] = method;
}

LgsMethodImpl* LgsType::findMethod(const string& name) const {
    const auto method = methods.find(name);
    if (method != methods.end()) {
        return method->second;
    }
    return nullptr;
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
