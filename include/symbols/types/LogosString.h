#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "CodeGeneration.h"
#include "LogosType.h"

#include <string>


class LogosString final : public LogosType {
public:
    Type* llvmType = nullptr;
    static constexpr auto typeName = "Str";

    const string name() const override;
    Type* writeLLVMType(CodeGenMetadata* metadata) override;
    bool operator==(LogosType* other) const override;
    ~LogosString() override = default;
};

inline const string LogosString::name() const {
    return typeName;
}

inline Type* LogosString::writeLLVMType(CodeGenMetadata* metadata) {
    if (llvmType) return llvmType;
    return nullptr;
}

inline bool LogosString::operator==(LogosType* other) const { return true;
}

#endif //LOGOSSTRING_H
