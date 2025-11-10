#pragma once
#include "LgsType.h"

class LgsAny final : public LgsType {
public:
    static constexpr auto name = "Any";

    LgsAny() {
        isPrimitive = true;
    }
    size_t getSizeBytes() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string getName() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
};

inline LgsAny LGS_ANY;


