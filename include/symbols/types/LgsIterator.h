#pragma once
#include "LgsAny.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsVoid.h"

class LgsIterator final : public LgsUnaryExpr {
public:
    LgsExpr* baseExpr;
    static constexpr auto name = "Iterator";

    explicit LgsIterator(LgsExpr* baseExpr) : baseExpr(baseExpr) {
        type = baseExpr->type;
    }
    static StructType* getStructType();
    Value* createIRValue(LgsRuntime* runtime) override;
    void initIterator(LgsRuntime* runtime);
    Value* next(LgsRuntime* runtime) const;
    Value* hasNext(LgsRuntime* runtime) const;
    ~LgsIterator() override = default;
};


inline void LgsIterator::initIterator(LgsRuntime* runtime) {
    LgsBuiltinFunc iterInitFunc{"initIter", &LGS_VOID, type->getIRName(), {type, &LGS_ANY}};
    IRValue = runtime->builder.CreateAlloca(getStructType());
    iterInitFunc.callIR(runtime, {baseExpr->getIRValue(runtime), IRValue});
}

inline Value* LgsIterator::next(LgsRuntime* runtime) const {
    LgsBuiltinFunc iterInitFunc{"next", &LGS_ANY, type->getIRName(), {&LGS_ANY}};
    return iterInitFunc.callIR(runtime, {IRValue});
}

inline Value* LgsIterator::hasNext(LgsRuntime* runtime) const {
    LgsBuiltinFunc iterInitFunc{"hasNext", &LGS_BOOL, type->getIRName(), {&LGS_ANY}};
    return iterInitFunc.callIR(runtime, {IRValue});
}
