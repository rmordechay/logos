#ifndef LGSCAST_H
#define LGSCAST_H
#include "LgsExpr.h"
#include "LgsValue.h"

class LgsType;
class LgsExpr;

class LgsCast final : public LgsExpr {
public:
    LgsType* toType = nullptr;
    LgsExpr* fromValue = nullptr;
    LgsExpr* toValue = nullptr;

    LgsCast(LgsType* castToType, LgsExpr* castFromValue) : LgsExpr(castToType), toType(castToType), fromValue(castFromValue) {}
    Value* createIRValue(CodegenMetadata* metadata) override;
    Value* addIR(CodegenMetadata* metadata, LgsExpr* other) override;
    bool cast();
    ~LgsCast() override;
};

#endif //LGSCAST_H
