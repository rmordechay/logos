#pragma once
#include "LgsType.h"

class LgsNullable final : public LgsType {
public:
    static constexpr auto name = "Nullable";
    LgsType* baseType;

    explicit LgsNullable(LgsType* baseType) : baseType(baseType) {
        if (baseType) passByRef = baseType->passByRef;
    }
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    bool canCastTo(LgsType* other) override;
    Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    std::string getName() override;
    std::string pname() override;
    void setNullableFields(LgsCgModule& cg, Value* ptr, Value* value, Value* isSet);
    Value* getNullableValue(LgsCgModule& cg, Value* ptr);
    Value* getIsSet(LgsCgModule& cg, Value* ptr);
    void setNullableValue(LgsCgModule& cg, Value* ptr, Value* value);
    void setIsSet(LgsCgModule& cg, Value* ptr, Value* value);
};
