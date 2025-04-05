#ifndef LGSENVS_H
#define LGSENVS_H
#include "types/LgsObject.h"

class LgsEnvObject final : public LgsObject {
public:
    static constexpr auto name = "Env";

    explicit LgsEnvObject() : LgsObject(name) {}
};

#endif //LGSENVS_H
