#include "files/LgsMainFile.h"

#include <utility>

#include "LgsUtils.h"
#include "stmts/LgsVarDec.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsStmt.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsSubType.h"

size_t LgsMainFile::hashFile() {
    size_t hash = 0;
    HASH_MAP(funcs, hash);
    HASH_VECTOR(objects, hash);
    HASH_VECTOR(interfaces, hash);
    HASH_VECTOR(enums, hash);
    HASH_VECTOR(subtypes, hash);
    return hash;
}

LgsMainFile::~LgsMainFile() {
    for (const auto& [_, func] : funcs) {
        delete func;
    }
    funcs.clear();
    for (const auto& varDec : varDecs) {
        freeStmt(varDec);
    }
    varDecs.clear();
    for (const auto& object : objects) {
        delete object;
    }
    objects.clear();
    for (const auto& interface : interfaces) {
        delete interface;
    }
    interfaces.clear();
    for (const auto enum_ : enums) {
        delete enum_;
    }
    enums.clear();
    for (const auto subtype : subtypes) {
        delete subtype;
    }
    subtypes.clear();
}
