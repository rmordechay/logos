#include "files/LgsObjectFile.h"

#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsIOPair.h"
#include "types/LgsEnum.h"
#include "types/LgsGenericType.h"
#include "types/LgsSubType.h"

size_t LgsObjectFile::hashFile() {
    size_t hash = 0;
    hashNodeString(hash, obj->name);
    HASH_MAP(obj->methods, hash);
    HASH_VECTOR(obj->fields, hash);
    HASH_VECTOR(obj->implements, hash);
    HASH_VECTOR(obj->enums, hash);
    HASH_VECTOR(obj->objects, hash);
    HASH_VECTOR(obj->generics, hash);
    HASH_VECTOR(obj->subtypes, hash);
    HASH_VECTOR(obj->ioPairs, hash);
    return hash;
}

LgsObjectFile::~LgsObjectFile() {
    // Released in global table
    obj = nullptr;
}
