#include "object/LogosObject.h"

const string LogosObject::name() const {
    return typeName;
}

Type* LogosObject::writeLLVMType(CodeGenMetadata* metadata) {
    if (llvmType) return llvmType;
    vector<Type*> elementTypes;
    for (const auto entry : fields) {
        auto fieldType = entry.second->inferredType->writeLLVMType(metadata);
        elementTypes.push_back(fieldType);
    }
    llvmType = StructType::create(metadata->builder->getContext(), elementTypes);
    return llvmType;
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
