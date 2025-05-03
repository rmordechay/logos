#ifndef LGSREFLECT_H
#define LGSREFLECT_H
#include "exprs/unary/LgsDArray.h"
#include "exprs/unary/LgsVariable.h"
#include "funcs/LgsMethodImpl.h"
#include "types/LgsAny.h"
#include "types/LgsObject.h"

class LgsReflectGetFields final : public LgsMethodImpl {
public:
    LgsAny rt = LgsAny();
    const LgsObject* parent;

    explicit LgsReflectGetFields(const LgsObject* parent) : LgsMethodImpl("getFields", &rt, parent->name, {LgsParam(new LgsObject())}), parent(parent) {
        isPublic = true;
        isStatic = true;
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
