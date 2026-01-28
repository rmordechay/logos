#pragma once
#include "LgsIterable.h"
#include "LgsRTTIndices.h"
#include "types/primitives/LgsChar.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    inline static Lgs_StrIndices rttIndices;

    explicit LgsStr(): LgsIterable(&LGS_CHAR) {
        passByRef = true;
        rttKind = RTT_STR;
    }
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Constant* getRTType(LgsCodeGen& cg) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    std::string fmtStr() const override;
    Value* asIRStr(LgsCodeGen& cg, Value* v) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsStr LGS_STR;