#pragma once
#include "LgsType.h"

class LgsNullable final : public LgsType {
public:
    static constexpr auto name = "Nullable";
    LgsType* baseType;

    explicit LgsNullable(LgsType* baseType) : baseType(baseType) {}
    LgsField* getField(const std::string& fieldName) override;
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsCgModule& cg) override;
    void setIRValue(LgsCgModule& cg, Value* nullablePtr, Value* value);
    Constant* getRTType(LgsCgModule& cg) override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    std::string pname() override;
    Value* eqIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    size_t sizeBytes() override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
    ~LgsNullable() override;
};
