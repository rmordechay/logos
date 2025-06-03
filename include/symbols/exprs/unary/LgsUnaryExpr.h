#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "codegen/CodegenMetadata.h"
#include "exprs/LgsExpr.h"
#include "logos/LgsRuntime.h"

#include <string>

class LgsUnaryExpr : public LgsExpr {
public:
    explicit LgsUnaryExpr() : LgsExpr(nullptr) {}
    explicit LgsUnaryExpr(LgsType* type) : LgsExpr(type) {}
    Value* addIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* subIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* mulIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* divIR(LgsRuntime* runtime, LgsExpr* other) override;
    virtual std::string getName();
    ~LgsUnaryExpr() override = default;
};

inline std::string LgsUnaryExpr::getName() {
    assert(false);
}

inline Value* LgsUnaryExpr::addIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto l = this->getIRValue(runtime);
    const auto r = other->getIRValue(runtime);
    return runtime->builder.CreateAdd(l, r);
}

inline Value* LgsUnaryExpr::subIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto l = this->getIRValue(runtime);
    const auto r = other->getIRValue(runtime);
    return runtime->builder.CreateSub(l, r);
}

inline Value* LgsUnaryExpr::mulIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto l = this->getIRValue(runtime);
    const auto r = other->getIRValue(runtime);
    return runtime->builder.CreateMul(l, r);
}

inline Value* LgsUnaryExpr::divIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto l = this->getIRValue(runtime);
    const auto r = other->getIRValue(runtime);
    return runtime->builder.CreateSDiv(l, r);
}

#endif //LOGOSUNARYEXPR_H
