#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LogosType.h"

#include <string>


class LogosString final : public LogosType {
public:
    static constexpr auto typeName = "Str";

    const string name() const override;
    Type* getLLVMType(IRBuilder<>* builder, LogosStack* theStack) const override;
    bool operator==(LogosType* other) const override;
    ~LogosString() override = default;
};

inline const string LogosString::name() const {
    return typeName;
}

inline Type* LogosString::getLLVMType(IRBuilder<>* builder, LogosStack* theStack) const {
    return nullptr;
}

inline bool LogosString::operator==(LogosType* other) const {
}

#endif //LOGOSSTRING_H
