#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "LogosValue.h"


class LogosInt final : public LogosValue {
public:
    int value;
    static constexpr auto name = "Int";

    explicit LogosInt(const int value): value(value) {}
    ~LogosInt() override = default;

    std::string getTypeName() const override;
    Type* getLLVMType(IRBuilder<>& builder) const override;
    Value* getLLVMValue(IRBuilder<>& builder) const override;
};


#endif //LOGOSINT_H
