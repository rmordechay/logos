#include "object/LogosObject.h"

const string LogosObject::name() const {
    return typeName;
}

Type* LogosObject::getLLVMType(IRBuilder<>* builder, LogosStack* theStack) const {
    vector<Type*> elementTypes;
    for (const auto entry : fields) {
        auto fieldType = entry.second->inferredType->getLLVMType(builder, theStack);
        elementTypes.push_back(fieldType);
    }
    return StructType::create(builder->getContext(), elementTypes);
}

bool LogosObject::operator==(LogosType* other) const { return true;
    return true;
}

LogosObject::~LogosObject() {
    for (const auto field : fields) {
        delete field.second;
    }
    for (const auto func : funcs) {
        delete func.second;
    }
}
