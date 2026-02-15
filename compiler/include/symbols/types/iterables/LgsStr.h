#pragma once
#include "LgsIterable.h"
#include "types/primitives/LgsChar.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    size_t const length;

    explicit LgsStr(const size_t len = 0): LgsIterable(&LGS_CHAR), length(len) {
        isHeap = true;
        passByRef = true;
        rttKind = RTT_STR;
    }
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::optional<int64_t> getConstLength() override;
    void asIRText(LgsCodeGen& cg, LgsStrBuilder& strBuilder, Value* ptr) override;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    Value* loadRTData(LgsCodeGen& cg, Value* value);
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsStr LGS_STR;