#pragma once
#include "LgsType.h"

class LgsNullable final : public LgsType {
public:
    LgsType* baseType;

    explicit LgsNullable(LgsType* baseType) : baseType(baseType) {}
    LgsField* getField(const std::string& fieldName) override;
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsLLVMGen& cg) override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    std::string getName() override;
    std::string pname() override;
    json::value asJsonStr() override;
    bool canCastTo(LgsType* other) override;
    size_t getSizeBytes() override;
    std::string strFormatPart() const override;
    Value* isNullIR(LgsLLVMGen& cg, Value* ptr);
    ~LgsNullable() override;
};
