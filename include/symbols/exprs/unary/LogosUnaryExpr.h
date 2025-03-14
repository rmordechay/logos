#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "LgsExpr.h"

#include <string>
#include <LgsType.h>

class LgsUnaryExpr: public LgsExpr {
public:
    explicit LgsUnaryExpr() : LgsExpr(nullptr) {}
    explicit LgsUnaryExpr(LgsType* type) : LgsExpr(type) {}
    virtual string getName();
    Value* operator+(LgsExpr* other) override;
    ~LgsUnaryExpr() override = default;
};

inline string LgsUnaryExpr::getName() { return ""; }

inline Value* LgsUnaryExpr::operator+(LgsExpr* other) {
    assert(false && "unary + operator not implemented");
}

#endif //LOGOSUNARYEXPR_H
