#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LgsIterable.h"
#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsInt.h"
#include "types/LgsVoid.h"

class LgsArray final : public LgsUnaryExpr, public LgsIterable {
public:
    vector<LgsExpr*> initialElements;
    FunctionType* const initArrIRFuncType = FunctionType::get(ptrTy, false);
    FunctionType* const freeArrIRFuncType = FunctionType::get(LgsVoid::IRValue, {ptrTy}, false);
    FunctionType* const addElementIRFuncType = FunctionType::get(LgsVoid::IRValue, {ptrTy, LgsInt::IRValue}, false);

    explicit LgsArray() : LgsUnaryExpr(nullptr) {}
    explicit LgsArray(LgsType* type) : LgsUnaryExpr(type) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    size_t size() override;
    FunctionCallee getIRFuncInitArr(const CodeGenMetadata* metadata) const;
    void free(CodeGenMetadata* metadata) override;
    FunctionCallee getIRFuncAddElement(const CodeGenMetadata* metadata) const;
    ~LgsArray() override = default;
};

#endif //LOGOSARRAY_H
