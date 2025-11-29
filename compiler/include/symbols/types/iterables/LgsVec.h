#pragma once
#include "exprs/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"

class LgsVec final : public LgsIterable {
public:
    static constexpr auto baseName = "Vec";
    size_t vectorDim = 0;

    explicit LgsVec(const size_t dim, LgsType* baseType = &LGS_FLOAT) : LgsIterable(baseType), vectorDim(dim) {
        assert(dim > 1 && dim <= 4);
        size = new LgsIntConst(&LGS_INT, dim);
        isStatic = true;
        passByRef = true;
    }

    LgsField* getField(const std::string& fieldName) override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string getGenericName() override;
    std::string getName() override;
    size_t sizeBytes() override;
    bool equals(LgsType* other) override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* crossIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
    Value* matMul(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right) const;
    static size_t getSwizzleSet(char c);
    static size_t getComponentIndex(char c);
    std::string strFormatPart() const override;
    llvm::DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsVec LGS_VEC2_F(2);
inline LgsVec LGS_VEC3_F(3);
inline LgsVec LGS_VEC4_F(4);
inline LgsVec LGS_VEC2_D(2, &LGS_DOUBLE);
inline LgsVec LGS_VEC3_D(3, &LGS_DOUBLE);
inline LgsVec LGS_VEC4_D(4, &LGS_DOUBLE);
inline LgsVec LGS_VEC2_I(2, &LGS_INT);
inline LgsVec LGS_VEC3_I(3, &LGS_INT);
inline LgsVec LGS_VEC4_I(4, &LGS_INT);