#pragma once
#include "LgsType.h"
#include <string>

#include "stmts/LgsField.h"

class LgsEnum : public LgsType {
public:
    std::string name;
    LgsType* exprType = nullptr;

    explicit LgsEnum(const std::string& name) : name(name) {
        rttKind = RTT_ENUM;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    size_t sizeBytes() override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    ~LgsEnum() override;
};

class LgsEnumField final : public LgsEnum {
public:
    size_t index;
    std::string fieldName;

    LgsEnumField(const std::string& enumName, const std::string& fieldName, const size_t index): LgsEnum(enumName), index(index), fieldName(fieldName) {}
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
};
