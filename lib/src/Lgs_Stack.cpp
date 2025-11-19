#include "Lgs_Stack.h"

void Lgs_Stack::addDefer(void* funcPtr, void* ctx) {
    const auto deferFunc = reinterpret_cast<ThunkFunc>(funcPtr);
    const auto deferIndex = frames[stackIndex].defersCount++;
    frames[stackIndex].defers[deferIndex] = Lgs_ThunkFunc{deferFunc, ctx};
}

void Lgs_Stack::callDefers() const {
    const auto& top = frames[stackIndex];
    for (size_t i = 0; i < LOCALS_CAPACITY; ++i) {
        const auto [func, ctx] = top.defers[i];
        if (!func) continue;
        func(ctx);
    }
}

void Lgs_Stack::addOwner(void* ptr, const Lgs_TypeKind type) {
    const auto ownerIndex = frames[stackIndex].ownersCount++;
    frames[stackIndex].owners[ownerIndex] = Lgs_Alloc{ptr, type};
}

void Lgs_Stack::addOrphan(void* ptr, const Lgs_TypeKind type) {
    const auto ownerIndex = frames[stackIndex].orphansCount++;
    frames[stackIndex].orphans[ownerIndex] = Lgs_Alloc{ptr, type};
}

void freeValue(void* ptr, const Lgs_TypeKind type) {
    switch (type) {
    case RTT_OBJECT: {
        // std::free(ptr);
        break;
    }
    case RTT_DARRAY: {
        const auto arr = static_cast<Lgs_DArray*>(ptr);
        // free(arr->data);
        break;
    }
    case RTT_SET: {
        const auto arr = static_cast<Lgs_Set*>(ptr);
        // delete arr->data;
        // std::free(arr);
        break;
    }
    case RTT_MAP: {
        const auto map = static_cast<Lgs_Map*>(ptr);
        // delete map->data;
        // std::free(map);
        break;
    }
    default:
        break;
    }
}

void Lgs_Stack::removeOwner(const void* owner) {
    auto& stackFrame = frames[stackIndex];
    for (size_t i = 0; i < stackFrame.ownersCount; i++) {
        if (stackFrame.owners[i].ptr != owner) continue;
        freeValue(stackFrame.owners[i].ptr, stackFrame.owners[i].type);
        for (size_t j = i; j < stackFrame.ownersCount - 1; j++) {
            stackFrame.owners[j] = stackFrame.owners[j + 1];
        }
        break;
    }
}

void Lgs_Stack::push() {
    stackIndex++;
}

void Lgs_Stack::pop(const bool cleanup) {
    if (cleanup) funcCleanup();
    stackIndex--;
}

void Lgs_Stack::funcCleanup() {
    auto& stackFrame = frames[stackIndex];
    if (stackFrame.ownersCount > 0) {
        for (size_t i = 0; i < stackFrame.ownersCount; i++) {
            freeValue(stackFrame.owners[i].ptr, stackFrame.owners[i].type);
        }
        stackFrame.ownersCount = 0;
    }
    if (stackFrame.orphansCount > 0) {
        for (size_t i = 0; i < stackFrame.orphansCount; i++) {
            freeValue(stackFrame.orphans[i].ptr, stackFrame.orphans[i].type);
        }
        stackFrame.orphansCount = 0;
    }
}