#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LogosType.h"


class LogosFloat final : public LogosType {
public:
    static constexpr auto typeName = "Float";

    const string name() const override;
    Type* getLLVMType(IRBuilder<>* builder) const override;
    bool operator==(LogosType* other) const override;
    ~LogosFloat() override = default;
};

inline const string LogosFloat::name() const {
    return typeName;
}

inline Type* LogosFloat::getLLVMType(IRBuilder<>* builder) const {
    return builder->getFloatTy();
}

inline bool LogosFloat::operator==(LogosType* other) const {
}


#endif //LOGOSFLOAT_H
