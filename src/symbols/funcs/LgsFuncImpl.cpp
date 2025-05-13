#include "funcs/LgsFuncImpl.h"
#include "exprs/unary/LgsFuncCall.h"
#include "types/LgsIterable.h"

void LgsMainFunc::setArgs(const vector<char*>& args) {
    if (funcType.params.empty()) return;
    this->args = args;
    const auto argv = funcType.params[0];
    const auto iterable = argv->type->asIterable();
    iterable->isConst = true;
}
