#pragma once
#include "LgsAny.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "primitives/LgsBool.h"
#include "LgsVoid.h"
#include "funcs/LgsFunc.h"

class LgsIterator final : public LgsUnaryExpr {
public:

    LgsExpr* baseExpr;
    static constexpr auto name = "Iterator";

    explicit LgsIterator(LgsExpr* baseExpr) : baseExpr(baseExpr) {
        type = baseExpr->type;
    }

    std::string pname() override;
    void createIRValue(LgsCodeGen* codeGen) override;
    void initIterator(LgsCodeGen* codeGen);
    Value* next(LgsCodeGen* codeGen) const;
    Value* hasNext(LgsCodeGen* codeGen) const;
    ~LgsIterator() override = default;
};


inline void LgsIterator::initIterator(LgsCodeGen* codeGen) {
    LgsFunc iterInitFunc{"initIter", &LGS_VOID, {type, &LGS_ANY}};
    const auto structType = codeGen->getStructType({codeGen->ptrTy(), codeGen->i64Ty(), codeGen->ptrTy(), codeGen->ptrTy(), codeGen->ptrTy(), codeGen->ptrTy()}, name);
    IRValue = codeGen->builder.CreateAlloca(structType);
    iterInitFunc.callIR(codeGen, {baseExpr->getIRValue(codeGen), IRValue});
}

inline Value* LgsIterator::next(LgsCodeGen* codeGen) const {
    LgsFunc iterInitFunc{"next", &LGS_ANY, {&LGS_ANY}};
    return iterInitFunc.callIR(codeGen, {IRValue});
}

inline Value* LgsIterator::hasNext(LgsCodeGen* codeGen) const {
    LgsFunc iterInitFunc{"hasNext", &LGS_BOOL, {&LGS_ANY}};
    return iterInitFunc.callIR(codeGen, {IRValue});
}
