#pragma once
#include "types/LgsType.h"


class LgsFloat final : public LgsType {
public:
    static constexpr auto name = "Float";

    LgsFloat() {
        isPrimitive = true;
    }
    llvm::Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    string prettyName() const override;
    ~LgsFloat() override = default;
};

inline LgsFloat LGS_FLOAT;


