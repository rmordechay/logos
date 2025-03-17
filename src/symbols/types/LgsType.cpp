#include "types/LgsType.h"

#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"

LgsField* LgsType::getField(const string& name) {
    const auto it = fields.find(name);
    if (it != fields.end()) {
        return it->second;
    }
    return nullptr;
}

LgsMethodImpl* LgsType::getMethod(const string& name) {
    const auto it = methods.find(name);
    if (it != methods.end()) {
        return it->second;
    }
    return nullptr;
}

Type* LgsType::getIRType() {
    assert(false && "iterable type has no size");
}

Type* LgsType::getIRType(int size) {
    assert(false && "primitive type has no size");
}
