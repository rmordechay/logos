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
    if (IRType) return IRType;
    // Add one or zero if table exists
    const size_t offset = hasVirtuals();
    vector<Type*> elementTypes(fields.size() + offset);
    if (offset) {
        setVTable();
        elementTypes[0] = vtable->type->getIRType(codeGen);
    }
    for (const auto [fieldName, field] : fields) {
        field->position += offset;
        Type* fieldType;
        if (field->type->asObject()) {
            fieldType = codeGen->ptrTy();
        } else {
            fieldType = field->type->getIRType(codeGen);
        }
        elementTypes[field->position] = fieldType;
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

string LgsObject::strFormatPart() const {
    stringstream str;
    str << '{';
    for (const auto [fieldName, field] : fields) {
        str << fieldName << " = " << field->type->strFormatPart();
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

void LgsObject::setVTable() {
    vtable = new LgsHashMap(new LgsStr(), &LGS_ANY);
}

bool LgsObject::hasVirtuals() const {
    for (const auto method : methods) {
        if (method.second->funcType->isVirtual) {
            return true;
        }
    }
    return false;
}

void LgsObject::freeValue(LgsCodeGen* codeGen, Value* value) {
    codeGen->builder.CreateFree(value);
}

LgsObject* LgsObject::clone() {
    const auto cloned = new LgsObject(*this);
    cloned->fields.clear();
    for (const auto [fieldName, field] : fields) {
        cloned->fields[fieldName] = new LgsField(*field);
    }
    return cloned;
}

size_t LgsObject::getSizeBytes() {
    size_t sum = 0;
    for (const auto& [_, field] : fields) {
        if (name == field->type->getName()) {
            sum += sizeof(void*);
        } else {
            sum += field->type->getSizeBytes();
        }
    }
    return sum;
}

LgsObject::~LgsObject() {
    if (vtable) delete vtable;
    for (const auto interface : interfaces) {
        freeType(interface);
    }
}
