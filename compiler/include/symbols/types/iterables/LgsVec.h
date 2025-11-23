#pragma once
#include "exprs/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"

class LgsVec final : public LgsIterable {
public:
    static constexpr auto baseName = "Vec";
    size_t vectorDim = 0;
    std::vector<uint8_t> indices;

    explicit LgsVec(const size_t dim, LgsType* baseType = &LGS_FLOAT) : LgsIterable(baseType), vectorDim(dim) {
        assert(dim > 1 && dim <= 4);
        size = new LgsIntConst(&LGS_INT, dim);
        isStatic = true;
        passByRef = true;
    }

    LgsField* getField(const std::string& fieldName) override;
    Type* getIRType(LgsLLVMGen& cg) override;
    Constant* getRTType(LgsLLVMGen& cg) override;
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* lenIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    Value* dotProduct(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) const;
    Value* matMul(LgsLLVMGen& cg, const LgsExpr* left, const LgsExpr* right) const;
    static size_t getSwizzleSet(char c);
    static size_t getComponentIndex(char c);
    std::string strFormatPart() const override;
    llvm::DIType* getDebugType(LgsLLVMGen& cg) override;
    LgsType* clone() override;
};
