#pragma once
#include "LgsType.h"

enum LgsJsonKind {
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_INT,
    JSON_FLOAT,
    JSON_STRING,
    JSON_NULL,
    JSON_UNKNOWN,
};

class LgsJsonType final : public LgsType {
public:
    static constexpr auto name = "Json";
    LgsJsonKind kind;

    explicit LgsJsonType(const LgsJsonKind kind = JSON_UNKNOWN) : kind(kind) {}
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    bool canCastTo(LgsType* other) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string getName() override;
};
