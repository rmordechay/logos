#pragma once
#include "LgsType.h"

class LgsDouble final : public LgsType {
public:
    static constexpr auto name = "Double";
    LgsDouble() {
        isPrimitive = true;
        isNumber = true;
    }
    std::string getName() override;
    std::string pname() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    llvm::Type* getIRType(LgsCodeGen* codeGen) override;
    bool equals(LgsType* other) override;
};
