#include "object/LogosObject.h"
#include "funcs/LogosFuncImpl.h"
#include "object/LogosField.h"
#include <ranges>

const string LogosObject::getName() const {
    return name;
}

Type* LogosObject::getIRType() {
    if (IRType) return IRType;
    vector<Type*> elementTypes;
    for (const auto& [_, val] : fields) {
        auto fieldType = val->type->getIRType();
        elementTypes.push_back(fieldType);
    }
    IRType = StructType::create(context, elementTypes, getName());
    return IRType;
}

LogosConstant* LogosObject::getZeroValue() {
    // TODO return empty constructor
    return nullptr;
}

bool LogosObject::containsField(const string& name) const {
    return fields.find(name) != fields.end();
}

bool LogosObject::containsMethod(const string& name) const {
    return methods.find(name) != methods.end();
}

LogosField* LogosObject::getField(const string& name) const {
    const auto it = fields.find(name);
    if (it != fields.end()) {
        return it->second;
    }
    return nullptr;
}

LogosMethodImpl* LogosObject::getMethod(const string& name) const {
    const auto it = methods.find(name);
    if (it != methods.end()) {
        return it->second;
    }
    return nullptr;
}

bool LogosObject::equals(LogosType* other) const {
    return name == other->getName();
}

LogosObject::~LogosObject() {
    for (const auto& field : fields) {
        delete field.second;
    }
    for (const auto& func : methods) {
        delete func.second;
    }
}
