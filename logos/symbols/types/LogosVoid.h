#ifndef LOGOSVOID_H
#define LOGOSVOID_H

#include "LogosType.h"

class LogosVoid final : public LogosType {
public:
    static constexpr auto typeName = "Void";

    const string& name() const override;
    Type* getLLVMType(IRBuilder<>* builder) const override;
    bool operator==(const LogosType* other) const override;
    ~LogosVoid() override = default;
};

inline const string& LogosVoid::name() const {
    return typeName;
}

inline Type* LogosVoid::getLLVMType(IRBuilder<>* builder) const {
    return builder->getVoidTy();
}

inline bool LogosVoid::operator==(const LogosType* other) const {
}

inline const LogosType& LOGOS_VOID = LogosVoid();

#endif //LOGOSVOID_H
