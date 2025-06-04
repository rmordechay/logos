#ifndef LOGOSVOID_H
#define LOGOSVOID_H
#include "types/LgsType.h"

using namespace std;

class LgsVoid final : public LgsType {
public:
    static constexpr auto name = "Void";

    LgsVoid() {
        isVoid = true;
        isPrimitive = true;
    }
    string prettyName() const override;
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    ~LgsVoid() override = default;
};

inline LgsVoid LGS_VOID;

#endif //LOGOSVOID_H
