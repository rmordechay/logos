#pragma once
#include "LgsType.h"

class LgsDouble final : public LgsType {
public:
    static constexpr auto name = "Double";
    LgsDouble() {
        isPrimitive = true;
        isFloat = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
    LgsExpr* powConst(LgsExpr* self, LgsExpr* other) override;
    Value* powIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
};

inline LgsDouble LGS_DOUBLE;