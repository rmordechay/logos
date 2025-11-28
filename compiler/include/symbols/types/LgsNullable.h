#pragma once
#include "LgsType.h"

class LgsNullable final : public LgsType {
public:
    LgsType* baseType;

    explicit LgsNullable(LgsType* baseType) : baseType(baseType) {}
    LgsField* getField(const std::string& fieldName) override;
    LgsFunc* getMethod(const std::string& methodName) override;
    void setIRValue(LgsCgModule& cg, Value* nullablePtr, Value* value);
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    size_t sizeBytes() override;
    std::string strFormatPart() const override;
    llvm::DIType* getDebugType(LgsCgModule& cg) override;
    LgsType* clone() override;
    ~LgsNullable() override;
};
