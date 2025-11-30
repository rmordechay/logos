#pragma once
#include "LgsIterable.h"
#include "types/primitives/LgsChar.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";

    explicit LgsStr(LgsExpr* size = nullptr): LgsIterable(&LGS_CHAR, size) {
        passByRef = true;
    }
    Type* getIRType(LgsCgModule& cg) override;
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Constant* getRTType(LgsCgModule& cg) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
    std::string strFormatPart() const override;
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* eqIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* neIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsStr LGS_STR;