#include "types/LgsVoid.h"

inline const std::string LgsVoid::getName() const {
    return typeName;
}

inline llvm::Type* LgsVoid::getIRType() {
    return IRType;
}

inline LgsConstant* LgsVoid::getZeroValue() {
    return nullptr;
}

inline bool LgsVoid::equals(LgsType* other) const {
    return typeName == other->getName();
}