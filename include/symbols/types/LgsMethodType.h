#ifndef LGSMETHODTYPE_H
#define LGSMETHODTYPE_H
#include "LgsFuncType.h"


class LgsMethodType final : public LgsFuncType {
public:
    string parentName;

    string getIRName() override;
    FunctionType* getIRFuncType(const CodeGenMetadata* metadata) override;
    void setIRFuncParams(Argument* args) override;
    bool equals(LgsType* other) const override;
    ~LgsMethodType() override = default;
};

#endif //LGSMETHODTYPE_H
