#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LgsForLoop.h"
#include <exprs/unary/LgsUnaryExpr.h>

class LgsDArrayType;

class LgsForeachLoop final : public LgsForLoop {
public:
    LgsUnaryExpr* iterExpr = nullptr;
    Value* iterPtr = nullptr;

    explicit LgsForeachLoop(LgsUnaryExpr* iterable) : iterExpr(iterable) {}
    void setIRLoopVars(Module* module) override;
    void setIRIterable(Module* module) override;
    Value* loopStart(Module* module) override;
    Value* loopEnd(Module* module) override;
    ~LgsForeachLoop() override;
};

#endif //LOGOSFOREACHLOOP_H
