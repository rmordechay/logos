#pragma once
#include "LgsType.h"
#include <string>

class LgsEnum : public LgsType {
public:
    std::string name;
    LgsType* subtype = nullptr;

    explicit LgsEnum(const std::string& name) : name(name) {
        rtt = RTT_ENUM;
    }
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    Value* asIRStr(LgsCodeGen& cg, Value* v) override;
    size_t sizeBytes() override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    ~LgsEnum() override;
};

