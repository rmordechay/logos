#pragma once
#include "LgsType.h"

class LgsVoid final : public LgsType {
public:
    static constexpr auto name = "Void";

    LgsVoid() {
        isPrimitive = true;
        rtt = RTT_VOID;
    }
    std::string pname() override;
    llvm::Type* getIRType(LgsLLVMGen& cg) override;
    size_t getSizeBytes() override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
    json::value asJSON() override;
};

inline LgsVoid LGS_VOID;


