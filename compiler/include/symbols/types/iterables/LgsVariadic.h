#pragma once
#include "LgsIterable.h"
#include "LgsType.h"

class LgsVariadic final : public LgsIterable {
public:

    explicit LgsVariadic(LgsType* baseType): LgsIterable(baseType) {}
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    llvm::DIType* getDebugType(LgsCgModule& cg) override;
    std::string getName() override;
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
};
