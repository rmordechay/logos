#ifndef LGSSTRMETHODS_H
#define LGSSTRMETHODS_H
#include "funcs/LgsMethodImpl.h"

class LgsStrFormatFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam args{};

    explicit LgsStrFormatFunc(LgsType* parent) : LgsMethodImpl("format", parent->getIRName(), parent) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
        funcType.isVariadic = true;
    }
};

#endif //LGSSTRMETHODS_H
