#pragma once
#include <string>

#include "stmts/LgsField.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "LgsValue.h"
#include "Lgs_Types.h"
#include "types/iterables/LgsIterable.h"

class LgsCodeGen;
class LgsExpr;
class LgsType;
namespace llvm {
class Function;
class Value;
}

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
    std::string fmtStr() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    bool canCastTo(LgsType* other) override;
    std::optional<int64_t> getConstLength() override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Constant* getRTTypeExtra(LgsCodeGen& cg) override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* modIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) override;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    void addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) override;
    Value* matVecMul(LgsCodeGen& cg, const LgsExpr* left, LgsExpr* right) const;
    static size_t getSwizzleSet(char c);
    static size_t getComponentIndex(char c);
    DIType* getDebugType(LgsCodeGen& cg) override;
};

Function* getDotProductFunc(LgsCodeGen& cg, LgsVec* vecType);
Function* getCrossProductFunc(LgsCodeGen& cg, LgsVec* vecType);
