#include "configs/LgsConfig.h"
#include "exprs/unary/LgsVectorExpr.h"
#include "stmts/LgsField.h"
#include "types/LgsPtr.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsDArray.h"
#include "types/LgsEnum.h"
#include "types/LgsGroup.h"
#include "types/LgsMap.h"
#include "types/LgsNullable.h"
#include "types/LgsSArray.h"
#include "types/LgsUnknown.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsUInt.h"

LgsField* LgsType::getField(const std::string& name) {
    for (auto* f : fields) {
        if (f->name == name) return f;
    }
    return nullptr;
}

LgsFunc* LgsType::getMethod(const std::string& name) {
    const auto method = methods.find(name);
    if (method != methods.end()) {
        return method->second;
    }
    return nullptr;
}

bool LgsType::equals(LgsType* other) {
    return getName() == other->getName();
}

DIBasicType* LgsType::getDebugType(LgsLLVM& codeGen) {
    assert(0);
}

bool LgsType::addMethod(LgsFunc* method) {
    if (methods.find(method->funcType->name) != methods.end()) return false;
    methods[method->funcType->name] = method;
    return true;
}

bool LgsType::addField(LgsField* field) {
    for (const auto* f : fields) {
        if (f->name == field->name) return false;
    }
    if (methods.find(field->name) != methods.end()) return false;
    fields.push_back(field);
    return true;
}

bool LgsType::isBig() {
    return (asObject() || asDArray()) && getSizeBytes() >= BIG_SIZE_THRESHOLD;
}

void LgsType::freeValue(LgsLLVM& codeGen, Value* value) {

}

LgsType* LgsType::clone() {
    if (isPrimitive) return this; assert(0);
}

LgsBool* LgsType::asBool() { return dynamic_cast<LgsBool*>(this); }
LgsChar* LgsType::asChar() { return dynamic_cast<LgsChar*>(this); }
LgsShort* LgsType::asShort() { return dynamic_cast<LgsShort*>(this); }
LgsInt* LgsType::asInt() { return dynamic_cast<LgsInt*>(this); }
LgsLong* LgsType::asLong() { return dynamic_cast<LgsLong*>(this); }
LgsUInt* LgsType::asUInt() { return dynamic_cast<LgsUInt*>(this); }
LgsFloat* LgsType::asFloat() { return dynamic_cast<LgsFloat*>(this); }
LgsDouble* LgsType::asDouble() { return dynamic_cast<LgsDouble*>(this); }
LgsStr* LgsType::asStr() { return dynamic_cast<LgsStr*>(this); }
LgsObject* LgsType::asObject() { return dynamic_cast<LgsObject*>(this); }
LgsNullable* LgsType::asNullable() { return dynamic_cast<LgsNullable*>(this); }
LgsInterface* LgsType::asInterface() { return dynamic_cast<LgsInterface*>(this); }
LgsIterable* LgsType::asIterable() { return dynamic_cast<LgsIterable*>(this); }
LgsDArray* LgsType::asDArray() { return dynamic_cast<LgsDArray*>(this); }
LgsSArray* LgsType::asSArray() { return dynamic_cast<LgsSArray*>(this); }
LgsVec* LgsType::asVec() { return dynamic_cast<LgsVec*>(this); }
LgsMap* LgsType::asMap() { return dynamic_cast<LgsMap*>(this); }
LgsEnum* LgsType::asEnum() { return dynamic_cast<LgsEnum*>(this); }
LgsFuncType* LgsType::asFuncType() { return dynamic_cast<LgsFuncType*>(this); }
LgsPtr* LgsType::asPtr() { return dynamic_cast<LgsPtr*>(this); }
LgsGroup* LgsType::asGroup() { return dynamic_cast<LgsGroup*>(this); }
LgsTypePair* LgsType::asPair() { return dynamic_cast<LgsTypePair*>(this); }
bool LgsType::isVector() { return dynamic_cast<LgsVec*>(this); }
bool LgsType::isVoid() { return dynamic_cast<LgsVoid*>(this); }
bool LgsType::isUnknown() { return dynamic_cast<LgsUnknown*>(this); }

LgsType::~LgsType() {
    for (const auto& field : fields) {
        delete field;
    }
    fields.clear();
    for (const auto& [_, method] : methods) {
        if (method->funcType->isInternal) continue;
        // delete method;
    }
    methods.clear();
}
