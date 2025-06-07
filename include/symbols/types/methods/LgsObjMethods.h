#ifndef LGSOBJMETHODS_H
#define LGSOBJMETHODS_H
#include "funcs/LgsBuiltinFunc.h"
#include "types/LgsArray.h"

class LgsObjFieldsFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};

    explicit LgsObjFieldsFunc(LgsType* parent) : LgsBuiltinFunc("fields", new LgsArray(&LGS_ANY), parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self};
    }
};

#endif //LGSOBJMETHODS_H
