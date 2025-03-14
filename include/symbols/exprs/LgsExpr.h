#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "LgsValue.h"
#include <LgsType.h>

class LgsExpr: virtual public LgsValue {
public:
    LgsType* type = nullptr;

    explicit LgsExpr(LgsType* type) : type(type) {}

    virtual Value* operator+(LgsExpr* other) = 0;
    ~LgsExpr() override = default;
};

#endif //LOGOSEXPR_H

