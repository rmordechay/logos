#ifndef LOGOSCONSTANTEXPR_H
#define LOGOSCONSTANTEXPR_H
#include "exprs/unary/LgsUnaryExpr.h"


class LgsFloatConst;
class LgsBool;
class LgsIntConst;
class LgsStrConst;
using namespace std;

class LgsConstExpr : public LgsUnaryExpr {
public:
    explicit LgsConstExpr(LgsType* type) : LgsUnaryExpr(type) {
        type->isConst = true;
    }
    ~LgsConstExpr() override = default;
};

#endif //LOGOSCONSTANTEXPR_H
