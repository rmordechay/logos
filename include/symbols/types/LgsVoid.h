#pragma once
#include "LgsType.h"

class LgsVoid final : public LgsType {
public:
    static constexpr auto name = "Void";

    std::string pname() override;
    json::object asJSON() override;
    llvm::Type* getIRType(LgsCodeGen* codeGen) override;
    size_t getSizeBytes() override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    bool equals(LgsType* other) override;
};

inline LgsVoid LGS_VOID;


