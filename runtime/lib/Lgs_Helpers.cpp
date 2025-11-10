#include "Lgs_Helpers.h"
#include "Lgs_DArray.h"
#include "Lgs_Map.h"
#include "Lgs_Set.h"
#include "Lgs_Stack.h"
#include <cassert>

void freeRTType(void* ptr, const Lgs_TypeKind type) {
    switch (type) {
    case RTT_OBJECT: {
        // std::free(ptr);
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

void funcCleanup(Lgs_Stack& stack) {
    auto& stackFrame = stack.frames[stack.stackIndex];
    if (stackFrame.ownersCount > 0) {
        for (size_t i = 0; i < stackFrame.ownersCount; i++) {
            freeRTType(stackFrame.owners[i].ptr, stackFrame.owners[i].type);
        }
        stackFrame.ownersCount = 0;
    }
    if (stackFrame.orphansCount > 0) {
        for (size_t i = 0; i < stackFrame.orphansCount; i++) {
            freeRTType(stackFrame.orphans[i].ptr, stackFrame.orphans[i].type);
        }
        stackFrame.orphansCount = 0;
    }
}

std::string getTypeName(const Lgs_TypeKind type) {
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
    case RTT_ENUM: return "Enum";
    case RTT_TYPE: return "Type";
    case RTT_ANY: return "Any";
    case RTT_NULLABLE: return "Any?";
    }
    assert(0);
}
