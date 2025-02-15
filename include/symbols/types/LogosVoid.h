#ifndef LOGOSVOID_H
#define LOGOSVOID_H

#include "CodeGenerator.h"
#include "LogosType.h"

class LogosVoid final : public LogosType {
public:
    Type* llvmType = Type::getVoidTy(context);
    static constexpr auto typeName = "Void";

    const string name() const override;
    Type* writeLLVMType(CodeGenMetadata* metadata) override;
    bool operator==(LogosType* other) const override;
    ~LogosVoid() override = default;
};

inline const string LogosVoid::name() const {
    return typeName;
}

inline Type* LogosVoid::writeLLVMType(CodeGenMetadata* metadata) {
    return llvmType;
}

inline bool LogosVoid::operator==(LogosType* other) const {
    return true;
}

inline LogosVoid LOGOS_VOID;

#endif //LOGOSVOID_H
