#pragma once
#include "LgsType.h"

class LgsFloat final : public LgsType {
public:
    static constexpr auto name = "Float";

    LgsFloat() {
        isPrimitive = true;
        isNumber = true;
    }
    llvm::Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    size_t getSizeBytes() override;
    std::string strFormatPart() const override;
    bool equals(LgsType* other) override;
    std::string pname() override;
    json::object asJSON() override;
};

inline LgsFloat LGS_FLOAT;
