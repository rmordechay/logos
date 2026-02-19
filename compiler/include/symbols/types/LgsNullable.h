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
    std::string pname() override;
    std::string getName() override;
    std::string fmtStr() const override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTTypeExtra(LgsCodeGen& cg) override;
    void asIRText(LgsStrBuilder& sb, Value* ptr) override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee) override;
    Value* moveValue(LgsCodeGen& cg, Value* value, Value* toLevel) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    void setIRFields(LgsCodeGen& cg, Value* ptr, Value* value, Value* isSet);
    Value* applyPtrBinOp(LgsCodeGen& cg, LgsBinaryExpr* binExpr, const std::function<Value*(LgsBinaryExpr*)>& func);
    Value* applyNumberBinOp(LgsCodeGen& cg, LgsBinaryExpr* binExpr, const std::function<Value*(LgsBinaryExpr*)>& func);
    DIType* getDebugType(LgsCodeGen& cg) override;
    static Value* loadValue(LgsCodeGen& cg, Value* ptr);
    static Value* loadIsSet(LgsCodeGen& cg, Value* ptr);
};
