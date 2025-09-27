#include "Lgs_set.h"
#include "data/LgsErrors.h"
#include "utils/LgsUtils.h"
#include <cstring>

extern "C" void Lgs_Set_init(Lgs_set* set, const size_t elementSize) {
    set->elementSize = elementSize;
    set->data = new std::vector<char>();
}

extern "C" bool Lgs_Set_contains(const Lgs_set* set, const void* value) {
    if (!set || !set->data || set->data->empty()) return false;
    const size_t len = set->data->size() / set->elementSize;
    const char* base = set->data->data();
    for (size_t i = 0; i < len; ++i) {
        const void* elem = base + i * set->elementSize;
        if (std::memcmp(elem, value, set->elementSize) == 0) {
            return true;
        }
    }
    return false;
}

extern "C" bool Lgs_Set_add(const Lgs_set* set, const void* value) {
    assert(set->elementSize <= MAX_ELEMENT_SIZE);
    if (Lgs_Set_contains(set, value)) return false;
    const auto oldSize = set->data->size();
    set->data->resize(oldSize + set->elementSize);
    std::memcpy(set->data->data() + oldSize, value, set->elementSize);
    return true;
}

extern "C" bool Lgs_Set_remove(const Lgs_set* set, const void* value) {
    if (!set || !set->data || set->data->empty()) return false;
    const size_t len = set->data->size() / set->elementSize;
    const char* base = set->data->data();
    for (size_t i = 0; i < len; ++i) {
        const void* elem = base + i * set->elementSize;
        if (std::memcmp(elem, value, set->elementSize) == 0) {
            // Found element, remove it by moving last element to this position
            if (i < len - 1) {
                const void* lastElem = base + (len - 1) * set->elementSize;
                std::memcpy(const_cast<char*>(base) + i * set->elementSize, lastElem, set->elementSize);
            }
            set->data->resize(set->data->size() - set->elementSize);
            return true;
        }
    }
    return false;
}

extern "C" void* Lgs_Set_get(const Lgs_set* set, const size_t index) {
    if (!set || !set->data) return nullptr;
    const auto len = set->data->size() / set->elementSize;
    if (index >= len) {
        formatAndLogError(E10080, {std::to_string(index)});
        return nullptr;
    }
    return set->data->data() + index * set->elementSize;
}

extern "C" size_t Lgs_Set_size(const Lgs_set* set) {
    return set->data->size() / set->elementSize;
}

extern "C" bool Lgs_Set_isEmpty(const Lgs_set* set) {
    return set->data->empty();
}

extern "C" bool Lgs_Set_isNotEmpty(const Lgs_set* set) {
    return !set->data->empty();
}

extern "C" void Lgs_Set_clear(const Lgs_set* set) {
    set->data->clear();
}

extern "C" size_t Lgs_Set_len(const Lgs_set* set) {
    return set->data->size() / set->elementSize;
}
