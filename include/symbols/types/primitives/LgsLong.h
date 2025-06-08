#pragma once


class LgsLong final : public LgsType {
public:
    static constexpr auto name = "Long";

    LgsLong() {
        isPrimitive = true;
    }
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    string getIRName() override;
    string prettyName() const override;
    bool equals(LgsType* other) override;
    ~LgsLong() override = default;
};

inline LgsLong LGS_LONG;


