#pragma once
#include "LgsAny.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsChar.h"
#include "types/LgsIterable.h"

class LgsStrFormatFunc final : public LgsBuiltinFunc {
public:
    explicit LgsStrFormatFunc(LgsType* parent) : LgsBuiltinFunc("format", parent, parent->getIRName(), {parent, &LGS_ANY}, true, true) {}
    Value* call(LgsRuntime* runtime, const vector<LgsExpr*>& args) override;
};

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    LgsStrFormatFunc formatFunc{this};
    LgsBuiltinFunc lenFunc{"len", &LGS_LONG, name, {this}};
    LgsBuiltinFunc isEmptyFunc{"isEmpty", &LGS_BOOL, name, {this}};
    LgsBuiltinFunc isNotEmptyFunc{"isNotEmpty", &LGS_BOOL, name, {this}};

    LgsStr() : LgsIterable(&LGS_CHAR) {
        addMethod(&formatFunc);
        addMethod(&lenFunc);
        addMethod(&isEmptyFunc);
        addMethod(&isNotEmptyFunc);
        unpackLength = 1;
    }
    static size_t hashString(const string& str);
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
