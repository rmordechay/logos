#pragma once
#include "LgsIterable.h"
#include "exprs/constants/LgsIntConst.h"

class LgsSArray final : public LgsIterable {
public:
    static constexpr auto name = "SArray";
    LgsExpr* lengthExpr = nullptr;
    size_t len = 0;

    explicit LgsSArray(LgsType* baseType, LgsExpr* length): LgsIterable(baseType), lengthExpr(length) {
        isStatic = true;
        passByRef = true;
        rttKind = RTT_SARRAY;
    }
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Constant* getRTType(LgsCodeGen& cg) override;
    std::string fmtStr() const override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) override;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    void addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    bool canCastTo(LgsType* other) override;
    bool equals(LgsType* other) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};
