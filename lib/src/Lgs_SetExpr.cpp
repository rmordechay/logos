#include "Lgs_SetExpr.h"
#include "Lgs_Types.h"
#include <cassert>
#include <cstdlib>
#include <cstring>

static void resizeSetIfNeeded(Lgs_SetExpr* set);

extern "C" void Lgs_Set_init(Lgs_SetExpr* set, Lgs_TypeInfo* baseType) {
    assert(baseType->kind != RTT_UNKNOWN);
    set->baseType = baseType;
    set->capacity = 10;
    set->data = static_cast<char*>(std::malloc(set->capacity * baseType->size));
    set->length = 0;
}

extern "C" bool Lgs_Set_add(Lgs_SetExpr* set, const void* value) {
    assert(set);
    const auto count = set->length;
    const auto elemSize = set->baseType->size;
    for (size_t i = 0; i < count; ++i) {
        const void* elem = set->data + i * elemSize;
        if (std::memcmp(elem, value, elemSize) == 0) return false;
    }
    resizeSetIfNeeded(set);
    std::memcpy(set->data + set->length * elemSize, value, elemSize);
    set->length += 1;
    return true;
}

extern "C" bool Lgs_Set_contains(const Lgs_SetExpr* set, const void* value) {
    assert(set);
    const auto count = set->length;
    const auto elemSize = set->baseType->size;
    for (size_t i = 0; i < count; ++i) {
        const void* elem = set->data + i * elemSize;
        if (std::memcmp(elem, value, elemSize) == 0) return true;
    }
    return false;
}

extern "C" bool Lgs_Set_remove(Lgs_SetExpr* set, const void* value) {
    assert(set);
    const auto count = set->length;
    const auto elemSize = set->baseType->size;
    for (size_t i = 0; i < count; ++i) {
        char* elem = set->data + i * elemSize;
        if (memcmp(elem, value, elemSize) == 0) {
            const auto remaining = (count - i - 1) * elemSize;
            if (remaining > 0) {
                std::memmove(elem, elem + elemSize, remaining);
            }
            set->length -= 1;
            return true;
        }
    }
    return false;
}

extern "C" void* Lgs_Set_get(const Lgs_SetExpr* set, const size_t index) {
    if (!set || index >= set->length) return nullptr;
    return set->data + index * set->baseType->size;
}

extern "C" size_t Lgs_Set_len(const Lgs_SetExpr* set) {
    return set->length;
}

extern "C" bool Lgs_Set_isEmpty(const Lgs_SetExpr* set) {
    return set->length == 0;
}

extern "C" bool Lgs_Set_isNotEmpty(const Lgs_SetExpr* set) {
    return set->length != 0;
}

extern "C" void Lgs_Set_clear(Lgs_SetExpr* set) {
    set->length = 0;
}

static void resizeSetIfNeeded(Lgs_SetExpr* set) {
    if (set->length < set->capacity) return;
    set->capacity *= 2;
    set->data = static_cast<char*>(
        std::realloc(set->data, set->capacity * set->baseType->size)
    );
}
