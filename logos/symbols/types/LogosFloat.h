#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LogosType.h"


class LogosFloat final : public LogosType {
public:
    static constexpr auto name = "Float";
    Type* getLLVMType(IRBuilder<>* builder) const override {
        return builder->getFloatTy();
    }
    ~LogosFloat() override = default;
};


#endif //LOGOSFLOAT_H
