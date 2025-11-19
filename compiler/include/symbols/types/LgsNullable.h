#pragma once
#include "LgsType.h"
#include "types/LgsAny.h"

class LgsNullable final : public LgsType {
public:
    LgsType* baseType;

    explicit LgsNullable(LgsType* baseType) : baseType(baseType) {}
    LgsField* getField(const std::string& fieldName) override;
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsLLVMGen& cg) override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    size_t sizeBytes() override;
    std::string strFormatPart() const override;
    LgsType* clone() override;
    ~LgsNullable() override;
};
