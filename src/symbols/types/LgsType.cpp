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

LgsMethodImpl* LgsType::getMethod(const string& name, const string& composedName) const {
    assert(composedName != "");
    const auto overloads = getMethodsOverloads(name);
    for (const auto& overload : overloads) {
        if (overload->signature.composedName == composedName) {
            return overload;
        }
    }
    return nullptr;
}

vector<LgsMethodImpl*> LgsType::getMethodsOverloads(const string& funcName) const {
    const auto method = methods.find(funcName);
    if (method != methods.end()) {
        return method->second;
    }
    return {};
}

Type* LgsType::getIRType() {
    std::cerr << "Type '" << getName() << "' has no IR type" << std::endl;
    assert(false);
}

Type* LgsType::getIRType(int size) {
    assert(false && "type has no IR type");
}
