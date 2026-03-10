#pragma once
#include <string>

#include "LgsType.h"

class LgsCPtr final : public LgsType {
public:
    static constexpr auto name = "CPtr";
    LgsType* baseType;

    explicit LgsCPtr(LgsType* baseType) : baseType(baseType) {
        isExternal = true;
    }
    std::string getName() override;
    std::string pname() override;
    Type* getIRType(LgsCodeGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    ~LgsCPtr() override;
};
