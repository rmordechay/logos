#pragma once
#include "LgsType.h"

class LgsInt final : public LgsType {
public:
    static constexpr auto name = "Int";

    LgsInt() {
        isPrimitive = true;
        isNumber = true;
    }
    size_t getSizeBytes() override;
    llvm::Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    std::string pname() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    std::string strFormatPart() const override;
    ~LgsInt() override = default;
};

inline LgsInt LGS_INT;
