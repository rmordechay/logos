#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H
#include "funcs/LgsFuncImpl.h"
#include "types/LgsFloat.h"
#include <types/LgsVoid.h>

class LgsPrint final : public LgsFuncImpl {
public:
    static constexpr auto name = "print";
    explicit LgsPrint(const vector<LgsParam>& params) : LgsFuncImpl(name, &LGS_VOID, params) {}

    void setIRFuncType(const CodeGenMetadata* metadata) override;
    ~LgsPrint() override = default;
};

#endif //LOGOSPRINT_H
