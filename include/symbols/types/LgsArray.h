#pragma once
#include "LgsAny.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsInt.h"
#include "primitives/LgsLong.h"
#include "primitives/LgsVoid.h"
#include "types/LgsIterable.h"

class LgsArray final : public LgsIterable {
public:
    static constexpr auto name = "Array";
    StructType* arrStruct = nullptr;
    LgsBuiltinFunc init{"init", &LGS_VOID, name, {LgsParam{this}, LgsParam{&LGS_INT}, LgsParam{&LGS_LONG}}};
    LgsBuiltinFunc get{"get", &LGS_ANY, name, {LgsParam{this}, LgsParam {&LGS_INT}}};
    LgsBuiltinFunc put{"put", &LGS_VOID, name, {LgsParam{this}, LgsParam{&LGS_INT}, LgsParam{&LGS_ANY}}};
    LgsBuiltinFunc add{"add", &LGS_VOID, name, {LgsParam{this}, LgsParam{&LGS_ANY}}};
    LgsBuiltinFunc delete_{"delete", &LGS_VOID, name, {LgsParam{this}, LgsParam{&LGS_INT}}};
    LgsBuiltinFunc len{"len", &LGS_INT, name, {LgsParam{this}}};
    LgsBuiltinFunc isEmpty{"isEmpty", &LGS_INT, name, {LgsParam{this}}};
    LgsBuiltinFunc isNotEmpty{"isNotEmpty", &LGS_INT, name, {LgsParam{this}}};
    LgsBuiltinFunc free{"free", &LGS_INT, name, {LgsParam{this}}};

    explicit LgsArray(LgsType* baseType = nullptr): LgsIterable(baseType) {
        unpackLength = 1;
        addMethod(&add);
        addMethod(&len);
        addMethod(&isEmpty);
        addMethod(&isNotEmpty);
    }
    size_t getSizeBytes() override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    void unpackTypes(const vector<LgsVarDec*>& varDecs) override;
    Value* getLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* getLoopLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    StructType* getArrStruct(LgsRuntime* runtime);
    LgsType* clone() override;
    ~LgsArray() override;
};
