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

    Value* createIRValue(LgsModule* module) override;
    void initIterator(LgsModule* module);
    Value* next(LgsModule* module) const;
    Value* hasNext(LgsModule* module) const;
    ~LgsIterator() override = default;
};


inline void LgsIterator::initIterator(LgsModule* module) {
    LgsBuiltinFunc iterInitFunc{"initIter", &LGS_VOID, type->getIRName(), {type, &LGS_ANY}};
    const auto structType = getIRStructType(module->context, name, {ptrTy(module->context), i64Ty(module->context), ptrTy(module->context), ptrTy(module->context), ptrTy(module->context), ptrTy(module->context)});
    IRValue = module->builder.CreateAlloca(structType);
    iterInitFunc.callIR(module, {baseExpr->getIRValue(module), IRValue});
}

inline Value* LgsIterator::next(LgsModule* module) const {
    LgsBuiltinFunc iterInitFunc{"next", &LGS_ANY, type->getIRName(), {&LGS_ANY}};
    return iterInitFunc.callIR(module, {IRValue});
}

inline Value* LgsIterator::hasNext(LgsModule* module) const {
    LgsBuiltinFunc iterInitFunc{"hasNext", &LGS_BOOL, type->getIRName(), {&LGS_ANY}};
    return iterInitFunc.callIR(module, {IRValue});
}
