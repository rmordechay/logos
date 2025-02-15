#include "object/LogosObject.h"

const string LogosObject::name() const {
    return typeName;
}

Type* LogosObject::getLLVMType() {
    if (llvmType) return llvmType;
    vector<Type*> elementTypes;
    for (const auto entry : fields) {
        auto fieldType = entry.second->inferredType->getLLVMType();
        elementTypes.push_back(fieldType);
    }
    llvmType = StructType::create(context, elementTypes);
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
