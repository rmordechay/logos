#include "types/LgsObject.h"
#include "funcs/LgsFuncImpl.h"
#include "stmts/LgsField.h"

LgsObject::LgsObject(const LgsObject& other) : name(other.name) {
    for (const auto& [name, field] : other.fields) {
        fields[name] = new LgsField(*field);
    }
    methods = other.methods;
}

const string LgsObject::getName() const {
    return name;
}

Type* LgsObject::getIRType() {
    if (IRType) return IRType;
    vector<Type*> elementTypes;
    for (const auto& [_, val] : fields) {
        auto fieldType = val->type->getIRType();
        elementTypes.push_back(fieldType);
    }
    IRType = StructType::create(elementTypes, getName());
    return IRType;
}

LgsConstant* LgsObject::getZeroValue() {
    // TODO return empty constructor
    return nullptr;
}

bool LgsObject::equals(LgsType* other) const {
    return name == other->getName();
}

LgsObject::~LgsObject() {
    for (const auto& field : fields) {
        delete field.second;
    }
    for (const auto& func : methods) {
        delete func.second;
    }
}
