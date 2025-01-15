#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LogosType.h"

#include <string>


class LogosString final : public LogosType {
public:
    static constexpr auto name = "Str";

    LogosString();
    ~LogosString() override = default;

    Type* getLLVMType(IRBuilder<>& builder) const override {
        return nullptr;
    }
};

#endif //LOGOSSTRING_H
