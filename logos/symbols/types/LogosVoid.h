#ifndef LOGOSVOID_H
#define LOGOSVOID_H

#include "LogosType.h"

class LogosVoid final : public LogosType {
public:
    static constexpr auto name = "Void";
    LogosVoid() = default;
    Type* getLLVMType(IRBuilder<>* builder) const override {
        return builder->getVoidTy();
    }
    ~LogosVoid() override = default;
};

inline const LogosType& LOGOS_VOID = LogosVoid();

#endif //LOGOSVOID_H
