#include "funcs/LgsMethodImpl.h"

#include "exprs/unary/LgsFuncCall.h"
#include "types/LgsObject.h"

bool LgsMethodImpl::equals(const LgsFuncCall* other) {
    if (methodType.name != other->name) return false;
    const auto params = methodType.params;
    const auto args = other->args;
    if (params.size() == 0 && args.size() == 0) return true;
    const auto argsSize = isStatic ? args.size() - 1 : args.size();
    if (params.size() < argsSize) return false;
    for (size_t i = 0; i < params.size(); ++i) {
        const auto paramType = params[i].type;
        const auto argType = args[i + isStatic]->type;
        if (!paramType->equals(argType)) return false;
    }
    return true;
}

LgsFuncType* LgsMethodImpl::getFuncType() {
    return &methodType;
}
