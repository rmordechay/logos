#ifndef LGSARRAYMETHODS_H
#define LGSARRAYMETHODS_H
#include "LgsBuiltinFunc.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsVoid.h"

class LgsArrayInitFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};
    LgsParam capacityParam{&LGS_INT};
    LgsParam elementSizeParam{&LGS_LONG};

    explicit LgsArrayInitFunc(LgsType* parent) : LgsBuiltinFunc("init", &LGS_VOID, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self, &capacityParam, &elementSizeParam};
    }
};

class LgsArrayGetFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};
    LgsParam indexParam{&LGS_INT};

    explicit LgsArrayGetFunc(LgsType* parent) : LgsBuiltinFunc("get", &LGS_ANY, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self, &indexParam};
    }
};

class LgsArrayPutFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};
    LgsParam indexParam{&LGS_INT};
    LgsParam valueParam{&LGS_ANY};

    explicit LgsArrayPutFunc(LgsType* parent) : LgsBuiltinFunc("put", &LGS_VOID, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self, &indexParam, &valueParam};
    }
};

class LgsArrayAddFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};
    LgsParam valueParam{&LGS_ANY};

    explicit LgsArrayAddFunc(LgsType* parent) : LgsBuiltinFunc("add", &LGS_VOID, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self, &valueParam};
        funcType.isPublic = true;
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

class LgsArrayDeleteFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};
    LgsParam indexParam{&LGS_INT};

    explicit LgsArrayDeleteFunc(LgsType* parent) : LgsBuiltinFunc("delete", &LGS_VOID, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self, &indexParam};
    }
};

class LgsArrayLenFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};

    explicit LgsArrayLenFunc(LgsType* parent) : LgsBuiltinFunc("len", &LGS_INT, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
    }
};

class LgsArrayIsEmptyFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};

    explicit LgsArrayIsEmptyFunc(LgsType* parent) : LgsBuiltinFunc("isEmpty", &LGS_INT, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
    }
};

class LgsArrayIsNotEmptyFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};

    explicit LgsArrayIsNotEmptyFunc(LgsType* parent) : LgsBuiltinFunc("isNotEmpty", &LGS_INT, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
    }
};

class LgsArrayFreeFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};

    explicit LgsArrayFreeFunc(LgsType* parent) : LgsBuiltinFunc("free", &LGS_INT, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self};
    }
};

#endif //LGSARRAYMETHODS_H
