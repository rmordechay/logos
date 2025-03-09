#include "object/LogosObject.h"
#include "funcs/LogosFuncImpl.h"
#include "object/LogosField.h"
#include <ranges>

const string LogosObject::getName() const {
    return typeName;
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

bool LogosObject::equals(LogosType* other) const {
    return typeName == other->getName();
}

LogosObject::~LogosObject() {
    for (const auto& field : fields) {
        delete field.second;
    }
    for (const auto& func : methods) {
        delete func.second;
    }
}
