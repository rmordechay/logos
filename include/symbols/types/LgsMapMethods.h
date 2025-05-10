#ifndef METHODS_H
#define METHODS_H
#include "LgsAny.h"
#include "LgsInt.h"
#include "LgsStr.h"
#include "LgsVoid.h"
#include "funcs/LgsMethodImpl.h"

class LgsMapNewFunc final : public LgsMethodImpl {
public:
    LgsParam valueSizeParam{&LGS_INT};

    explicit LgsMapNewFunc(LgsType* parent) : LgsMethodImpl("new", parent->getIRName(), &LGS_ANY) {
        funcType.params = {&valueSizeParam};
    }
};

class LgsMapGetFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam keyParam{&LGS_STR};

    explicit LgsMapGetFunc(LgsType* parent) : LgsMethodImpl("get", parent->getIRName(), &LGS_ANY) {
        self.type = parent;
        funcType.params = {&self, &keyParam};
    }
};

class LgsMapAddFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam keyParam{&LGS_STR};
    LgsParam valueParam{&LGS_ANY};

    explicit LgsMapAddFunc(LgsType* parent) : LgsMethodImpl("add", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        funcType.params = {&self, &keyParam, &valueParam};
    }

    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override {
        auto& builder = metadata->builder;
        const auto map = args[0];
        const auto key = args[1];
        const auto value = args[2];
        const auto keyType = key->type->getIRType();
        const auto valueType = value->type->getIRType();
        const auto mapPtr = map->getIRValue(metadata);

        const auto valuePtr = builder.CreateAlloca(valueType);
        const auto keyIRValue = key->getIRValue(metadata);
        const auto valueIRValue = value->getIRValue(metadata);
        builder.CreateStore(valueIRValue, valuePtr);
        const auto mapPtrLoad = builder.CreateLoad(keyType, mapPtr);
        return LgsMethodImpl::makeCall(metadata, {mapPtrLoad, keyIRValue, valuePtr});
    }
};

class LgsMapDeleteFunc final : public LgsMethodImpl {
public:
    LgsParam self{};

    explicit LgsMapDeleteFunc(LgsType* parent) : LgsMethodImpl("delete", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        funcType.params = {&self};
    }
};

class LgsMapLenFunc final : public LgsMethodImpl {
public:
    LgsParam self{};

    explicit LgsMapLenFunc(LgsType* parent) : LgsMethodImpl("len", parent->getIRName(), &LGS_INT) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
    }
};

#endif //METHODS_H