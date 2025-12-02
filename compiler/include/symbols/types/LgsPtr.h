#pragma once
#include "LgsType.h"

class LgsPtr final : public LgsType {
public:
    static constexpr auto name = "Ptr";
    LgsType* baseType;

    explicit LgsPtr(LgsType* baseType) : baseType(baseType) {}
    std::string getName() override;
    std::string pname() override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
    ~LgsPtr() override;
};
