#pragma once
#include "LgsAny.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsBool.h"
#include "LgsVoid.h"

class LgsIterator final : public LgsUnaryExpr {
public:

    LgsExpr* baseExpr;
    static constexpr auto name = "Iterator";

    explicit LgsIterator(LgsExpr* baseExpr) : baseExpr(baseExpr) {
        type = baseExpr->type;
    }

    string prettyName() override;
    Value* createIRValue(LgsCodeGen* codeGen) override;
    void initIterator(LgsCodeGen* codeGen);
    Value* next(LgsCodeGen* codeGen) const;
    Value* hasNext(LgsCodeGen* codeGen) const;
    ~LgsIterator() override = default;
};


inline void LgsIterator::initIterator(LgsCodeGen* codeGen) {
    LgsBuiltinFunc iterInitFunc{"initIter", &LGS_VOID, type->getName(), {type, &LGS_ANY}};
    const auto structType = codeGen->getStructType(name, {codeGen->ptrTy(), codeGen->i64Ty(), codeGen->ptrTy(), codeGen->ptrTy(), codeGen->ptrTy(), codeGen->ptrTy()});
    IRValue = codeGen->builder.CreateAlloca(structType);
    iterInitFunc.callIR(codeGen, {baseExpr->getIRValue(codeGen), IRValue});
}

inline Value* LgsIterator::next(LgsCodeGen* codeGen) const {
    LgsBuiltinFunc iterInitFunc{"next", &LGS_ANY, type->getName(), {&LGS_ANY}};
    return iterInitFunc.callIR(codeGen, {IRValue});
}

inline Value* LgsIterator::hasNext(LgsCodeGen* codeGen) const {
    LgsBuiltinFunc iterInitFunc{"hasNext", &LGS_BOOL, type->getName(), {&LGS_ANY}};
    return iterInitFunc.callIR(codeGen, {IRValue});
}
