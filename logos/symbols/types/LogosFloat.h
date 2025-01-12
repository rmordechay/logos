#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LogosValue.h"


class LogosFloat final : public LogosValue {
public:
    float value;
    static constexpr auto name = "Float";

    explicit LogosFloat(const float value): value(value) {}
    ~LogosFloat() override = default;

    std::string getTypeName() const override;
    Type* getLLVMType(IRBuilder<>& builder) const override;
    Value* getLLVMValue(IRBuilder<>& builder) const override;
};


#endif //LOGOSFLOAT_H
