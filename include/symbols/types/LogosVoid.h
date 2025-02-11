#ifndef LOGOSVOID_H
#define LOGOSVOID_H

#include "LogosType.h"

class LogosVoid final : public LogosType {
public:
    static constexpr auto typeName = "Void";

    const string name() const override;
    Type* getLLVMType(IRBuilder<>* builder, LogosStack* theStack) const override;
    bool operator==(LogosType* other) const override;
    ~LogosVoid() override = default;
};

inline const string LogosVoid::name() const {
    return typeName;
}

inline Type* LogosVoid::getLLVMType(IRBuilder<>* builder, LogosStack* theStack) const {
    return builder->getVoidTy();
}

inline bool LogosVoid::operator==(LogosType* other) const {
    return true;
}

inline LogosVoid LOGOS_VOID;

#endif //LOGOSVOID_H
