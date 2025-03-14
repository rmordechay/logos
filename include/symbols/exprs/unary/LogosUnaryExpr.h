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

    Value* add(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* sub(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* mul(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* div(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* gt(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* lt(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* eq(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* ne(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* le(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* ge(CodeGenMetadata* metadata, LgsExpr* other) override;
    ~LgsUnaryExpr() override = default;
};

inline string LgsUnaryExpr::getName() { return ""; }

inline Value* LgsUnaryExpr::add(CodeGenMetadata* metadata, LgsExpr* other) {
     assert(false && "unary add operator not implemented");
}

inline Value* LgsUnaryExpr::sub(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "unary sub operator not implemented");
}

inline Value* LgsUnaryExpr::mul(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "unary mul operator not implemented");
}

inline Value* LgsUnaryExpr::div(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "unary div operator not implemented");
}

inline Value* LgsUnaryExpr::gt(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "unary gt operator not implemented");
}

inline Value* LgsUnaryExpr::lt(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "unary lt operator not implemented");
}

inline Value* LgsUnaryExpr::eq(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "unary eq operator not implemented");
}

inline Value* LgsUnaryExpr::ne(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "unary ne operator not implemented");
}

inline Value* LgsUnaryExpr::le(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "unary le operator not implemented");
}

inline Value* LgsUnaryExpr::ge(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "unary ge operator not implemented");
}


#endif //LOGOSUNARYEXPR_H
