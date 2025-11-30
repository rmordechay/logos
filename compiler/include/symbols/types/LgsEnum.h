#pragma once
#include "LgsType.h"
#include <string>

namespace llvm {
    class DIType;
    class Constant;
    class Type;
}

class LgsEnum final : public LgsType {
public:
    std::string name;

    explicit LgsEnum(const std::string& enumName) : name(enumName) {}
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    size_t sizeBytes() override;
    DIType* getDebugType(LgsCgModule& cg) override;
};


