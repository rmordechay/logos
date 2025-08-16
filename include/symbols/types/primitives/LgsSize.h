#pragma once
#include "LgsType.h"

class LgsSize final : public LgsType {
public:
    static constexpr auto name = "Size";

    LgsSize() {
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
    ~LgsSize() override = default;
};

inline LgsSize LGS_SIZE;