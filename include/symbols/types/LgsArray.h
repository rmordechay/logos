#pragma once
#include "LgsAny.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsInt.h"
#include "primitives/LgsLong.h"
#include "primitives/LgsVoid.h"
#include "types/LgsIterable.h"

class LgsArrayAddFunc final : public LgsBuiltinFunc {
public:
    explicit LgsArrayAddFunc(LgsType* parent) : LgsBuiltinFunc("add", &LGS_VOID, parent->getIRName()) {
        funcType.isPublic = true;
        funcType.params = {LgsParam{parent}, LgsParam{&LGS_ANY}};
    }

    Value* call(LgsRuntime* runtime, const vector<LgsExpr*>& args) override {
        const auto arrPtr = args[0]->getIRValue(runtime);
        const auto elementValue = args[1]->getIRValue(runtime);
        const auto elementType = args[1]->type->getIRType();
        const auto elementPtr = runtime->builder.CreateAlloca(elementType);
        runtime->builder.CreateStore(elementValue, elementPtr);
        return callIR(runtime, {arrPtr, elementPtr});
    }
};

class LgsArray final : public LgsIterable {
public:
    static constexpr auto name = "Array";
    StructType* arrStruct = nullptr;
    LgsBuiltinFunc get{"get", &LGS_ANY, name, {this, &LGS_INT}, true};
    LgsArrayAddFunc add{this};
    LgsBuiltinFunc len{"len", &LGS_INT, name, {this}, true};
    LgsBuiltinFunc isEmpty{"isEmpty", &LGS_INT, name, {this}, true};
    LgsBuiltinFunc isNotEmpty{"isNotEmpty", &LGS_INT, name, {this}, true};
    LgsBuiltinFunc init{"init", &LGS_VOID, name, {this, &LGS_INT, &LGS_LONG}};
    LgsBuiltinFunc put{"put", &LGS_VOID, name, {this, &LGS_INT, &LGS_ANY}};
    LgsBuiltinFunc delete_{"delete", &LGS_VOID, name, {this, &LGS_INT}};
    LgsBuiltinFunc free{"free", &LGS_VOID, name, {this}};

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
