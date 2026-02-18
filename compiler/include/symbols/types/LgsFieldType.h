#pragma once
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>

#include "LgsType.h"

class LgsFieldType final : public LgsType {
public:
    static constexpr std::string name = "Field";

    LgsFieldType() {
        rttKind = RTT_FIELD_TYPE;
    }
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Type* getIRType(LgsCodeGen& cg) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    static Value* loadRTName(LgsCodeGen& cg, Value* ptr);
    static Value* loadRTSize(LgsCodeGen& cg, Value* ptr);
    static Value* loadRTOffset(LgsCodeGen& cg, Value* ptr);
    static Value* loadRTKind(LgsCodeGen& cg, Value* ptr);
    static Value* loadRTType(LgsCodeGen& cg, Value* ptr);
    static StructType* getRTTStruct(LgsCodeGen& cg);
};
