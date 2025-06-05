#ifndef LGSARRAYMETHODS_H
#define LGSARRAYMETHODS_H
#include "LgsBuiltinMethod.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsVoid.h"

class LgsArrayInitFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};
    LgsParam capacityParam{&LGS_INT};
    LgsParam elementSizeParam{&LGS_LONG};

    explicit LgsArrayInitFunc(LgsType* parent) : LgsBuiltinMethod("init", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        funcType.params = {&self, &capacityParam, &elementSizeParam};
        funcType.isStatic = true;
    }
};

class LgsArrayGetFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};
    LgsParam indexParam{&LGS_INT};

    explicit LgsArrayGetFunc(LgsType* parent) : LgsBuiltinMethod("get", parent->getIRName(), &LGS_ANY) {
        self.type = parent;
        funcType.params = {&self, &indexParam};
    }
};

class LgsArrayPutFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};
    LgsParam indexParam{&LGS_INT};
    LgsParam valueParam{&LGS_ANY};

    explicit LgsArrayPutFunc(LgsType* parent) : LgsBuiltinMethod("put", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        funcType.params = {&self, &indexParam, &valueParam};
    }
};

class LgsArrayAddFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};
    LgsParam valueParam{&LGS_ANY};

    explicit LgsArrayAddFunc(LgsType* parent) : LgsBuiltinMethod("add", parent->getIRName(), &LGS_VOID) {
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

class LgsArrayDeleteFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};
    LgsParam indexParam{&LGS_INT};

    explicit LgsArrayDeleteFunc(LgsType* parent) : LgsBuiltinMethod("delete", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        funcType.params = {&self, &indexParam};
    }
};

class LgsArrayLenFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};

    explicit LgsArrayLenFunc(LgsType* parent) : LgsBuiltinMethod("len", parent->getIRName(), &LGS_INT) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
    }
};

class LgsArrayIsEmptyFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};

    explicit LgsArrayIsEmptyFunc(LgsType* parent) : LgsBuiltinMethod("isEmpty", parent->getIRName(), &LGS_INT) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
        funcType.IRName = parent->getIRName() + "_is_empty";
    }
};

class LgsArrayIsNotEmptyFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};

    explicit LgsArrayIsNotEmptyFunc(LgsType* parent) : LgsBuiltinMethod("isNotEmpty", parent->getIRName(), &LGS_INT) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
        funcType.IRName = parent->getIRName() + "_is_not_empty";
    }
};

class LgsArrayFreeFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};

    explicit LgsArrayFreeFunc(LgsType* parent) : LgsBuiltinMethod("free", parent->getIRName(), &LGS_INT) {
        self.type = parent;
        funcType.params = {&self};
    }
};

#endif //LGSARRAYMETHODS_H
