#ifndef LGSSTRMETHODS_H
#define LGSSTRMETHODS_H
#include "funcs/LgsMethodImpl.h"
#include "types/LgsAny.h"

void replaceNextPlaceholder(string& str, const LgsExpr* expr);

class LgsStrFormatFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam args{&LGS_ANY};

    explicit LgsStrFormatFunc(LgsType* parent) : LgsMethodImpl("format", parent->getIRName(), parent) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
        funcType.isVariadic = true;
    }

    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override;
};

#endif //LGSSTRMETHODS_H
