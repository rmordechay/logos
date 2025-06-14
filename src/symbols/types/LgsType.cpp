#include "stmts/LgsField.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsArray.h"
#include "types/LgsGroup.h"
#include "types/LgsMap.h"
#include "types/LgsUnknownType.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsUInt.h"

class LgsShort;

bool LgsType::equals(LgsType& other) {
    return getIRName() == other.getIRName();
}

LgsField* LgsType::getField(const string& name) {
    const auto field = fields.find(name);
    if (field != fields.end()) {
        return field->second;
    }
    return nullptr;
}

LgsFunc* LgsType::getMethod(const string& name) {
    const auto method = methods.find(name);
    if (method != methods.end()) {
        return method->second;
    }
    return nullptr;
}

void LgsType::addMethod(LgsFunc* method) {
    methods[method->funcType->name] = method;
}

LgsFunc* LgsType::findMethod(const string& name) const {
    const auto method = methods.find(name);
    if (method != methods.end()) {
        return method->second;
    }
    return nullptr;
}

void LgsType::setLocation(const Token* ctx, path* filePath) {
    location.lineNumber = ctx->getLine();
    location.posInLine = ctx->getCharPositionInLine() + 1;
    location.filePath = filePath;
    assert(location.filePath);
}

LgsType::~LgsType() {
    if (vtable) delete vtable;
}

size_t LgsType::getSizeBytes() { assert(0); }
string LgsType::getStrFormatPart() const { assert(0); }
LgsType* LgsType::clone() { assert(0); }

LgsBool* LgsType::asBool() { return dynamic_cast<LgsBool*>(this); }
LgsShort* LgsType::asShort() { return dynamic_cast<LgsShort*>(this); }
LgsInt* LgsType::asInt() { return dynamic_cast<LgsInt*>(this); }
LgsLong* LgsType::asLong() { return dynamic_cast<LgsLong*>(this); }
LgsUInt* LgsType::asUInt() { return dynamic_cast<LgsUInt*>(this); }
LgsStr* LgsType::asStr() { return dynamic_cast<LgsStr*>(this); }
LgsObject* LgsType::asObject() { return dynamic_cast<LgsObject*>(this); }
LgsInterface* LgsType::asInterface() { return dynamic_cast<LgsInterface*>(this); }
LgsIterable* LgsType::asIterable() { return dynamic_cast<LgsIterable*>(this); }
LgsArray* LgsType::asArray() { return dynamic_cast<LgsArray*>(this); }
LgsMap* LgsType::asMap() { return dynamic_cast<LgsMap*>(this); }
LgsFuncType* LgsType::asFuncType() { return dynamic_cast<LgsFuncType*>(this); }
LgsGroup* LgsType::asGroup() { return dynamic_cast<LgsGroup*>(this); }
LgsTypePair* LgsType::asPair() { return dynamic_cast<LgsTypePair*>(this); }
bool LgsType::isUnknown() { return dynamic_cast<LgsUnknownType*>(this); }
