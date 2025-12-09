#pragma once
#include "LgsIterable.h"
#include "exprs/constants/LgsIntConst.h"

class LgsSArray final : public LgsIterable {
public:
    static constexpr auto name = "SArray";

    explicit LgsSArray(LgsType* baseType, LgsExpr* size): LgsIterable(baseType, size) {
        isStatic = true;
        passByRef = true;
    }
    explicit LgsSArray(LgsType* baseType, const size_t size): LgsSArray(baseType, new LgsIntConst(size)) {}
    Type* getIRType(LgsCgModule& cg) override;
    std::string getName() override;
    std::string pname() override;
    std::string getGenericName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string fmtStr() const override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCgModule& cg) override;
};
