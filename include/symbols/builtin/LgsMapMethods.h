#ifndef LGSMAPMETHODS_H
#define LGSMAPMETHODS_H
#include "LgsBuiltinMethod.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"
#include "../types/LgsStr.h"
#include "types/primitives/LgsVoid.h"
#include "funcs/LgsMethodImpl.h"

class LgsMapInitFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};
    LgsParam valueSizeParam{&LGS_INT};

    explicit LgsMapInitFunc(LgsType* parent) : LgsBuiltinMethod("init", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        funcType.params = {&self, &valueSizeParam};
    }
};

class LgsMapGetFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};
    LgsParam keyParam{new LgsStr()};

    explicit LgsMapGetFunc(LgsType* parent) : LgsBuiltinMethod("get", parent->getIRName(), &LGS_ANY) {
        self.type = parent;
        funcType.params = {&self, &keyParam};
    }
};

class LgsMapAddFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};
    LgsParam keyParam{new LgsStr()};
    LgsParam valueParam{&LGS_ANY};

    explicit LgsMapAddFunc(LgsType* parent) : LgsBuiltinMethod("add", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        funcType.params = {&self, &keyParam, &valueParam};
        funcType.isPublic = true;
    }
};

class LgsMapDeleteFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};

    explicit LgsMapDeleteFunc(LgsType* parent) : LgsBuiltinMethod("delete", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        funcType.params = {&self};
    }
};

class LgsMapLenFunc final : public LgsBuiltinMethod {
public:
    LgsParam self{};

    explicit LgsMapLenFunc(LgsType* parent) : LgsBuiltinMethod("len", parent->getIRName(), &LGS_INT) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
    }
};

#endif //LGSMAPMETHODS_H