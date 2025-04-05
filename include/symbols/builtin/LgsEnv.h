#ifndef LGSENVS_H
#define LGSENVS_H
#include "types/LgsObject.h"

class LgsEnv final : public LgsObject {
public:
    static constexpr auto name = "Env";

    explicit LgsEnv() : LgsObject(name) {}
};

#endif //LGSENVS_H
