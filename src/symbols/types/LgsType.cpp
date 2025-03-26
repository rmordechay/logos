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
    const auto method = methods.find(funcCall->signature.name);
    if (method != methods.end()) {
        for (const auto& overload : method->second) {
            std::cout << overload->signature.composedName << '\n';
            std::cout << funcCall->signature.composedName << '\n';
            if (overload->signature.composedName == funcCall->signature.composedName) {
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
