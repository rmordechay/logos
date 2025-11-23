#pragma once
#include "LgsType.h"

class LgsULong final : public LgsType {
public:
    static constexpr auto name = "ULong";

    LgsULong() {
        isPrimitive = true;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
    llvm::DIType* getDebugType(LgsLLVMGen& cg) override;
    LgsType* clone() override;
};

inline LgsULong LGS_ULONG;