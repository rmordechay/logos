#ifndef LOGOSVOID_H
#define LOGOSVOID_H

#include "LogosType.h"

class LogosVoid final : public LogosType {
public:
    Type* IRType = Type::getVoidTy(context);
    string typeName = "Void";

    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    bool equals(LogosType* other) const override;
    ~LogosVoid() override = default;
};

inline const string LogosVoid::getName() const {
    return typeName;
}

inline Type* LogosVoid::getIRType() {
    return IRType;
}

inline LogosConstant* LogosVoid::getZeroValue() {
    return nullptr;
}

inline bool LogosVoid::equals(LogosType* other) const {
    return typeName == other->getName();
}

inline LogosVoid LOGOS_VOID;

#endif //LOGOSVOID_H
