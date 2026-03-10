#pragma once
#include <utility>
#include <string>

#include "LgsType.h"

class LgsUnknown final : public LgsType {
public:
    std::string name;

    explicit LgsUnknown(std::string name) : name(std::move(name)) {}
    Type* getIRType(LgsCodeGen& cg) override;
    LgsType* clone() override;
    std::string getName() override;
    std::string pname() override;
    LgsExpr* getZeroValue() override;
    size_t sizeBytes() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};
