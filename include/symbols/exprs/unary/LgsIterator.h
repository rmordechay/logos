#pragma once
#include "types/LgsAny.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsBool.h"
#include "types/LgsVoid.h"
#include "funcs/LgsFunc.h"

class LgsIterator final : public LgsUnaryExpr {
public:
    static constexpr auto name = "Iterator";
    LgsExpr* baseExpr;

    explicit LgsIterator(LgsExpr* baseExpr) : baseExpr(baseExpr) {
        type = baseExpr->type;
    }

    std::string pname() override;
    json::value asJSON() override;
    void initIterator(LgsCodeGen& codeGen);
    Value* next(LgsCodeGen* codeGen) const;
    Value* hasNext(LgsCodeGen& codeGen) const;
};


inline void LgsIterator::initIterator(LgsCodeGen& codeGen) {
    LgsFunc iterInitFunc{"initIter", &LGS_VOID, {type, &LGS_ANY}};
    const auto structType = codeGen.getStructType({codeGen.ptrTy(), codeGen.i64Ty(), codeGen.ptrTy(), codeGen.ptrTy(), codeGen.ptrTy(), codeGen.ptrTy()}, name);
    IRValue = codeGen.builder.CreateAlloca(structType);
    iterInitFunc.callIR(codeGen, {baseExpr->IRValue, IRValue});
}

inline Value* LgsIterator::next(LgsCodeGen* codeGen) const {
    LgsFunc iterInitFunc{"next", &LGS_ANY, {&LGS_ANY}};
    return iterInitFunc.callIR(*codeGen, {IRValue});
}

inline Value* LgsIterator::hasNext(LgsCodeGen& codeGen) const {
    LgsFunc iterInitFunc{"hasNext", &LGS_BOOL, {&LGS_ANY}};
    return iterInitFunc.callIR(codeGen, {IRValue});
}
