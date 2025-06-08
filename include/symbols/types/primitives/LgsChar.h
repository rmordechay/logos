#pragma once



class LgsChar final : public LgsType {
public:
    static constexpr auto name = "Char";

    LgsChar() {
        isPrimitive = true;
    }
    string prettyName() const override;
    Type* getIRType(LgsRuntime* runtime) override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    string getStrFormatPart() const override;
    bool equals(LgsType* other) override;
    ~LgsChar() override = default;
};

inline LgsChar LGS_CHAR;


