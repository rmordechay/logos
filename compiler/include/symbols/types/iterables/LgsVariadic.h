#pragma once
#include "LgsIterable.h"
#include "LgsType.h"

class LgsVariadic final : public LgsIterable {
public:
    static constexpr auto name = "Variadic";

    explicit LgsVariadic(LgsType* baseType): LgsIterable(baseType) {}
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index) override;
};
