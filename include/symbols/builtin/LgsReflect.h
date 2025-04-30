#ifndef LGSREFLECT_H
#define LGSREFLECT_H
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

class LgsReflect final : public LgsObject {
public:
    static constexpr auto name = "Reflect";
    LgsMethodImpl getFieldFunc = LgsMethodImpl("get", new LgsStr(), name, {LgsParam(this), LgsParam(new LgsStr()), LgsParam(new LgsStr())});

    explicit LgsReflect() : LgsObject(name) {
        addMethod(&getFieldFunc);
    }
    ~LgsReflect() override = default;
};

#endif //LGSREFLECT_H
