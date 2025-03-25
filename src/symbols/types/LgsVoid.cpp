#include "types/LgsVoid.h"

inline const std::string LgsVoid::getName() const {
    return name;
}

inline Type* LgsVoid::getIRType() {
    return Type::getVoidTy(context);
}

inline LgsConst* LgsVoid::getZeroValue() {
    return nullptr;
}

LgsType* LgsVoid::inferBinaryType(LgsType* other) {
    return this;
}

inline bool LgsVoid::equals(LgsType* other) const {
    return name == other->getName();
}