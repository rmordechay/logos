#ifndef LGSMAPMETHODS_H
#define LGSMAPMETHODS_H
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"
#include "../types/LgsStr.h"
#include "types/primitives/LgsVoid.h"
#include "funcs/LgsMethodImpl.h"

class LgsMapInitFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam valueSizeParam{&LGS_INT};

    explicit LgsMapInitFunc(LgsType* parent) : LgsMethodImpl("init", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        funcType.params = {&self, &valueSizeParam};
    }
};

class LgsMapGetFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam keyParam{new LgsStr()};

    explicit LgsMapGetFunc(LgsType* parent) : LgsMethodImpl("get", parent->getIRName(), &LGS_ANY) {
        self.type = parent;
        funcType.params = {&self, &keyParam};
    }
};

class LgsMapAddFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam keyParam{new LgsStr()};
    LgsParam valueParam{&LGS_ANY};

    explicit LgsMapAddFunc(LgsType* parent) : LgsMethodImpl("add", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        funcType.params = {&self, &keyParam, &valueParam};
        funcType.isPublic = true;
        IRGenerated = true;
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
        IRGenerated = true;
    }
};

#endif //LGSMAPMETHODS_H