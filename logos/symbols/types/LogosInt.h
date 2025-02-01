#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "LogosType.h"

class LogosInt final : public LogosType {
public:
    static constexpr auto typeName = "Int";

    const string& name() const override;
    Type* getLLVMType(IRBuilder<>* builder) const override;
    bool operator==(const LogosType* other) const override;
    ~LogosInt() override = default;
};

inline const string& LogosInt::name() const {
    return typeName;
}

inline Type* LogosInt::getLLVMType(IRBuilder<>* builder) const {
    return builder->getInt32Ty();
}

inline bool LogosInt::operator==(const LogosType* other) const {
}

inline const LogosType& LOGOS_INT = LogosInt();

#endif //LOGOSINT_H
