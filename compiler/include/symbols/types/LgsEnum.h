#pragma once
#include "LgsType.h"
#include <string>

class LgsEnum : public LgsType {
public:
    std::string name;
    std::string fieldName;
    size_t fieldIndex;
    LgsType* subtype = nullptr;

    explicit LgsEnum(const std::string& name) : LgsEnum(name, "", 0) {}
    LgsEnum(const std::string& name, const std::string& fieldName, const size_t fieldIndex) : name(name), fieldName(fieldName), fieldIndex(fieldIndex) {
        rttKind = RTT_ENUM;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    Value* asIRStr(LgsCodeGen& cg, Value* v) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    size_t sizeBytes() override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    ~LgsEnum() override;
};

