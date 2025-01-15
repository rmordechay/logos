#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LogosType.h"


class LogosFloat final : public LogosType {
public:
    static constexpr auto name = "Float";

    LogosFloat() = default;
    ~LogosFloat() override = default;

    Type* getLLVMType(IRBuilder<>& builder) const override {
        return builder.getFloatTy();
    }
};


#endif //LOGOSFLOAT_H
