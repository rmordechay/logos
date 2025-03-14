#include "types/LgsVoid.h"

inline const std::string LgsVoid::getName() const {
    return name;
}

inline Type* LgsVoid::getIRType() {
    return IRType;
}

inline LgsConst* LgsVoid::getZeroValue() {
    return nullptr;
}

LgsType* LgsVoid::inferBinaryType(LgsType* other) const {
    return other;
}

inline bool LgsVoid::equals(LgsType* other) const {
    return name == other->getName();
}