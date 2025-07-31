#include "types/LgsObject.h"
#include "exprs/unary/LgsInstance.h"
#include "stmts/LgsField.h"
#include "types/LgsGroup.h"
#include "utils/LgsUtils.h"

string LgsObject::prettyName() {
    return name;
}

string LgsObject::getName() {
    return name;
}

Type* LgsObject::getIRType(LgsCodeGen* codeGen) {
    // Add one or zero if table exists
    const size_t offset = !!vtable;
    vector<Type*> elementTypes(fields.size() + offset);
    size_t position = 0;
    if (vtable) {
        elementTypes[position++] = vtable->type->getIRType(codeGen);
    }
    for (const auto [_, field] : fields) {
        const auto fieldType = field->type->getIRType(codeGen);
        elementTypes[field->position + offset] = fieldType;
        field->position = position++;
    }
    IRType = StructType::getTypeByName(codeGen->context, name);
    if (!IRType) {
        IRType = StructType::create(codeGen->context, elementTypes, name);
    }
    for (const auto field : fields) {
        field.second->parentIRType = IRType;
    }
    return IRType;
}

LgsExpr* LgsObject::getZeroValue() {
    return new LgsInstance(this);
}

string LgsObject::getStrFormatPart() const {
    stringstream str;
    str << '{';
    for (const auto [name, field] : fields) {
        str << name << " = " << field->type->getStrFormatPart();
    }
    str << '}';
    return str.str();
}

bool LgsObject::equals(LgsType* other) {
    if (const auto group = other->asGroup()) {
        for (const auto groupType : group->types) {
            if (name == groupType->getName()) {
                return true;
            }
        }
        return false;
    }
    return name == other->getName();
}

void LgsObject::freeValue(LgsCodeGen* codeGen, Value* value) {
    codeGen->builder.CreateFree(value);
}

LgsObject* LgsObject::clone() {
    const auto cloned = new LgsObject(*this);
    cloned->hasVirtuals = hasVirtuals;
    cloned->isVoid = isVoid;
    cloned->isInt = isInt;
    cloned->isHeapAlloc = isHeapAlloc;
    cloned->isUnsigned = isUnsigned;
    cloned->isPrimitive = isPrimitive;
    cloned->isSizeBig = isSizeBig;
    cloned->isBuiltin = isBuiltin;
    cloned->isUnknown = isUnknown;
    cloned->canSlice = canSlice;
    cloned->fields.clear();
    for (const auto [name, field] : fields) {
        cloned->fields[name] = field->clone();
    }
    return cloned;
}

size_t LgsObject::getSizeBytes() {
    size_t sum = 0;
    for (const auto& [name, field] : fields) {
        sum += field->type->getSizeBytes();
    }
    return sum;
}

LgsObject::~LgsObject() {
    for (const auto interface : interfaces) {
        freeType(interface);
    }
}
