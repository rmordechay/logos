#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LgsInt.h"
#include "LgsType.h"
#include "LgsVoid.h"
#include "funcs/LgsMethodImpl.h"
#include "funcs/LgsParam.h"

#include <string>

class LgsStr final : public LgsType {
public:
    static constexpr auto name = "Str";
    LgsMethodImpl addElementFunc = LgsMethodImpl("add", new LgsVoid(), "ArrayType", {new LgsParam(this), new LgsParam(new LgsInt())});

    const string getName() const override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    static void cleanStr(string& value);
    ~LgsStr() override = default;
};

inline void LgsStr::cleanStr(string& value) {
    value.erase(0, 1);
    value.pop_back();
}


#endif // LOGOSSTRING_H
