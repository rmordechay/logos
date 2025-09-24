#include "Lgs_stack.h"
#include "Lgs_darray.h"
#include "utils/LgsUtils.h"

static std::string getTypeName(const Lgs_RTType type) {
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
    case RTT_OBJECT: return "Object";
    case RTT_TYPE: return "Type";
    }
    assert(0);
}

static void freeType(void* ptr, const Lgs_RTType type) {
    std::cout << "\tFreeing: " << ptr << std::endl;
    switch (type) {
    case RTT_OBJECT: {
        std::free(ptr);
        break;
    }
    case RTT_DARRAY: {
        const auto arr = static_cast<Lgs_darray*>(ptr);
        delete arr->data;
        std::free(arr);
        break;
    }
    default:
        assert(0);
    }
}

void Lgs_stack::push() {
    if (stackIndex + 1 >= STACK_CAPACITY) std::exit(1);
    stackIndex++;
    Lgs_stack_frame& frame = frames[stackIndex];
    frame.defersCount = 0;
}

void Lgs_stack::pop(const bool cleanup) {
    if (cleanup) funcCleanup();
    if (stackIndex < 0) std::exit(1);
    stackIndex--;
}

void Lgs_stack::addDefer(void* funcPtr, void* ctx) {
    if (stackIndex < 0) std::exit(1);
    const auto deferFunc = reinterpret_cast<Lgs_Defer_Func>(funcPtr);
    const Lgs_Thunk_Func func_entry{deferFunc, ctx};
    frames[stackIndex].defers[frames[stackIndex].defersCount++] = func_entry;
}

void Lgs_stack::addOwner(void* ptr, const Lgs_RTType type) {
    std::cout << "alloc owner " << getTypeName(type) << ": " << ptr << std::endl;
    frames[stackIndex].owners.push_back(Lgs_alloc{.ptr = ptr, .type = type});
}

void Lgs_stack::addOrphan(void* ptr, const Lgs_RTType type) {
    std::cout << "alloc orphan " << getTypeName(type) << ": " << ptr << std::endl;
    frames[stackIndex].orphans.push_back(Lgs_alloc{.ptr = ptr, .type = type});
}

void Lgs_stack::removeOwner(const void* owner) const {
    std::cout << "removing owner: " << owner << std::endl;
    auto stackFrame = frames[stackIndex];
    for (auto it = stackFrame.owners.begin(); it != stackFrame.owners.end(); ) {
        if (it->ptr == owner) {
            freeType(it->ptr, it->type);
            it = stackFrame.owners.erase(it);
        } else {
            ++it;
        }
    }
}

void Lgs_stack::funcCleanup() const {
    auto stackFrame = frames[stackIndex];
    const auto ownersSize = stackFrame.owners.size();
    if (ownersSize > 0) {
        std::cout << ownersSize << " owners:" << std::endl;
        for (const auto [ptr, type] : stackFrame.owners) {
            freeType(ptr, type);
        }
        stackFrame.owners.clear();
    }
    const auto orphansSize = stackFrame.orphans.size();
    if (orphansSize > 0) {
        std::cout << orphansSize << " orphans:" << std::endl;
        for (const auto [ptr, type] : stackFrame.orphans) {
            freeType(ptr, type);
        }
        stackFrame.orphans.clear();
    }
}

void Lgs_stack::callDefers() const {
    const auto& top = frames[stackIndex];
    for (int i = 0; i < LOCALS_CAPACITY; ++i) {
        const auto [func, ctx] = top.defers[i];
        if (!func) continue;
        func(ctx);
    }
}
