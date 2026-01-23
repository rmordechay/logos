#pragma once
#include "LgsType.h"
#include <string>

class LgsEnumField : public LgsType {
public:
    std::string name;
    LgsEnum* parentType;

    LgsEnumField(LgsEnum* parentType, const std::string& name) : name(name), parentType(parentType) {
        rtt = RTT_ENUM;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    std::string fmtStr() const override;
    Value* asIRStr(LgsCodeGen& cg, Value* v) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    ~LgsEnumField() override;
};
