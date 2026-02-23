#pragma once
#include <string>

#include "LgsIterable.h"
#include "LgsType.h"
#include "Lgs_Types.h"

class LgsType;

class LgsVariadic final : public LgsIterable {
public:
    static constexpr auto name = "Variadic";

    explicit LgsVariadic(LgsType* baseType): LgsIterable(baseType) {
        rttKind = RTT_VARIADIC;
    }
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Type* getIRType(LgsCodeGen& cg) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) override;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
};
