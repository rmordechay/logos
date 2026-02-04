#pragma once
#include "LgsIterable.h"
#include "exprs/constants/LgsIntConst.h"

class LgsSArray final : public LgsIterable {
public:
    static constexpr auto name = "SArr";
    LgsExpr* lengthExpr = nullptr;
    size_t len = 0;

    explicit LgsSArray(LgsType* baseType, LgsExpr* length): LgsIterable(baseType), lengthExpr(length) {
        isStatic = true;
        passByRef = true;
        rttKind = RTT_SARRAY;
        len = length->getConstInt().value();
    }
    explicit LgsSArray(LgsType* baseType, const size_t length): LgsSArray(baseType, new LgsIntConst(&LGS_SIZE, length)) {
        len = length;
    }
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    std::string fmtStr() const override;
    bool canCastTo(LgsType* other) override;
    bool equals(LgsType* other) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee) override;
    Type* getIRType(LgsCodeGen& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Constant* getRTTypeExtra(LgsCodeGen& cg) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* inIR(LgsCodeGen& cg, Value* iterable, Value* value) override;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    void addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) override;
    Function* generateEqFunc(LgsCodeGen& cg);
    DIType* getDebugType(LgsCodeGen& cg) override;
};
