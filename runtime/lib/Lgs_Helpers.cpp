#include "Lgs_Helpers.h"
#include "Lgs_DArray.h"
#include "Lgs_Map.h"
#include "Lgs_Set.h"
#include "Lgs_Stack.h"
#include <cassert>

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

void funcCleanup(Lgs_Stack& stack) {
    auto& stackFrame = stack.frames[stack.stackIndex];
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