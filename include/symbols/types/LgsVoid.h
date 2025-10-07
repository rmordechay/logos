#pragma once
#include "LgsType.h"

class LgsVoid final : public LgsType {
public:
    static constexpr auto name = "Void";

    LgsVoid() {
        isPrimitive = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t getSizeBytes() override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    Lgs_rttype getRTType() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
    void parseAsJSON(std::stringstream& json) override;
};

inline LgsVoid LGS_VOID;


