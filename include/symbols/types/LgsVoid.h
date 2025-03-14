#ifndef LOGOSVOID_H
#define LOGOSVOID_H

#include "LgsType.h"
#include <LogosMetadata.h>

using namespace std;

class LgsVoid final : public LgsType {
public:
    Type* IRType = Type::getVoidTy(context);
    string typeName = "Void";

    const string getName() const override;
    Type* getIRType() override;
    LgsConstant* getZeroValue() override;
    bool equals(LgsType* other) const override;
    ~LgsVoid() override = default;
};

inline LgsVoid LOGOS_VOID;

#endif //LOGOSVOID_H
