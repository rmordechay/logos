#ifndef LGSREFLECT_H
#define LGSREFLECT_H
#include "exprs/unary/LgsArray.h"
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

class LgsReflectGetFields final : public LgsMethodImpl {
public:
    explicit LgsReflectGetFields(const string& parentName) : LgsMethodImpl("getFields", new LgsArrayType(&LGS_STR), parentName, {LgsParam("object", new LgsObject())}) {}

    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override {
        return nullptr;
    }

    ~LgsReflectGetFields() override = default;
};

class LgsReflect final : public LgsObject {
public:
    static constexpr auto name = "Reflect";
    LgsReflectGetFields getFieldsFunc = LgsReflectGetFields(name);

    explicit LgsReflect() : LgsObject(name) {
        addMethod(&getFieldsFunc);
    }
    ~LgsReflect() override = default;
};

#endif //LGSREFLECT_H
