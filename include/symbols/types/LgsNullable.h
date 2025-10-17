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
    Lgs_rttype getRTType() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    size_t getSizeBytes() override;
    std::string strFormatPart() const override;
    Value* isSetIR(LgsLLVMGen& cg, Value* ptr);
    Value* getValue(LgsLLVMGen& cg, Value* ptr);
    ~LgsNullable() override;
};

inline LgsNullable LGS_ANY_NULLABLE(&LGS_ANY);