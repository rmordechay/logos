#ifndef LOGOSARRAYTYPE_H
#define LOGOSARRAYTYPE_H
#include "LgsBool.h"
#include "LgsStr.h"
#include "LgsType.h"
#include "LgsVoid.h"
#include "LgsIterable.h"
#include "funcs/LgsMethodImpl.h"
#include "funcs/LgsParam.h"

class LgsBool;
class LgsStr;
class LgsInt;
struct CodeGenMetadata;

class LgsDArrType final : public LgsIterable {
public:
    static constexpr auto name = "DArrayType";
    LgsMethodImpl addFunc = LgsMethodImpl("add", &LGS_VOID, name, {LgsParam(this), LgsParam(&LGS_STR)});
    LgsMethodImpl isEmptyFunc = LgsMethodImpl("isEmpty", &LGS_BOOL, name, {LgsParam(this)});

    explicit LgsDArrType(LgsType* underlyingType, const vector<size_t>& initialSize = {}) : LgsIterable(underlyingType, initialSize) {
        addMethod(&addFunc);
        addMethod(&isEmptyFunc);
    }

    const string getName() const override;
    Type* getIRType() override;
    Type* getUnderlyingIRType() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    Value* getIRFuncGetElement(CodeGenMetadata* metadata, Value* arrPtr, Value* index) const;
    ~LgsDArrType() override = default;
};

#endif //LOGOSARRAYTYPE_H
