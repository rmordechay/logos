#ifndef LOGOSVOID_H
#define LOGOSVOID_H
#include "LgsType.h"

using namespace std;

class LgsVoid final : public LgsType {
public:

    static constexpr auto name = "Void";

    const string getName() const override;
    size_t size() override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    ~LgsVoid() override = default;
};

#endif //LOGOSVOID_H
