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
    void setIRLoopVars(LgsRuntime* runtime) override;
    void setIterVars(LgsRuntime* runtime, LgsArray* arr) const;
    void setIterVars(LgsRuntime* runtime, LgsMap* map) const;
    void setIRIterable(LgsRuntime* runtime) override;
    Value* loopStart(LgsRuntime* runtime) override;
    Value* loopEnd(LgsRuntime* runtime) override;
    ~LgsForeachLoop() override;
};

#endif //LOGOSFOREACHLOOP_H
