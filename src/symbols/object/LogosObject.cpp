#include "object/LogosObject.h"

const string LogosObject::name() const {
    return typeName;
}

Type* LogosObject::getLLVMType(CodeGenMetadata* metadata) {
    vector<Type*> elementTypes;
    for (const auto entry : fields) {
        auto fieldType = entry.second->inferredType->getLLVMType(metadata);
        elementTypes.push_back(fieldType);
    }
    llvmStruct = StructType::create(metadata->builder->getContext(), elementTypes);
    return llvmStruct;
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
