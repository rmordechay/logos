#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "LogosType.h"


class LogosInt final : public LogosType {
public:
    static constexpr auto name = "Int";

    LogosInt() = default;
    ~LogosInt() override = default;

    Type* getLLVMType(IRBuilder<>& builder) const override {
        return builder.getInt32Ty();
    }

};

#endif //LOGOSINT_H
