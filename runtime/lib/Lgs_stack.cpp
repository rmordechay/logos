#include "Lgs_stack.h"
#include "Lgs_darray.h"
#include "utils/LgsUtils.h"

static void freeType(void* ptr, const Lgs_RTType type) {
    std::cout << "\tFreeing: " << ptr << std::endl;
    switch (type) {
    case RTT_UNKNOWN:
    case RTT_VOID:
    case RTT_BOOL:
    case RTT_CHAR:
    case RTT_FLOAT:
    case RTT_DOUBLE:
    case RTT_INT:
    case RTT_VEC2:
    case RTT_VEC3:
    case RTT_VEC4:
    case RTT_LONG:
    case RTT_SIZE:
    case RTT_STR:
        return;
    case RTT_SARRAY:
    case RTT_TYPE:
        break;
        assert(0);
    case RTT_OBJECT: {
        // std::free(ptr);
        break;
    }
    case RTT_DARRAY: {
        const auto arr = static_cast<Lgs_darray*>(ptr);
        delete arr->data;
        // std::free(arr);
        break;
    }
    }
}

void Lgs_stack::push() {
    if (stackIndex + 1 >= STACK_CAPACITY) std::exit(1);
    stackIndex++;
    Lgs_stack_frame& frame = frames[stackIndex];
    frame.defersCount = 0;
}

void Lgs_stack::pop() {
    funcCleanup();
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
    std::cout << "malloc: " << ptr << std::endl;
    frames[stackIndex].owners.push_back(Lgs_alloc{.ptr = ptr, .type = type});
}

void Lgs_stack::addOrphan(void* ptr, const Lgs_RTType type) {
    std::cout << "malloc: " << ptr << std::endl;
    frames[stackIndex].orphans.push_back(Lgs_alloc{.ptr = ptr, .type = type});
}

void Lgs_stack::removeOwner(const void* owner) const {
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
    std::cout << stackFrame.owners.size() << " owners:" << std::endl;
    for (const auto [ptr, type] : stackFrame.owners) {
        freeType(ptr, type);
    }
    stackFrame.owners.clear();
    std::cout << stackFrame.orphans.size() << " orphans:" << std::endl;
    for (const auto [ptr, type] : stackFrame.orphans) {
        freeType(ptr, type);
    }
    stackFrame.orphans.clear();
}

void Lgs_stack::callDefers() const {
    const auto& top = frames[stackIndex];
    for (int i = 0; i < LOCALS_CAPACITY; ++i) {
        const auto [func, ctx] = top.defers[i];
        if (!func) continue;
        func(ctx);
    }
}
