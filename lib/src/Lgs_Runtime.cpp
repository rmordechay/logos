#include "Lgs_Runtime.h"

#include "LgsConfigs.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include "Lgs_DArrayExpr.h"
#include "Lgs_SetExpr.h"
#include "context/Lgs_Aarch64.h"
#include <cassert>

extern "C" void Lgs_Runtime_freeValue(void* ptr, const Lgs_TypeInfo* type);

extern "C" void Lgs_Runtime_init() {}
extern "C" void Lgs_Runtime_close() {}

extern "C" void Lgs_Runtime_push() {
    runtime.stackLevel++;
}

extern "C" void Lgs_Runtime_pop() {
    auto& top = runtime.stack[runtime.stackLevel];
    for (auto [func, ctx] : top.defers) {
        func(ctx);
    }
    if (!top.orphans.empty()) {
        for (const auto [ptr, type] : top.orphans) {
            Lgs_Runtime_freeValue(ptr, type);
        }
    }
    runtime.stackLevel--;
}

extern "C" void Lgs_Runtime_addDefer(const ThunkFunc funcPtr, void* ctx) {
    runtime.stack[runtime.stackLevel].defers.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void Lgs_Runtime_addCoro(const ThunkFunc funcPtr, void* ctx) {
    runtime.coros.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void* Lgs_Runtime_allocateOwner(const size_t size, Lgs_TypeInfo* type) {
    const auto ptr = std::malloc(size);
    std::println("Allocated owner in {}: {}B {}", runtime.stackLevel, size, ptr);
    runtime.stack[runtime.stackLevel].owners[ptr] = type;
    return ptr;
}

extern "C" void* Lgs_Runtime_allocateOrphan(const size_t size, Lgs_TypeInfo* type) {
    const auto ptr = std::malloc(size);
    std::println("Allocated orphan in {}: {}B {}", runtime.stackLevel, size, ptr);
    runtime.stack[runtime.stackLevel].orphans[ptr] = type;
    return ptr;
}

extern "C" void* Lgs_Runtime_allocateReturn(const size_t size, Lgs_TypeInfo* type) {
    const auto ptr = std::malloc(size);
    std::println("Allocated return in {}: {}B {}", runtime.stackLevel, size, ptr);
    // This is safe because the func should never be called from the main frame
    runtime.stack[runtime.stack.size() - 2].orphans[ptr] = type;
    return ptr;
}

extern "C" void Lgs_Runtime_removeOwner(void* owner) {
    runtime.stack[runtime.stackLevel].owners.erase(owner);
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

extern "C" void Lgs_Runtime_throwError(const size_t count, const char* msg, ...) {
    char out[STRING_BUFFER_SIZE];
    va_list args;
    va_start(args, msg);
    formatErrorMsg(msg, out, count, args);
    va_end(args);
    logError(std::string(out) + "\n");
    exit(1);
}

extern "C" void Lgs_Runtime_freeValue(void* ptr, const Lgs_TypeInfo* type) {
    if (!ptr) return;
    std::println("Freeing in {}: {}", runtime.stackLevel, ptr);
    switch (type->kind) {
    case RTT_DARRAY: {
        const auto darray = static_cast<Lgs_DArrayExpr*>(ptr);
        auto offset = 0;
        for (int i = 0; i < darray->length; ++i) {
            const auto element = darray->data + offset;
            Lgs_Runtime_freeValue(element, type->dArray.baseType);
            offset += type->dArray.baseType->size;
        }
        //std::free(ptr);
        break;
    }
    case RTT_SET: {
        const auto set = static_cast<Lgs_SetExpr*>(ptr);
        //std::free(set->data);
        //std::free(ptr);
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
            offset += fieldType->size;
        }
        // std::free(ptr);
        break;
    }
    case RTT_STR:
        break;
    case RTT_NULLABLE: {
        Lgs_Runtime_freeValue(ptr, type->nullable.baseType);
        break;
    }
    case RTT_SARRAY:
    case RTT_MAP: {
        assert(0);
    }
    default: break;
    }
}
