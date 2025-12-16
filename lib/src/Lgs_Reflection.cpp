#include "LgsUtils.h"
#include "Lgs_Types.h"
struct Lgs_TypeInfo;

extern "C" void* Lgs_getObjectField(const Lgs_TypeInfo* typeInfo, void* ptr, const char* name) {
    size_t offset = 0;
    for (int i = 0; i < typeInfo->obj.fieldsCount; ++i) {
        const auto hash1 = typeInfo->obj.fieldNames[i];
        const auto fieldType = typeInfo->obj.fieldTypes[i];
        void* fieldPtr = static_cast<char*>(ptr) + offset;
        offset += fieldType->size;
        if (std::strcmp(hash1, name) == 0) {
            return fieldPtr;
        }
    }
    return nullptr;
}
