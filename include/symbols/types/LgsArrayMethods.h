#ifndef LGSARRAYMETHODS_H
#define LGSARRAYMETHODS_H
#include "LgsAny.h"
#include "LgsInt.h"
#include "LgsLong.h"
#include "LgsVoid.h"
#include "funcs/LgsMethodImpl.h"
#include "exprs/LgsExpr.h"

class LgsArrayNewFunc final : public LgsMethodImpl {
public:
    LgsParam capacityParam{&LGS_INT};
    LgsParam elementSizeParam{&LGS_LONG};

    explicit LgsArrayNewFunc(LgsType* parent) : LgsMethodImpl("new", parent->getIRName(), &LGS_ANY) {
        methodType.params = {&capacityParam, &elementSizeParam};
        isStatic = true;
    }
};

class LgsArrayGetFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam indexParam{&LGS_INT};

    explicit LgsArrayGetFunc(LgsType* parent) : LgsMethodImpl("get", parent->getIRName(), &LGS_ANY) {
        self.type = parent;
        methodType.params = {&self, &indexParam};
    }
};

class LgsArrayAddFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam valueParam{&LGS_ANY};

    explicit LgsArrayAddFunc(LgsType* parent) : LgsMethodImpl("add", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        methodType.params = {&self, &valueParam};
        isPublic = true;
    }

    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args, Value* callback = nullptr) override {
        auto& builder = metadata->builder;
        const auto arrPtr = args[0]->getIRValue(metadata);
        const auto arrPtrLoad = builder.CreateLoad(ptrTy, arrPtr);
        const auto element = args[1];
        const auto elementType = element->type->getIRType();
        const auto valurPtr = builder.CreateAlloca(elementType);
        builder.CreateStore(element->getIRValue(metadata), valurPtr);
        return LgsMethodImpl::makeCall(metadata, {arrPtrLoad, valurPtr});
    }
};

class LgsArrayDeleteFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam indexParam{&LGS_INT};

    explicit LgsArrayDeleteFunc(LgsType* parent) : LgsMethodImpl("delete", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        methodType.params = {&self, &indexParam};
    }
};

class LgsArrayLenFunc final : public LgsMethodImpl {
public:
    LgsParam self{};

    explicit LgsArrayLenFunc(LgsType* parent) : LgsMethodImpl("len", parent->getIRName(), &LGS_INT) {
        self.type = parent;
        methodType.params = {&self};
        isPublic = true;
    }
};

#endif //LGSARRAYMETHODS_H
