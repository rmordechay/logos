#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H
#include "types/LgsChar.h"
#include "types/LgsFloat.h"
#include <types/LgsStr.h>
#include <types/LgsVoid.h>


class LgsPrint final : public LgsFunc {
public:
    static constexpr auto name = "print";
    explicit LgsPrint(const vector<LgsParam*>& params) : LgsFunc(name, new LgsVoid(), params) {
        signature.setNameFromParams();
    }
    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override;
    void createIRValue(CodeGenMetadata* metadata) override;
    Function* getIRFunc(const CodeGenMetadata* metadata) override;
    void setIRFuncType() override;
    ~LgsPrint() override = default;
};

#endif //LOGOSPRINT_H
