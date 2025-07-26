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

Type* LgsObject::getIRType(LgsModule* module) {
    if (IRType) return IRType;
    // Add one or zero if table exists
    const size_t offset = !!vtable;
    vector<Type*> elementTypes(fields.size() + offset);
    size_t position = 0;
    if (vtable) {
        elementTypes[position++] = vtable->type->getIRType(module);
    }
    for (const auto [_, field] : fields) {
        const auto fieldType = field->type->getIRType(module);
        elementTypes[field->position + offset] = fieldType;
        field->position = position++;
    }
    IRType = StructType::getTypeByName(module->context, name);
    if (!IRType) {
        IRType = StructType::create(module->context, elementTypes, name);
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
