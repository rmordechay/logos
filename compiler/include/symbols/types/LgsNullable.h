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
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    bool canCastTo(LgsType* other) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    void setNullableFields(LgsCodeGen& cg, Value* ptr, Value* value, Value* isSet);
    Value* getNullableValue(LgsCodeGen& cg, Value* ptr);
    Value* getIsSet(LgsCodeGen& cg, Value* ptr);
    void storeNullableValue(LgsCodeGen& cg, Value* ptr, Value* value);
    void storeIsSet(LgsCodeGen& cg, Value* ptr, Value* value);
    Value* applyNumberBinOp(LgsCodeGen& cg, LgsBinaryExpr* binExpr, const std::function<Value*(LgsBinaryExpr*)>& func);
    Value* applyPtrBinOp(LgsCodeGen& cg, LgsBinaryExpr* binExpr, const std::function<Value*(LgsBinaryExpr*)>& func);
};

inline LgsNullable LGS_NULLABLE;