#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H
#include "types/LgsChar.h"
#include "types/LgsFloat.h"
#include "types/LgsInt.h"
#include <types/LgsStr.h>
#include <types/LgsVoid.h>


class LgsPrint final : public LgsFunc {
public:
    static constexpr auto name = "print";
    explicit LgsPrint(const vector<LgsParam*>& params) : LgsFunc(name, &LOGOS_VOID, params) {}
    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void setIRFunc(CodeGenMetadata* metadata) override;
    ~LgsPrint() override = default;
};

#endif //LOGOSPRINT_H
