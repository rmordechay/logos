#ifndef LGSINTERFACE_H
#define LGSINTERFACE_H
#include "LgsType.h"


struct LgsFuncSignature;

class LgsInterface final : public LgsType {
public:
    string name;
    vector<LgsFuncSignature*> funcSignatures;

    explicit LgsInterface(const string& name) : name(name) {}
    const string getName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsInterface() override = default;
};



#endif //LGSINTERFACE_H
