#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LogosValue.h"

#include <string>


class LogosString final : public LogosValue {
public:
    std::string value;
    static constexpr auto name = "Str";

    explicit LogosString(const std::string &value): value(value) {}
    ~LogosString() override = default;

    std::string getTypeName() const override;
    Type* getLLVMType(IRBuilder<>& builder) const override;
    Value* getLLVMValue(IRBuilder<>& builder) const override;
};



#endif //LOGOSSTRING_H
