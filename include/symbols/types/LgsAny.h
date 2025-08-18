#pragma once
#include "LgsType.h"

class LgsAny final : public LgsType {
public:
    static constexpr auto name = "Any";

    LgsAny() {
        isPrimitive = true;
    }
    size_t getSizeBytes() override;
    llvm::Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string pname() override;
    json::object asJSON() override;
    std::string strFormatPart() const override;
    bool equals(LgsType* other) override;
    ~LgsAny() override = default;
};

inline LgsAny LGS_ANY;


