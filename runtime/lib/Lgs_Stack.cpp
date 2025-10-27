#include "Lgs_Stack.h"
#include "Lgs_DArray.h"
#include "Lgs_Set.h"
#include "Lgs_Map.h"

#include <cassert>
#include <iostream>

#define PRINT_MEMORY false

static std::string getTypeName(const Lgs_rttype type) {
    switch (type) {
    case RTT_UNKNOWN: return "<Unknown>";
    case RTT_VOID: return "Void";
    case RTT_BOOL: return "Bool";
    case RTT_CHAR: return "Char";
    case RTT_STR: return "Str";
    case RTT_BYTE: return "Byte";
    case RTT_SHORT: return "Short";
    case RTT_INT: return "Int";
    case RTT_LONG: return "Long";
    case RTT_SIZE: return "Size";
    case RTT_UBYTE: return "UByte";
    case RTT_USHORT: return "UShort";
    case RTT_UINT: return "UInt";
    case RTT_ULONG: return "ULong";
    case RTT_FLOAT: return "Float";
    case RTT_DOUBLE: return "Double";
    case RTT_VEC2: return "Vec2";
    case RTT_VEC3: return "Vec3";
    case RTT_VEC4: return "Vec4";
    case RTT_SARRAY: return "SArray";
    case RTT_DARRAY: return "DArray";
    case RTT_SET: return "Set";
    case RTT_MAP: return "Map";
    case RTT_OBJECT: return "Object";
    case RTT_TYPE: return "Type";
    case RTT_ANY: return "Any";
    case RTT_NULLABLE: return "Any?";
    }
    assert(0);
}

static void freeType(void* ptr, const Lgs_rttype type) {
    if constexpr (PRINT_MEMORY) {
        std::cout << "\tFreeing: " << ptr << std::endl;
    }
    switch (type) {
    case RTT_OBJECT: {
        std::free(ptr);
        break;
    }
    case RTT_DARRAY: {
        const auto arr = static_cast<Lgs_DArray*>(ptr);
        free(arr->data);
        break;
    }
    case RTT_SET: {
        const auto arr = static_cast<Lgs_Set*>(ptr);
        delete arr->data;
        std::free(arr);
        break;
    }
    case RTT_MAP: {
        const auto map = static_cast<Lgs_Map*>(ptr);
        delete map->data;
        std::free(map);
        break;
    }
    default:
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

void Lgs_Stack::addDefer(void* funcPtr, void* ctx) {
    const auto deferFunc = reinterpret_cast<Lgs_DeferFunc>(funcPtr);
    const Lgs_ThunkFunc func_entry{deferFunc, ctx};
    const auto deferIndex = frames[stackIndex].defersCount++;
    frames[stackIndex].defers[deferIndex] = func_entry;
}

void Lgs_Stack::addOwner(void* ptr, const Lgs_rttype type) {
    if constexpr (PRINT_MEMORY) {
        std::cout << "alloc owner " << getTypeName(type) << ": " << ptr << std::endl;
    }
    const auto ownerIndex = frames[stackIndex].ownersCount++;
    frames[stackIndex].owners[ownerIndex] = Lgs_Alloc{ptr, type};
}

void Lgs_Stack::addOrphan(void* ptr, const Lgs_rttype type) {
    if constexpr (PRINT_MEMORY) {
        std::cout << "alloc orphan " << getTypeName(type) << ": " << ptr << std::endl;
    }
    const auto ownerIndex = frames[stackIndex].orphansCount++;
    frames[stackIndex].orphans[ownerIndex] = Lgs_Alloc{ptr, type};
}

void Lgs_Stack::removeOwner(const void* owner) {
    if constexpr (PRINT_MEMORY) {
        std::cout << "removing owner: " << owner << std::endl;
    }
    auto& stackFrame = frames[stackIndex];
    for (size_t i = 0; i < stackFrame.ownersCount; i++) {
        if (stackFrame.owners[i].ptr == owner) {
            freeType(stackFrame.owners[i].ptr, stackFrame.owners[i].type);
            for (size_t j = i; j < stackFrame.ownersCount - 1; j++) {
                stackFrame.owners[j] = stackFrame.owners[j + 1];
            }
            break;
        }
    }
}

void Lgs_Stack::funcCleanup() {
    auto& stackFrame = frames[stackIndex];
    if (stackFrame.ownersCount > 0) {
        if constexpr (PRINT_MEMORY) {
            std::cout << stackFrame.ownersCount << " owners:" << std::endl;
        }
        for (size_t i = 0; i < stackFrame.ownersCount; i++) {
            freeType(stackFrame.owners[i].ptr, stackFrame.owners[i].type);
        }
        stackFrame.ownersCount = 0;
    }
    if (stackFrame.orphansCount > 0) {
        if constexpr (PRINT_MEMORY) {
            std::cout << stackFrame.orphansCount << " orphans:" << std::endl;
        }
        for (size_t i = 0; i < stackFrame.orphansCount; i++) {
            freeType(stackFrame.orphans[i].ptr, stackFrame.orphans[i].type);
        }
        stackFrame.orphansCount = 0;
    }
}

void Lgs_Stack::callDefers() const {
    const auto& top = frames[stackIndex];
    for (size_t i = 0; i < LOCALS_CAPACITY; ++i) {
        const auto [func, ctx] = top.defers[i];
        if (!func) continue;
        func(ctx);
    }
}
