#ifndef LOGOSVOID_H
#define LOGOSVOID_H

#include "CodeGenerator.h"
#include "LogosType.h"

class LogosVoid final : public LogosType {
public:
    Type* IRType = Type::getVoidTy(context);
    string typeName = "Void";

    const string name() const override;
    Type* getIRType() override;
    bool operator==(LogosType* other) const override;
    ~LogosVoid() override = default;
};

inline const string LogosVoid::name() const {
    return typeName;
}

inline Type* LogosVoid::getIRType() {
    return IRType;
}

inline bool LogosVoid::operator==(LogosType* other) const {
    return true;
}

inline LogosVoid LOGOS_VOID;

#endif //LOGOSVOID_H
