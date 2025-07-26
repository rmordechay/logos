#pragma once
#include "LgsUnaryExpr.h"

class LgsSingleton final : public LgsUnaryExpr {
public:

    Value* createIRValue(LgsModule* module) override;
    ~LgsSingleton() override = default;
};
