#pragma once


using namespace std;

class LgsVoid final : public LgsType {
public:
    static constexpr auto name = "Void";

    LgsVoid() {
        isVoid = true;
        isPrimitive = true;
    }
    string prettyName() const override;
    Type* getIRType(LgsRuntime* runtime) override;
    size_t getSizeBytes() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    ~LgsVoid() override = default;
};

inline LgsVoid LGS_VOID;


