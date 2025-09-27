#include "exprs/LgsVectorExpr.h"
#include "stmts/LgsField.h"
#include "types/LgsPtr.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/iterables/LgsDArray.h"
#include "types/LgsEnum.h"
#include "types/LgsGroup.h"
#include "types/iterables/LgsMap.h"
#include "types/LgsNullable.h"
#include "types/LgsSubType.h"
#include "types/LgsUnknown.h"
#include "types/LgsVoid.h"
#include "types/iterables/LgsSArray.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsByte.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

LgsType* LgsType::extendInt() {
    if (asBool()) {
        return &LGS_BYTE;
    }
    if (asByte()) {
        return &LGS_SHORT;
    }
    if (asShort()) {
        return &LGS_INT;
    }
    if (asInt()) {
        return &LGS_LONG;
    }
    return this;
}

bool LgsType::addField(LgsField* field) {
    for (const auto* f : fields) {
        if (f->name == field->name) return false;
    }
    if (methods.find(field->name) != methods.end()) return false;
    fields.push_back(field);
    return true;
}

bool LgsType::addMethod(LgsFunc* method) {
    if (methods.find(method->funcType->name) != methods.end()) return false;
    methods[method->funcType->name] = method;
    return true;
}

bool LgsType::addEmptyMethod(const std::string& name) {
    if (methods.find(name) != methods.end()) return false;
    methods[name] = nullptr;
    return true;
}

bool LgsType::equals(LgsType* other) {
    return getName() == other->getName();
}

bool LgsType::isVoid() {
    return dynamic_cast<LgsVoid*>(this);
}

bool LgsType::isNumber() const {
    return isInt || isFloat;
}

bool LgsType::isBig() {
    return (asObject() || asDArray()) && getSizeBytes() >= BIG_SIZE_THRESHOLD;
}

bool LgsType::isNullable() {
    return asNullable() || asPtr();
}

bool LgsType::isUnknown() {
    return dynamic_cast<LgsUnknown*>(this);
}

bool LgsType::isSliceable() {
    return asStr() || asDArray() || asSArray();
}

LgsAny* LgsType::asAny() {
    return dynamic_cast<LgsAny*>(this);
}

LgsChar* LgsType::asChar() {
    return dynamic_cast<LgsChar*>(this);
}

LgsStr* LgsType::asStr() {
    return dynamic_cast<LgsStr*>(this);
}

LgsBool* LgsType::asBool() {
    return dynamic_cast<LgsBool*>(this);
}

LgsByte* LgsType::asByte() {
    return dynamic_cast<LgsByte*>(this);
}

LgsInt* LgsType::asInt() {
    return dynamic_cast<LgsInt*>(this);
}

LgsShort* LgsType::asShort() {
    return dynamic_cast<LgsShort*>(this);
}

LgsLong* LgsType::asLong() {
    return dynamic_cast<LgsLong*>(this);
}

LgsSize* LgsType::asSize() {
    return dynamic_cast<LgsSize*>(this);
}

LgsUInt* LgsType::asUInt() {
    return dynamic_cast<LgsUInt*>(this);
}

LgsFloat* LgsType::asFloat() {
    return dynamic_cast<LgsFloat*>(this);
}

LgsDouble* LgsType::asDouble() {
    return dynamic_cast<LgsDouble*>(this);
}

LgsMap* LgsType::asMap() {
    return dynamic_cast<LgsMap*>(this);
}

LgsEnum* LgsType::asEnum() {
    return dynamic_cast<LgsEnum*>(this);
}

LgsNullable* LgsType::asNullable() {
    return dynamic_cast<LgsNullable*>(this);
}

LgsObject* LgsType::asObject() {
    return dynamic_cast<LgsObject*>(this);
}

LgsInterface* LgsType::asInterface() {
    return dynamic_cast<LgsInterface*>(this);
}

LgsIterable* LgsType::asIterable() {
    return dynamic_cast<LgsIterable*>(this);
}

LgsDArray* LgsType::asDArray() {
    return dynamic_cast<LgsDArray*>(this);
}

LgsSArray* LgsType::asSArray() {
    return dynamic_cast<LgsSArray*>(this);
}

LgsVec* LgsType::asVec() {
    return dynamic_cast<LgsVec*>(this);
}

LgsFuncType* LgsType::asFuncType() {
    return dynamic_cast<LgsFuncType*>(this);
}

LgsPtr* LgsType::asPtr() {
    return dynamic_cast<LgsPtr*>(this);
}

LgsGroup* LgsType::asGroup() {
    return dynamic_cast<LgsGroup*>(this);
}

LgsSubType* LgsType::asSubtype() {
    return dynamic_cast<LgsSubType*>(this);
}

LgsTypePair* LgsType::asPair() {
    return dynamic_cast<LgsTypePair*>(this);
}

LgsField* LgsType::getField(const std::string& name) {
    for (auto* f : fields) {
        if (f->name == name) return f;
    }
    return nullptr;
}

LgsFunc* LgsType::getMethod(const std::string& name) {
    const auto method = methods.find(name);
    if (method != methods.end()) return method->second;
    return nullptr;
}

Lgs_RTType LgsType::getRTType() {
    assert(0);
}

LgsType* LgsType::applyOp(LgsType* other, const LgsOperator op) {
    assert(0);
}

DIBasicType* LgsType::getDebugType(LgsLLVMGen& cg) {
    assert(0);
}

LgsType* LgsType::clone() {
    if (isPrimitive || asSArray()) return this;
    assert(0);
}

Value* LgsType::addIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::subIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::mulIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::divIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::modIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::eqIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::neIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::ltIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::gtIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::geIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::leIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::bitAndIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::bitOrIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::bitXorIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::lshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::rshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::andIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}

Value* LgsType::orIR(LgsLLVMGen& cg, Value* self, Value* other) {
    assert(0);
}
