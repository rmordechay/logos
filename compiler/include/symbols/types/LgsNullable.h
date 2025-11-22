#pragma once
#include "LgsType.h"

class LgsNullable final : public LgsType {
public:
    LgsType* baseType;

    explicit LgsNullable(LgsType* baseType) : baseType(baseType) {}
    LgsField* getField(const std::string& fieldName) override;
    LgsFunc* getMethod(const std::string& methodName) override;
    void setIRValue(LgsLLVMGen& cg, Value* nullablePtr, Value* value);
    Type* getIRType(LgsLLVMGen& cg) override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    size_t sizeBytes() override;
    std::string strFormatPart() const override;
    llvm::DIType* getDebugType(LgsLLVMGen& cg) override;
    LgsType* clone() override;
    ~LgsNullable() override;
};
