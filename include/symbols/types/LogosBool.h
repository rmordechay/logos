#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "CodeGeneration.h"
#include "LogosType.h"


class LogosBool final : public LogosType {
public:
    static constexpr auto typeName = "Bool";
    static constexpr auto trueLiteral = "true";

    const string name() const override;
    Type* writeLLVMType(CodeGenMetadata* metadata) override;
    bool operator==(LogosType* other) const override;
    ~LogosBool() override = default;
};

inline const string LogosBool::name() const {
    return typeName;
}

inline Type* LogosBool::writeLLVMType(CodeGenMetadata* metadata) {
    if (llvmType) return llvmType;
    llvmType = metadata->builder->getInt1Ty();
    return llvmType;
}

inline bool LogosBool::operator==(LogosType* other) const { return true;
    return true;
}

#endif //LOGOSBOOL_H
