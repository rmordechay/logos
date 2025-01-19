#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LogosType.h"

#include <string>


class LogosString final : public LogosType {
public:
    static constexpr auto name = "Str";
    Type* getLLVMType(IRBuilder<>* builder) const override {
        return nullptr;
    }
    ~LogosString() override = default;
};

#endif //LOGOSSTRING_H
