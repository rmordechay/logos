#include "funcs/LgsFuncImpl.h"

#include "exprs/unary/LgsFuncCall.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

bool LgsFuncImpl::equals(const LgsFuncCall* other) {
    if (funcType.name != other->name) return false;
    const auto params = funcType.params;
    const auto args = other->args;
    if (params.size() == 0 && args.size() == 0) return true;
    if (params.size() < args.size()) return false;
    for (size_t i = 0; i < params.size(); ++i) {
        assert(args[i]);
        auto thisTypeName = params[i].type->getName();
        auto otherTypeName = args[i]->type->getName();
        if (thisTypeName != otherTypeName) return false;
    }
    return true;
}
