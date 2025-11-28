#pragma once
#include "LgsType.h"

class LgsChar final : public LgsType {
public:
    static constexpr auto name = "Char";

    LgsChar() {
        isPrimitive = true;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
    llvm::DIType* getDebugType(LgsCgModule& cg) override;
    LgsType* clone() override;
};

inline LgsChar LGS_CHAR;


