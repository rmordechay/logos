#pragma once
#include "stmts/LgsField.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"

class LgsVec final : public LgsIterable {
public:
    static constexpr auto name = "Vec";
    size_t dimVec = 0;

    explicit LgsVec(const size_t dim, LgsType* baseType = &LGS_FLOAT) : LgsIterable(baseType), dimVec(dim) {
        assert(dim > 1 && dim <= 4);
        isStatic = true;
        rttKind = RTT_VEC;
    }
    LgsField* getField(const std::string& fieldName) override;
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    std::optional<int64_t> getConstLength() override;
    bool equals(LgsType* other) override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee) override;
    Constant* getRTTypeExtra(LgsCodeGen& cg) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* modIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* crossIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr);
    Value* inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    void addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) override;
    Value* matVecMul(LgsCodeGen& cg, const LgsExpr* left, LgsExpr* right) const;
    static size_t getSwizzleSet(char c);
    static size_t getComponentIndex(char c);
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

Function* getDotProductFunc(LgsCodeGen& cg, LgsVec* vecType);
Function* getCrossProductFunc(LgsCodeGen& cg, LgsVec* vecType);
