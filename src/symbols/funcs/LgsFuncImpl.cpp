#include "funcs/LgsFuncImpl.h"
#include "exprs/unary/LgsFuncCall.h"
#include "types/LgsIterable.h"

bool LgsFuncImpl::equals(const LgsFuncCall* other) {
    return funcType.equals(other);
}

LgsFuncType* LgsFuncImpl::getFuncType() {
    return &funcType;
}

void LgsMainFunc::setArgs(const vector<char*>& args) {
    if (funcType.params.empty()) return;
    this->args = args;
    const auto argv = funcType.params[0];
    const auto iterable = argv->type->asIterable();
    iterable->sizes = {args.size()};
    iterable->isStaticIter = true;
}
