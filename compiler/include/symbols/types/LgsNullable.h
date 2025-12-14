#pragma once
#include "LgsType.h"

#include <llvm/IR/Instructions.h>

class LgsNullable final : public LgsType {
public:
    static constexpr auto name = "Null";
    LgsType* baseType;

    explicit LgsNullable(LgsType* baseType = nullptr) : baseType(baseType) {
        if (baseType) passByRef = baseType->passByRef;
        else passByRef = true;
    }

    LgsField* getField(const std::string& fieldName) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string pname() override;
    std::string getName() override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    bool canCastTo(LgsType* other) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    void setNullableFields(LgsCgModule& cg, Value* ptr, Value* value, Value* isSet);
    Value* getNullableValue(LgsCgModule& cg, Value* ptr);
    Value* getIsSet(LgsCgModule& cg, Value* ptr);
    void setNullableValue(LgsCgModule& cg, Value* ptr, Value* value);
    void setIsSet(LgsCgModule& cg, Value* ptr, Value* value);
    Value* applyNumberBinOp(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right, const std::function<Value*(LgsExpr*, LgsExpr*)>& func);
    Value* applyPtrBinOp(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right, const std::function<Value*(LgsExpr*, LgsExpr*)>& func);
};

inline LgsNullable LGS_NULLABLE;