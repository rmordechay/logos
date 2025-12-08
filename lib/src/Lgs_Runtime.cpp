#include "Lgs_Runtime.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include "Lgs_DArrayExpr.h"
#include "Lgs_SetExpr.h"
#include "context/Lgs_Aarch64.h"
#include <cassert>

static void freeValue(void* ptr, const Lgs_TypeInfo* type);

extern "C" void Lgs_Runtime_init() {}
extern "C" void Lgs_Runtime_close() {}

extern "C" void Lgs_Runtime_push() {
    runtime.stack.push_back(Lgs_StackFrame{});
}

extern "C" void Lgs_Runtime_pop() {
    auto& stack = runtime.stack;
    auto& top = stack.back();
    for (auto [func, ctx] : top.defers) {
        func(ctx);
    }
    if (!top.orphans.empty()) {
        std::println("Freeing orphans in {}:", stack.size());
        for (const auto [ptr, type] : top.orphans) {
            std::println("\t* {}", ptr);
            freeValue(ptr, type);
        }
    }
    runtime.stack.pop_back();
}

extern "C" void Lgs_Runtime_addDefer(const ThunkFunc funcPtr, void* ctx) {
    runtime.stack.back().defers.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void Lgs_Runtime_addCoro(const ThunkFunc funcPtr, void* ctx) {
    runtime.coros.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void* Lgs_Runtime_allocateOwner(const size_t size, Lgs_TypeInfo* type) {
    const auto ptr = std::malloc(size);
    std::println("Allocated owner in {}: {}B {}", runtime.stack.size(), size, ptr);
    runtime.stack.back().owners[ptr] = type;
    return ptr;
}

extern "C" void* Lgs_Runtime_allocateOrphan(const size_t size, Lgs_TypeInfo* type) {
    const auto ptr = std::malloc(size);
    std::println("Allocated orphan in {}: {}B {}", runtime.stack.size(), size, ptr);
    runtime.stack.back().orphans[ptr] = type;
    return ptr;
}

extern "C" void* Lgs_Runtime_allocateReturn(const size_t size, Lgs_TypeInfo* type) {
    const auto ptr = std::malloc(size);
    std::println("Allocated return in {}: {}B {}", runtime.stack.size(), size, ptr);
    // This is safe because the func should never be called from the main frame
    runtime.stack[runtime.stack.size() - 2].orphans[ptr] = type;
    return ptr;
}

extern "C" void Lgs_Runtime_removeOwner(void* owner) {
    runtime.stack.back().owners.erase(owner);
}

extern "C" void Lgs_Runtime_yield() {
    Lgs_switchContext();
}

extern "C" void Lgs_Runtime_addToVTable(void* instance, const int32_t virtualID, void* ptr) {
    runtime.vtable[{instance, virtualID}] = ptr;
}

extern "C" void* Lgs_Runtime_getFromVTable(void* instance, const int32_t virtualID) {
    assert(runtime.vtable.contains(VKey{instance, virtualID}));
    return runtime.vtable[VKey{instance, virtualID}];
}

extern "C" void Lgs_Runtime_throwError(const char* msg) {
    logError(std::string(msg) + "\n");
    exit(1);
}

void Lgs_exitWithErrors(const LgsBaseMsg& baseMsg, const std::vector<std::string>& args) {
    printCliError(baseMsg, args);
    exit(1);
}

static void freeValue(void* ptr, const Lgs_TypeInfo* type) {
    switch (type->kind) {
    case RTT_STR: break;
    case RTT_DARRAY: {
        const auto darray = static_cast<Lgs_DArrayExpr*>(ptr);
        std::free(darray->data);
        std::free(ptr);
        break;
    }
    case RTT_SET: {
        const auto set = static_cast<Lgs_SetExpr*>(ptr);
        std::free(set->data);
        std::free(ptr);
        break;
    }
    case RTT_OBJECT: {
        const auto fieldsCount = type->obj.fieldsCount;
        const auto fieldTypes = type->obj.fieldTypes;
        size_t offset = 0;
        for (size_t i = 0; i < fieldsCount; ++i) {
            const auto fieldType = fieldTypes[i];
            void* fieldPtr = static_cast<char*>(ptr) + offset;
            // freeValue(fieldPtr, fieldType);
            offset += fieldType->alignment;
        }
        std::free(ptr);
        break;
    }
    case RTT_SARRAY:
    case RTT_NULLABLE:
    case RTT_MAP: {
        assert(0);
    }
    default: break;
    }
}
