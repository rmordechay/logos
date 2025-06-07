#ifndef LGSMAPMETHODS_H
#define LGSMAPMETHODS_H
#include "funcs/LgsBuiltinFunc.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"
#include "types/LgsStr.h"
#include "types/primitives/LgsVoid.h"

class LgsMapInitFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};
    LgsParam valueSizeParam{&LGS_INT};

    explicit LgsMapInitFunc(LgsType* parent) : LgsBuiltinFunc("init", &LGS_VOID, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self, &valueSizeParam};
    }
};

class LgsMapGetFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};
    LgsParam keyParam{new LgsStr()};

    explicit LgsMapGetFunc(LgsType* parent) : LgsBuiltinFunc("get", &LGS_ANY, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self, &keyParam};
    }
};

class LgsMapAddFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};
    LgsParam keyParam{new LgsStr()};
    LgsParam valueParam{&LGS_ANY};

    explicit LgsMapAddFunc(LgsType* parent) : LgsBuiltinFunc("add", &LGS_VOID, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self, &keyParam, &valueParam};
        funcType.isPublic = true;
    }
};

class LgsMapDeleteFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};

    explicit LgsMapDeleteFunc(LgsType* parent) : LgsBuiltinFunc("delete", &LGS_VOID, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self};
    }
};

class LgsMapLenFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};

    explicit LgsMapLenFunc(LgsType* parent) : LgsBuiltinFunc("len", &LGS_INT, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
    }
};

class LgsMapIsEmptyFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};

    explicit LgsMapIsEmptyFunc(LgsType* parent) : LgsBuiltinFunc("isEmpty", &LGS_INT, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
    }
};

class LgsMapIsNotEmptyFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};

    explicit LgsMapIsNotEmptyFunc(LgsType* parent) : LgsBuiltinFunc("isNotEmpty", &LGS_INT, parent->getIRName()) {
        self.type = parent;
        funcType.params = {&self};
        funcType.isPublic = true;
    }
};

#endif //LGSMAPMETHODS_H