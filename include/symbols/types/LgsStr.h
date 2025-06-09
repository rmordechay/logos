#pragma once
#include "LgsAny.h"
#include "funcs/LgsBuiltinFunc.h"
#include "types/LgsIterable.h"

class LgsStrFormatFunc final : public LgsBuiltinFunc {
public:
    explicit LgsStrFormatFunc(LgsType* parent) : LgsBuiltinFunc("format", parent, parent->getIRName(), {parent, &LGS_ANY}, true, true) {}
    Value* call(LgsRuntime* runtime, const vector<LgsExpr*>& args) override;
};

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    LgsStrFormatFunc format{this};
    LgsBuiltinFunc len{"len", &LGS_INT, name, {this}};
    LgsBuiltinFunc isEmpty{"isEmpty", &LGS_INT, name, {this}};
    LgsBuiltinFunc isNotEmpty{"isNotEmpty", &LGS_INT, name, {this}};

    LgsStr() : LgsIterable(&LGS_CHAR) {
        addMethod(&format);
        addMethod(&len);
        addMethod(&isEmpty);
        addMethod(&isNotEmpty);
        unpackLength = 1;
    }
    static uint32_t hashString(const string& str);
    size_t getSizeBytes() override;
    string getIRName() override;
    Type* getIRType() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    string getStrFormatPart() const override;
    Value* getLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* getLoopLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    ~LgsStr() override = default;
};
