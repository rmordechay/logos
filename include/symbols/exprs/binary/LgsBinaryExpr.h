#ifndef LOGOSBINARYEXPR_H
#define LOGOSBINARYEXPR_H
#include "LgsExpr.h"
#include "LgsOperator.h"

#include <LogosMetadata.h>
#include <LgsType.h>

class LgsBinaryExpr final : public LgsExpr {
public:
    LgsExpr* left;
    LgsExpr* right;
    LgsOperator op;

    explicit LgsBinaryExpr(LgsType* type, LgsExpr* left, LgsExpr* right, const LgsOperator op) : LgsExpr(type), left(left), right(right), op(op) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
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
    ~LgsBinaryExpr() override = default;
};

inline Value* LgsBinaryExpr::add(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "binary add operator not implemented");
}

inline Value* LgsBinaryExpr::sub(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "binary sub operator not implemented");
}

inline Value* LgsBinaryExpr::mul(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "binary mul operator not implemented");
}

inline Value* LgsBinaryExpr::div(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "binary div operator not implemented");
}

inline Value* LgsBinaryExpr::gt(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "binary gt operator not implemented");
}

inline Value* LgsBinaryExpr::lt(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "binary lt operator not implemented");
}

inline Value* LgsBinaryExpr::eq(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "binary eq operator not implemented");
}

inline Value* LgsBinaryExpr::ne(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "binary ne operator not implemented");
}

inline Value* LgsBinaryExpr::le(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "binary le operator not implemented");
}

inline Value* LgsBinaryExpr::ge(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "binary ge operator not implemented");
}

#endif //LOGOSBINARYEXPR_H
