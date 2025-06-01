#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "codegen/CodegenMetadata.h"
#include "exprs/LgsExpr.h"
#include <string>

class LgsUnaryExpr : public LgsExpr {
public:
    explicit LgsUnaryExpr() : LgsExpr(nullptr) {}
    explicit LgsUnaryExpr(LgsType* type) : LgsExpr(type) {}
    Value* addIR(Module* module, LgsExpr* other) override;
    Value* subIR(Module* module, LgsExpr* other) override;
    Value* mulIR(Module* module, LgsExpr* other) override;
    Value* divIR(Module* module, LgsExpr* other) override;
    virtual std::string getName();
    ~LgsUnaryExpr() override = default;
};

inline std::string LgsUnaryExpr::getName() {
    assert(false);
}

inline Value* LgsUnaryExpr::addIR(Module* module, LgsExpr* other) {
    const auto l = this->getIRValue(module);
    const auto r = other->getIRValue(module);
    return builder.CreateAdd(l, r);
}

inline Value* LgsUnaryExpr::subIR(Module* module, LgsExpr* other) {
    const auto l = this->getIRValue(module);
    const auto r = other->getIRValue(module);
    return builder.CreateSub(l, r);
}

inline Value* LgsUnaryExpr::mulIR(Module* module, LgsExpr* other) {
    const auto l = this->getIRValue(module);
    const auto r = other->getIRValue(module);
    return builder.CreateMul(l, r);
}

inline Value* LgsUnaryExpr::divIR(Module* module, LgsExpr* other) {
    const auto l = this->getIRValue(module);
    const auto r = other->getIRValue(module);
    return builder.CreateSDiv(l, r);
}

#endif //LOGOSUNARYEXPR_H
