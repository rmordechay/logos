#ifndef LOGOSVOID_H
#define LOGOSVOID_H

#include "CodeGenMetadata.h"
#include "LgsType.h"

using namespace std;

class LgsVoid final : public LgsType {
public:
    static constexpr auto name = "Void";
    Type* IRType = Type::getVoidTy(context);

    const string getName() const override;
    Type* getIRType() override;
    LgsConst* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    ~LgsVoid() override = default;
};

inline LgsVoid LOGOS_VOID;

#endif //LOGOSVOID_H
