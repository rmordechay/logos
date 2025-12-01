#pragma once
#include "LgsType.h"

class LgsInterface final : public LgsType {
public:
    std::string name;

    explicit LgsInterface(const std::string& name) : name(name) {}
    LgsFunc* getMethod(const std::string& methodName) override;
    std::string getName() override;
    Type* getIRType(LgsCgModule& cg) override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    size_t sizeBytes() override;
    DIType* getDebugType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string fmtStr() const override;
};
