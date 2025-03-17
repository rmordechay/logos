#include "types/LgsObject.h"
#include "funcs/LgsFuncImpl.h"
#include "stmts/LgsField.h"

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
    IRType = StructType::create(context, elementTypes, name);
    return IRType;
}

LgsConst* LgsObject::getZeroValue() {
    // TODO return empty constructor
    return nullptr;
}

LgsType* LgsObject::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsObject::equals(LgsType* other) const {
    return name == other->getName();
}
