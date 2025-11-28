#pragma once
#include <utility>
#include "LgsType.h"

class LgsUnknown final : public LgsType {
public:
    std::string name;

    explicit LgsUnknown(std::string name) : name(std::move(name)) {}
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string getName() override;
    std::string pname() override;
    LgsExpr* getZeroValue() override;
    size_t sizeBytes() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    llvm::DIType* getDebugType(LgsCgModule& cg) override;
};
