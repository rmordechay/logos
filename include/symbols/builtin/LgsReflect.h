#ifndef LGSREFLECT_H
#define LGSREFLECT_H
#include "exprs/unary/LgsArray.h"
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

class LgsReflectGetFields final : public LgsMethodImpl {
public:
    explicit LgsReflectGetFields(LgsObject* parent) : LgsMethodImpl("getFields", new LgsArrayType(&LGS_STR), parent->name, {LgsParam(parent), LgsParam(new LgsObject())}) {}

    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override {
        assert(false);
    }

    ~LgsReflectGetFields() override = default;
};

class LgsReflect final : public LgsObject {
public:
    static constexpr auto name = "Reflect";
    LgsReflectGetFields getFieldsFunc = LgsReflectGetFields(this);

    explicit LgsReflect() : LgsObject(name) {
        addMethod(&getFieldsFunc);
    }
    ~LgsReflect() override = default;
};

#endif //LGSREFLECT_H
