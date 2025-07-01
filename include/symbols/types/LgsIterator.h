#pragma once
#include "LgsAny.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsVoid.h"
#include "utils/LgsUtils.h"

class LgsIterator final : public LgsUnaryExpr {
public:
    LgsExpr* baseExpr;
    static constexpr auto name = "Iterator";

    explicit LgsIterator(LgsExpr* baseExpr) : baseExpr(baseExpr) {
        type = baseExpr->type;
    }

    Value* createIRValue(LgsModule* runtime) override;
    void initIterator(LgsModule* runtime);
    Value* next(LgsModule* runtime) const;
    Value* hasNext(LgsModule* runtime) const;
    ~LgsIterator() override = default;
};


inline void LgsIterator::initIterator(LgsModule* runtime) {
    LgsBuiltinFunc iterInitFunc{"initIter", &LGS_VOID, type->getIRName(), {type, &LGS_ANY}};
    const auto structType = getIRStructType(runtime->context, name, {ptrTy(runtime->context), i64Ty(runtime->context), ptrTy(runtime->context), ptrTy(runtime->context), ptrTy(runtime->context), ptrTy(runtime->context)});
    IRValue = runtime->builder.CreateAlloca(structType);
    iterInitFunc.callIR(runtime, {baseExpr->getIRValue(runtime), IRValue});
}

inline Value* LgsIterator::next(LgsModule* runtime) const {
    LgsBuiltinFunc iterInitFunc{"next", &LGS_ANY, type->getIRName(), {&LGS_ANY}};
    return iterInitFunc.callIR(runtime, {IRValue});
}

inline Value* LgsIterator::hasNext(LgsModule* runtime) const {
    LgsBuiltinFunc iterInitFunc{"hasNext", &LGS_BOOL, type->getIRName(), {&LGS_ANY}};
    return iterInitFunc.callIR(runtime, {IRValue});
}
