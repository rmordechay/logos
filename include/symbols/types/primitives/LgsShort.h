#pragma once


class LgsShort final : public LgsType {
public:
    static constexpr auto name = "Int";

    LgsShort() {
        isPrimitive = true;
    }
    size_t getSizeBytes() override;
    Type* getIRType() override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    string getStrFormatPart() const override;
    LgsType* clone() override;
    ~LgsShort() override = default;
};

inline LgsShort LGS_SHORT;


