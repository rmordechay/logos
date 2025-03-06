#include "object/LogosObject.h"
#include "funcs/LogosFuncImpl.h"
#include "object/LogosField.h"
#include <ranges>

const string LogosObject::name() const {
    return typeName;
}

Type* LogosObject::getIRType() {
    if (IRType) return IRType;
    vector<Type*> elementTypes;
    for (const auto& [_, val] : fields) {
        auto fieldType = val->inferredType->getIRType();
        elementTypes.push_back(fieldType);
    }
    IRType = StructType::create(context, elementTypes);
    return IRType;
}

LogosConstant* LogosObject::getConstant() {
    // TODO return empty constructor
    return nullptr;
}

bool LogosObject::operator==(LogosType* other) const { return true;
    return true;
}

LogosObject::~LogosObject() {
    for (const auto& field : fields) {
        delete field.second;
    }
    for (const auto& func : methods) {
        delete func.second;
    }
}
