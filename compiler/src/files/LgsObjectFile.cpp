#include "files/LgsObjectFile.h"

#include "LgsUtils.h"
#include "stmts/LgsIOPair.h"
#include "types/LgsEnum.h"
#include "types/LgsGenericType.h"
#include "types/LgsObject.h"
#include "types/LgsSubType.h"

size_t LgsObjectFile::hashFile() {
    size_t hash = 0;
    hashNodeString(hash, obj->name);
    HASH_MAP(obj->methods, hash);
    HASH_VECTOR(obj->fields, hash);
    HASH_VECTOR(obj->implements, hash);
    HASH_VECTOR(obj->enums, hash);
    HASH_VECTOR(obj->objects, hash);
    HASH_VECTOR(obj->genericTypes, hash);
    HASH_VECTOR(obj->subtypes, hash);
    HASH_VECTOR(obj->ioPairs, hash);
    return hash;
}

LgsObjectFile::~LgsObjectFile() {
    // Object is released in global table
    obj = nullptr;
}
