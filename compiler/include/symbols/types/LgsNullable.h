#pragma once
#include <functional>
#include "LgsType.h"

class LgsNullable final : public LgsType {
public:
    static constexpr auto name = "Nullable";
    LgsType* baseType = nullptr;
    bool isNull = false;

    explicit LgsNullable(LgsType* baseType = nullptr) : baseType(baseType) {
        rttKind = RTT_NULLABLE;
        if (baseType) {
            isHeap = baseType->isHeap;
            passByRef = baseType->passByRef;
        } else {
            isNull = true;
        }
    }
    LgsField* getField(const std::string& fieldName) override;
    LgsFunc* getMethod(const std::string& methodName) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee) override;
    std::string pname() override;
    std::string getName() override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTTypeExtra(LgsCodeGen& cg) override;
    bool canCastTo(LgsType* other) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    void setIRFields(LgsCodeGen& cg, Value* ptr, Value* value, Value* isSet);
    Value* loadIsSet(LgsCodeGen& cg, Value* ptr);
    Value* loadValue(LgsCodeGen& cg, Value* ptr);
    Value* applyNumberBinOp(LgsCodeGen& cg, LgsBinaryExpr* binExpr, const std::function<Value*(LgsBinaryExpr*)>& func);
    Value* applyPtrBinOp(LgsCodeGen& cg, LgsBinaryExpr* binExpr, const std::function<Value*(LgsBinaryExpr*)>& func);
};
