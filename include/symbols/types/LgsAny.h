#pragma once


class LgsAny final : public LgsType {
public:
    static constexpr auto name = "Any";

    size_t getSizeBytes() override;
    Type* getIRType(LgsRuntime* runtime) override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsAny() override = default;
};

inline LgsAny LGS_ANY;


