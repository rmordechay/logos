#include "types/LogosVoid.h"

inline const std::string LogosVoid::getName() const {
    return typeName;
}

inline llvm::Type* LogosVoid::getIRType() {
    return IRType;
}

inline LogosConstant* LogosVoid::getZeroValue() {
    return nullptr;
}

inline bool LogosVoid::equals(LogosType* other) const {
    return typeName == other->getName();
}