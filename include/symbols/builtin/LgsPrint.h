#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H
#include "types/LgsFloat.h"
#include <types/LgsVoid.h>

class LgsPrint final : public LgsFunc {
public:
    static constexpr auto name = "print";
    explicit LgsPrint(const vector<LgsParam>& params) : LgsFunc(name, new LgsVoid(), params) {}

    vector<Type*> getIRParamTypes(const CodeGenMetadata* metadata) override;
    ~LgsPrint() override = default;
};

#endif //LOGOSPRINT_H
