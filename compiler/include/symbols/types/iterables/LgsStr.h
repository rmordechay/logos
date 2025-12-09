#pragma once
#include "LgsIterable.h"
#include "types/primitives/LgsChar.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";

    explicit LgsStr(const bool isHeap = false): LgsIterable(&LGS_CHAR) {
        passByRef = true;
        isHeapAlloc = isHeap;
    }
    Type* getIRType(LgsCgModule& cg) override;
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Constant* getRTType(LgsCgModule& cg) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
    std::string fmtStr() const override;
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsStr LGS_STR;