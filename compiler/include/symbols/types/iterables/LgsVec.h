#pragma once
#include "exprs/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"

class LgsVec final : public LgsIterable {
public:
    static constexpr auto name = "Vec";
    size_t dimVec = 0;

    explicit LgsVec(const size_t dim, LgsType* baseType = &LGS_FLOAT) : LgsIterable(baseType), dimVec(dim) {
        assert(dim > 1 && dim <= 4);
        size = new LgsIntConst(&LGS_INT, dim);
        isStatic = true;
    }
    LgsField* getField(const std::string& fieldName) override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    bool equals(LgsType* other) override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* modIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* crossIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* getIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index) override;
    void addIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index, LgsExpr* value) override;
    Value* matVecMul(LgsCgModule& cg, const LgsExpr* left, LgsExpr* right) const;
    static size_t getSwizzleSet(char c);
    static size_t getComponentIndex(char c);
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

Function* dotProductFunc(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right);
Function* crossProductFunc(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right);
