#ifndef LGSENVS_H
#define LGSENVS_H
#include "types/LgsObject.h"

class LgsEnv final : public LgsObject {
public:
    vector<LgsVarDec*> varDecs;
    static constexpr auto name = "Env";

    explicit LgsEnv(const vector<LgsVarDec*>& varDecs) : LgsObject(name), varDecs(varDecs) {}
};

#endif //LGSENVS_H
