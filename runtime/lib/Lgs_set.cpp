#include "Lgs_set.h"
#include "Lgs_types.h"
#include <cstring>

extern "C" void Lgs_set_init(Lgs_set* set, const size_t elementSize, const Lgs_rttype baseType) {
    assert(baseType != RTT_UNKNOWN);
    set->elementSize = elementSize;
    set->baseType = baseType;
    set->capacity = elementSize * 10;
    set->data = static_cast<char*>(malloc(set->capacity));
    set->size = 0;
}

extern "C" void Lgs_set_reserve(Lgs_set* set, const size_t numElements) {
    const auto newCapacity = numElements * set->elementSize;
    if (newCapacity <= set->capacity) return;
    set->data = static_cast<char*>(realloc(set->data, newCapacity));
    set->capacity = newCapacity;
}

static void resizeSetIfNeeded(Lgs_set* set) {
    if (set->size + set->elementSize <= set->capacity) return;
    set->capacity *= 2;
    set->data = static_cast<char*>(realloc(set->data, set->capacity));
}

static bool elementsEqual(const void* elem1, const void* elem2, const size_t elementSize) {
    return std::memcmp(elem1, elem2, elementSize) == 0;
}

extern "C" bool Lgs_set_add(Lgs_set* set, const void* value) {
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

extern "C" bool Lgs_set_contains(const Lgs_set* set, const void* value) {
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

extern "C" bool Lgs_set_remove(Lgs_set* set, const void* value) {
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

extern "C" void* Lgs_set_get(const Lgs_set* set, const size_t index) {
    if (!set || set->size == 0) return nullptr;
    const auto len = set->size / set->elementSize;
    if (index >= len) return nullptr;
    return set->data + index * set->elementSize;
}

extern "C" size_t Lgs_set_len(const Lgs_set* set) {
    return set->size / set->elementSize;
}

extern "C" bool Lgs_set_isEmpty(const Lgs_set* set) {
    return set->size == 0;
}

extern "C" bool Lgs_set_isNotEmpty(const Lgs_set* set) {
    return set->size != 0;
}

extern "C" void Lgs_set_clear(Lgs_set* set) {
    set->size = 0;
}