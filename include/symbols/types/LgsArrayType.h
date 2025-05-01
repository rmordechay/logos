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
    LgsMethodImpl addFunc = LgsMethodImpl("add", &LGS_VOID, name, {LgsParam(this), LgsParam(&LGS_STR)});
    LgsMethodImpl isEmptyFunc = LgsMethodImpl("isEmpty", &LGS_BOOL, name, {LgsParam(this)});

    LgsArrayType() {
        underlyingType = new LgsAny();
        addMethod(&addFunc);
        addMethod(&isEmptyFunc);
    }
    explicit LgsArrayType(LgsType* underlyingType) : underlyingType(underlyingType) {}
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
