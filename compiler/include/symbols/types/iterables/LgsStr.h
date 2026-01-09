#pragma once
#include "LgsIterable.h"
#include "types/primitives/LgsChar.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";

    explicit LgsStr(): LgsIterable(&LGS_CHAR) {
        passByRef = true;
    }
    Type* getIRType(LgsCgModule& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCgModule& cg, Value* pointee = nullptr, bool levelAbove = false) override;
    Constant* getRTType(LgsCgModule& cg) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* getIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index) override;
    std::string fmtStr() const override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsStr LGS_STR;