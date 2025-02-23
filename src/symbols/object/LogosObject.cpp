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
    for (const auto& val : fields | views::values) {
        auto fieldType = val->inferredType->getIRType();
        elementTypes.push_back(fieldType);
    }
    IRType = StructType::create(context, elementTypes);
    return IRType;
}

bool LogosObject::operator==(LogosType* other) const { return true;
    return true;
}

LogosObject::~LogosObject() {
    for (const auto& field : fields) {
        delete field.second;
    }
    for (const auto& func : funcs) {
        delete func.second;
    }
}
