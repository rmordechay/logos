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
            std::cout << "overload: " + overload->signature.composedName << '\n';
            std::cout << "funcCall: " + funcCall->signature.composedName << '\n';
            std::cout << "---" << '\n';
            if (overload->signature.composedName == funcCall->signature.composedName) {
                return overload;
            }
        }
    }
    return nullptr;
}

Type* LgsType::getIRType() {
    const auto message = "Type: " + getName();
    std::cerr << message << std::endl;
    assert(false && "type has no IR type");
}

Type* LgsType::getIRType(int size) {
    assert(false && "type has no IR type");
}
