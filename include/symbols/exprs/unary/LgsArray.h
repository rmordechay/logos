#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LgsIterable.h"
#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsVoid.h"

class LgsArray final : public LgsUnaryExpr, public LgsIterable {
public:
    vector<LgsExpr*> initialElements;
    FunctionType* const initArrIRFuncType = FunctionType::get(ptrTy, {i64Ty}, false);
    FunctionType* const freeArrIRFuncType = FunctionType::get(voidTy, {ptrTy}, false);
    FunctionType* const addElementIRFuncType = FunctionType::get(voidTy, {ptrTy, i32Ty}, false);
    FunctionType* const getElementIRFuncType = FunctionType::get(i32Ty, {ptrTy, i32Ty}, false);

    explicit LgsArray() : LgsUnaryExpr(nullptr) {}
    explicit LgsArray(LgsType* type) : LgsUnaryExpr(type) {}
    size_t size() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* initIRArr(CodeGenMetadata* metadata) const;
    FunctionCallee getIRFuncAddElement(const CodeGenMetadata* metadata) const;
    Value* getIRFuncGetElement(CodeGenMetadata* metadata, Value* index) const;
    void free(CodeGenMetadata* metadata) override;
    ~LgsArray() override = default;
};

#endif //LOGOSARRAY_H
