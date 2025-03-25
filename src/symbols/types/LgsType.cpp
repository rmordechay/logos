#include "types/LgsType.h"

#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"

LgsField* LgsType::getField(const string& name) {
    const auto it = fields.find(name);
    if (it != fields.end()) {
        return it->second;
    }
    return nullptr;
}

LgsMethodImpl* LgsType::getMethod(const LgsFuncCall* funcCall) {
    const auto func = methods.find(funcCall->name);
    if (func != methods.end()) {
        for (const auto& overload : func->second) {
            if (overload->composedName == funcCall->composedName) {
                return overload;
            }
        }
    }
    return nullptr;
}

Type* LgsType::getIRType() {
    assert(false && "iterable type has no size");
}

Type* LgsType::getIRType(int size) {
    assert(false && "primitive type has no size");
}
