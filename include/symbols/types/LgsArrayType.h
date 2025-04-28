#ifndef LOGOSARRAYTYPE_H
#define LOGOSARRAYTYPE_H
#include "LgsAny.h"
#include "LgsBool.h"
#include "LgsStr.h"
#include "LgsType.h"
#include "LgsVoid.h"
#include "funcs/LgsMethodImpl.h"
#include "funcs/LgsParam.h"

class LgsBool;
class LgsStr;
class LgsInt;
struct CodeGenMetadata;

class LgsArrayType final : public LgsType {
public:
    static constexpr auto name = "ArrayType";
    LgsType* underlyingType = nullptr;

    StructType* arrIR = StructType::create(context, {i64Ty, i64Ty, ptrTy});
    Attribute sret = Attribute::getWithStructRetType(context, arrIR);
    FunctionType* const initArrIRFuncType = FunctionType::get(voidTy, {ptrTy, i64Ty, i64Ty}, false);
    FunctionType* const freeArrIRFuncType = FunctionType::get(voidTy, {ptrTy}, false);
    FunctionType* const addElementIRFuncType = FunctionType::get(voidTy, {ptrTy, ptrTy}, false);
    FunctionType* const getElementIRFuncType = FunctionType::get(ptrTy, {ptrTy, i32Ty}, false);

    LgsMethodImpl addFunc = LgsMethodImpl("add", new LgsVoid(), name, {LgsParam(this), LgsParam(new LgsStr())});
    LgsMethodImpl isEmptyFunc = LgsMethodImpl("isEmpty", new LgsBool(), name, {LgsParam(this)});

    LgsArrayType() {
        underlyingType = new LgsAny();
        methods[addFunc.signature.name] = {&addFunc};
        methods[isEmptyFunc.signature.name] = {&isEmptyFunc};
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
