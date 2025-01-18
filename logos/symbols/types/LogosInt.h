#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "LogosType.h"

class LogosInt final : public LogosType {
public:
    static constexpr auto name = "Int";
    Type* getLLVMType(IRBuilder<>* builder) const override { return builder->getInt32Ty(); }
    ~LogosInt() override = default;
};

inline const LogosType& LOGOS_INT = LogosInt();

#endif //LOGOSINT_H
