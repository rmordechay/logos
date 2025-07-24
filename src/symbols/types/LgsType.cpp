#include "stmts/LgsField.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsDArray.h"
#include "types/LgsEnum.h"
#include "types/LgsGroup.h"
#include "types/LgsMap.h"
#include "types/LgsNullable.h"
#include "types/LgsPtr.h"
#include "types/LgsSArray.h"
#include "types/LgsUnknownType.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsUInt.h"

class LgsShort;

bool LgsType::equals(LgsType& other) {
    return getName() == other.getName();
}

LgsField* LgsType::getField(const string& name) {
    const auto field = fields.find(name);
    if (field != fields.end()) {
        return field->second;
    }
    return nullptr;
}

bool LgsType::addMethod(LgsFunc* method) {
    if (methods.find(method->funcType->name) != methods.end()) return false;
    if (fields.find(method->funcType->name) != fields.end()) return false;
    methods[method->funcType->name] = method;
    return true;
}

bool LgsType::addField(LgsField* field) {
    if (fields.find(field->name) != fields.end()) return false;
    if (methods.find(field->name) != methods.end()) return false;
    fields[field->name] = field;
    return true;
}

LgsFunc* LgsType::getMethod(const string& name) const {
    const auto method = methods.find(name);
    if (method != methods.end()) {
        return method->second;
    }
    return nullptr;
}

void LgsType::setLocation(const Token* ctx, const Token* end, const path& filePath) {
    location.lineNumberStart = ctx->getLine();
    location.posInLineStart = ctx->getCharPositionInLine() + 1;
    location.filePath = filePath;
}

size_t LgsType::getSizeBytes() { assert(0); }
string LgsType::getStrFormatPart() const { assert(0); }

LgsPtr* LgsType::asPtr() { return dynamic_cast<LgsPtr*>(this); }
LgsBool* LgsType::asBool() { return dynamic_cast<LgsBool*>(this); }
LgsShort* LgsType::asShort() { return dynamic_cast<LgsShort*>(this); }
LgsInt* LgsType::asInt() { return dynamic_cast<LgsInt*>(this); }
LgsLong* LgsType::asLong() { return dynamic_cast<LgsLong*>(this); }
LgsUInt* LgsType::asUInt() { return dynamic_cast<LgsUInt*>(this); }
LgsStr* LgsType::asStr() { return dynamic_cast<LgsStr*>(this); }
LgsObject* LgsType::asObject() { return dynamic_cast<LgsObject*>(this); }
LgsNullable* LgsType::asNullable() { return dynamic_cast<LgsNullable*>(this); }
LgsInterface* LgsType::asInterface() { return dynamic_cast<LgsInterface*>(this); }
LgsIterable* LgsType::asIterable() { return dynamic_cast<LgsIterable*>(this); }
LgsDArray* LgsType::asDArray() { return dynamic_cast<LgsDArray*>(this); }
LgsSArray* LgsType::asSArray() { return dynamic_cast<LgsSArray*>(this); }
LgsMap* LgsType::asMap() { return dynamic_cast<LgsMap*>(this); }
LgsEnum* LgsType::asEnum() { return dynamic_cast<LgsEnum*>(this); }
LgsFuncType* LgsType::asFuncType() { return dynamic_cast<LgsFuncType*>(this); }
LgsGroup* LgsType::asGroup() { return dynamic_cast<LgsGroup*>(this); }
LgsTypePair* LgsType::asPair() { return dynamic_cast<LgsTypePair*>(this); }

LgsType::~LgsType() {
    if (vtable) delete vtable;
}