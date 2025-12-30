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
    Type* getIRType(LgsCgModule& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCgModule& cg, Value* pointee = nullptr) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string fmtStr() const override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index) override;
    void addIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index, LgsExpr* value) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    bool canCastTo(LgsType* other) override;
    bool equals(LgsType* other) override;
    DIType* getDebugType(LgsCgModule& cg) override;
};
