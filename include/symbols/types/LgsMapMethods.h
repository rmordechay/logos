#ifndef METHODS_H
#define METHODS_H
#include "LgsAny.h"
#include "LgsInt.h"
#include "LgsVoid.h"
#include "funcs/LgsMethodImpl.h"

class LgsMapGetFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam keyParam{&LGS_ANY};

    explicit LgsMapGetFunc(LgsType* parent) : LgsMethodImpl("get", parent->getIRName(), &LGS_ANY) {
        self.type = parent;
        methodType.params = {&self, &keyParam};
    }
};

class LgsMapInsertFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam keyParam{&LGS_ANY};
    LgsParam valueParam{&LGS_ANY};

    explicit LgsMapInsertFunc(LgsType* parent) : LgsMethodImpl("insert", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        methodType.params = {&self, &keyParam, &valueParam};
    }
};

class LgsMapDeleteFunc final : public LgsMethodImpl {
public:
    LgsParam self{};

    explicit LgsMapDeleteFunc(LgsType* parent) : LgsMethodImpl("delete", parent->getIRName(), &LGS_VOID) {
        self.type = parent;
        methodType.params = {&self};
    }
};

class LgsMapLenFunc final : public LgsMethodImpl {
public:
    LgsParam self{};

    explicit LgsMapLenFunc(LgsType* parent) : LgsMethodImpl("len", parent->getIRName(), &LGS_INT) {
        self.type = parent;
        methodType.params = {&self};
        isPublic = true;
    }
};

#endif //METHODS_H