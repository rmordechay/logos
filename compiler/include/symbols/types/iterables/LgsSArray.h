#pragma once
#include "LgsIterable.h"
#include "exprs/constants/LgsIntConst.h"

class LgsSArray final : public LgsIterable {
public:
    static constexpr auto name = "SArray";
    LgsExpr* length = nullptr;

    explicit LgsSArray(LgsType* baseType, LgsExpr* length): LgsIterable(baseType), length(length) {
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
    Value* inIR(LgsCgModule& cg, Value* iterableExpr, Value* value) override;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
    void addIRElement(LgsCgModule& cg, Value* iterable, Value* index, Value* value) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    bool canCastTo(LgsType* other) override;
    bool equals(LgsType* other) override;
    DIType* getDebugType(LgsCgModule& cg) override;
};
