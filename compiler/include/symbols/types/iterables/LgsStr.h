#pragma once
#include "LgsIterable.h"
#include "types/primitives/LgsChar.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";

    explicit LgsStr(): LgsIterable(&LGS_CHAR) {}
    Type* getIRType(LgsCgModule& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCgModule& cg, Value* pointee = nullptr) override;
    Constant* getRTType(LgsCgModule& cg) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Value* addIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, Value* iterableExpr, Value* value) override;
    void moveValue(LgsCgModule& cg, Value* leftPtr, Value* rightPtr, Constant* type) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsStr LGS_STR;