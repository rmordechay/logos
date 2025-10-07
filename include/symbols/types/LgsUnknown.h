#pragma once
#include <utility>
#include "LgsType.h"
#include "data/LgsDefinitions.h"

class LgsUnknown final : public LgsType {
public:
    std::string name;

    explicit LgsUnknown(std::string name = LGS_UNKNOWN_TYPE) : name(std::move(name)) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    Lgs_rttype getRTType() override;
    size_t getSizeBytes() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    void parseAsJSON(std::stringstream& json) override;
};
