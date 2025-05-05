#ifndef LGSINTERFACE_H
#define LGSINTERFACE_H
#include "LgsType.h"

struct LgsFuncType;

class LgsInterface final : public LgsType {
public:
    string name;

    explicit LgsInterface(const string& name) : name(name) {}
    const string getPrettyName() const override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsInterface() override = default;
};



#endif //LGSINTERFACE_H
