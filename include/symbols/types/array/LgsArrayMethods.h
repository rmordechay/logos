#ifndef LGSARRAYMETHODS_H
#define LGSARRAYMETHODS_H
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsVoid.h"
#include "funcs/LgsMethodImpl.h"
#include "exprs/LgsExpr.h"

class LgsArrayNewFunc final : public LgsMethodImpl {
public:
    LgsParam capacityParam{&LGS_INT};
    LgsParam elementSizeParam{&LGS_LONG};

    explicit LgsArrayNewFunc(LgsType* parent) : LgsMethodImpl("new", parent->getIRName(), &LGS_ANY) {
        funcType.params = {&capacityParam, &elementSizeParam};
        funcType.isStatic = true;
    }
};

class LgsArrayGetFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam indexParam{&LGS_INT};

    explicit LgsArrayGetFunc(LgsType* parent) : LgsMethodImpl("get", parent->getIRName(), &LGS_ANY) {
        self.type = parent;
        funcType.params = {&self, &indexParam};
    }
};

class LgsArrayAddFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam valueParam{&LGS_ANY};

    explicit LgsArrayAddFunc(LgsType* parent) : LgsMethodImpl("add", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        funcType.params = {&self, &valueParam};
        funcType.isPublic = true;
    }

    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override {
        auto& builder = metadata->builder;
        const auto arrPtr = args[0]->getIRValue(metadata);
        const auto elementValue = args[1]->getIRValue(metadata);
        const auto elementType = args[1]->type->getIRType();
        const auto elementPtr = builder.CreateAlloca(elementType);
        builder.CreateStore(elementValue, elementPtr);
        const auto arrPtrLoad = builder.CreateLoad(ptrTy, arrPtr);
        return callIR(metadata, {arrPtrLoad, elementPtr});
    }
};

class LgsArrayDeleteFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam indexParam{&LGS_INT};

    explicit LgsArrayDeleteFunc(LgsType* parent) : LgsMethodImpl("delete", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        funcType.params = {&self, &indexParam};
    }
};

class LgsArrayLenFunc final : public LgsMethodImpl {
public:
    LgsParam self{};

    explicit LgsArrayLenFunc(LgsType* parent) : LgsMethodImpl("len", parent->getIRName(), &LGS_INT) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
    }
};

class LgsArrayFreeFunc final : public LgsMethodImpl {
public:
    LgsParam self{};

    explicit LgsArrayFreeFunc(LgsType* parent) : LgsMethodImpl("free", parent->getIRName(), &LGS_INT) {
        self.type = parent;
        funcType.params = {&self};
    }
};

#endif //LGSARRAYMETHODS_H
