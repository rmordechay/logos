#include "Lgs_Set.h"
#include "Lgs_Types.h"

#include <cassert>
#include <cstdlib>
#include <cstring>

extern "C" void Lgs_Set_init(Lgs_Set* set, const size_t elementSize, const Lgs_TypeKind baseType) {
    assert(baseType != RTT_UNKNOWN);
    set->elementSize = elementSize;
    set->baseType = baseType;
    set->capacity = elementSize * 10;
    set->data = static_cast<char*>(std::malloc(set->capacity));
    set->size = 0;
}

extern "C" void Lgs_Set_reserve(Lgs_Set* set, const size_t numElements) {
    const auto newCapacity = numElements * set->elementSize;
    if (newCapacity <= set->capacity) return;
    set->data = static_cast<char*>(std::realloc(set->data, newCapacity));
    set->capacity = newCapacity;
}

static void resizeSetIfNeeded(Lgs_Set* set) {
    if (set->size + set->elementSize <= set->capacity) return;
    set->capacity *= 2;
    set->data = static_cast<char*>(std::realloc(set->data, set->capacity));
}

static bool elementsEqual(const void* elem1, const void* elem2, const size_t elementSize) {
    return std::memcmp(elem1, elem2, elementSize) == 0;
}

extern "C" bool Lgs_Set_add(Lgs_Set* set, const void* value) {
    const size_t len = set->size / set->elementSize;
    const char* base = set->data;
    for (size_t i = 0; i < len; ++i) {
        const void* elem = base + i * set->elementSize;
        if (elementsEqual(elem, value, set->elementSize)) {
            return false; // Element already exists
        }
    }
    resizeSetIfNeeded(set);
    std::memcpy(set->data + set->size, value, set->elementSize);
    set->size += set->elementSize;
    return true;
}

extern "C" bool Lgs_Set_contains(const Lgs_Set* set, const void* value) {
    if (set->size == 0) return false;
    const size_t len = set->size / set->elementSize;
    const char* base = set->data;
    for (size_t i = 0; i < len; ++i) {
        const void* elem = base + i * set->elementSize;
        if (elementsEqual(elem, value, set->elementSize)) {
            return true;
        }
    }
    return false;
}

extern "C" bool Lgs_Set_remove(Lgs_Set* set, const void* value) {
    assert(set);
    if (set->size == 0) return false;
    const size_t len = set->size / set->elementSize;
    char* base = set->data;
    for (size_t i = 0; i < len; ++i) {
        char* elem = base + i * set->elementSize;
        if (elementsEqual(elem, value, set->elementSize)) {
            // Shift remaining elements down
            const size_t remaining = set->size - (i + 1) * set->elementSize;
            if (remaining > 0) {
                std::memmove(elem, elem + set->elementSize, remaining);
            }
            set->size -= set->elementSize;
            return true;
        }
    }
    return false;
}

extern "C" void* Lgs_Set_get(const Lgs_Set* set, const size_t index) {
    if (!set || set->size == 0) return nullptr;
    const auto len = set->size / set->elementSize;
    if (index >= len) return nullptr;
    return set->data + index * set->elementSize;
}

extern "C" size_t Lgs_Set_len(const Lgs_Set* set) {
    return set->size / set->elementSize;
}

extern "C" bool Lgs_Set_isEmpty(const Lgs_Set* set) {
    return set->size == 0;
}

extern "C" bool Lgs_Set_isNotEmpty(const Lgs_Set* set) {
    return set->size != 0;
}

extern "C" void Lgs_Set_clear(Lgs_Set* set) {
    set->size = 0;
}