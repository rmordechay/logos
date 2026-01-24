#pragma once
#include "LgsType.h"

#include <llvm/IR/Instructions.h>

class LgsNullable final : public LgsType {
public:
    static constexpr auto name = "Null";
    LgsType* baseType = nullptr;
    bool isNull = false;
    const size_t valueIndex = 0;
    const size_t isSetIndex = 1;

    explicit LgsNullable(LgsType* baseType = nullptr) : baseType(baseType) {
        rtt = RTT_NULLABLE;
        if (baseType) {
            isHeapAlloc = baseType->isHeapAlloc;
            passByRef = baseType->passByRef;
        } else {
            isNull = true;
            passByRef = true;
        }
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
    void setIRFields(LgsCodeGen& cg, Value* ptr, Value* value, Value* isSet);
    Value* getNullableValue(LgsCodeGen& cg, Value* ptr);
    Value* getIsSet(LgsCodeGen& cg, Value* ptr);
    Value* applyNumberBinOp(LgsCodeGen& cg, LgsBinaryExpr* binExpr, const std::function<Value*(LgsBinaryExpr*)>& func);
    Value* applyPtrBinOp(LgsCodeGen& cg, LgsBinaryExpr* binExpr, const std::function<Value*(LgsBinaryExpr*)>& func);
};

inline LgsNullable LGS_NULLABLE;