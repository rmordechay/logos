#include "files/LgsMainFile.h"

size_t LgsMainFile::hashFile() {
    size_t hash = 0;
    HASH_MAP(funcs, hash);
    HASH_VECTOR(objects, hash);
    HASH_VECTOR(interfaces, hash);
    HASH_VECTOR(enums, hash);
    HASH_VECTOR(subtypes, hash);
    return hash;
}

LgsFunc* LgsMainFile::getMainFunc() {
    for (auto [name, func] : funcs) {
        if (name == LGS_MAIN_FUNC) return func;
    }
    return nullptr;
}

LgsMainFile::~LgsMainFile() {
    for (const auto& [_, func] : funcs) {
        delete func;
    }
    funcs.clear();
    for (const auto& object : objects) {
        freeType(object);
    }
    objects.clear();
    for (const auto lgsEnum : enums) {
        freeType(lgsEnum);
    }
    enums.clear();
}
