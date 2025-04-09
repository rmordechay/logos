#ifndef LOGOSARRAYTYPE_H
#define LOGOSARRAYTYPE_H
#include "LgsInt.h"
#include "LgsStr.h"
#include "LgsType.h"
#include "LgsVoid.h"
#include "funcs/LgsMethodImpl.h"
#include "funcs/LgsParam.h"

class LgsStr;
class LgsInt;
struct CodeGenMetadata;

class LgsArrayType final : public LgsType {
public:
    LgsType* underlyingType = nullptr;
    StructType* arrIR = StructType::create(context, {i64Ty, i64Ty, ptrTy});
    Attribute sret = Attribute::getWithStructRetType(context, arrIR);
    LgsMethodImpl addFunc = LgsMethodImpl("add", new LgsVoid(), getName(), {LgsParam(this), LgsParam(new LgsStr())});
    FunctionType* const initArrIRFuncType = FunctionType::get(ptrTy, {ptrTy, i64Ty}, false);
    FunctionType* const freeArrIRFuncType = FunctionType::get(voidTy, {ptrTy}, false);
    FunctionType* const addElementIRFuncType = FunctionType::get(voidTy, {ptrTy, ptrTy}, false);
    FunctionType* const getElementIRFuncType = FunctionType::get(ptrTy, {ptrTy, i32Ty}, false);

    LgsArrayType() {
        methods[addFunc.signature.name] = {&addFunc};
    }

    explicit LgsArrayType(LgsType* underlyingType) : underlyingType(underlyingType) {}
    size_t size() override;
    const string getName() const override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;

    Value* initIRArr(CodeGenMetadata* metadata, size_t size) const;
    Value* getIRFuncGetElement(CodeGenMetadata* metadata, Value* arrPtr, Value* index) const;
    FunctionCallee getIRFuncAddElement(const CodeGenMetadata* metadata) const;
    void free(CodeGenMetadata* metadata, bool* isFreed, Value* IRValue) const;
    ~LgsArrayType() override = default;
};

#endif //LOGOSARRAYTYPE_H
