#pragma once
#include "LgsType.h"

#include <llvm/IR/Instructions.h>

class LgsNullable final : public LgsType {
public:
    static constexpr auto name = "Null";
    LgsType* baseType = nullptr;
    bool isNull = false;

    explicit LgsNullable(LgsType* baseType) : baseType(baseType) {
        passByRef = baseType->passByRef;
        isHeapAlloc = baseType->isHeapAlloc;
    }
    explicit LgsNullable() {
        isNull = true;
        passByRef = true;
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
    Value* addIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    void setNullableFields(LgsCgModule& cg, Value* ptr, Value* value, Value* isSet);
    Value* getNullableValue(LgsCgModule& cg, Value* ptr);
    Value* getIsSet(LgsCgModule& cg, Value* ptr);
    void storeNullableValue(LgsCgModule& cg, Value* ptr, Value* value);
    void storeIsSet(LgsCgModule& cg, Value* ptr, Value* value);
    Value* applyNumberBinOp(LgsCgModule& cg, LgsBinaryExpr* binExpr, const std::function<Value*(LgsBinaryExpr*)>& func);
    Value* applyPtrBinOp(LgsCgModule& cg, LgsBinaryExpr* binExpr, const std::function<Value*(LgsBinaryExpr*)>& func);
};

inline LgsNullable LGS_NULLABLE;