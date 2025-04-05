#ifndef LGSENVS_H
#define LGSENVS_H
#include "types/LgsObject.h"

class LgsEnvObj final : public LgsObject {
public:
    static constexpr auto name = "Env";
    vector<LgsVarDec*> varDecs;

    explicit LgsEnvObj(const vector<LgsVarDec*>& varDecs) : LgsObject(name), varDecs(varDecs) {}
};

#endif //LGSENVS_H
