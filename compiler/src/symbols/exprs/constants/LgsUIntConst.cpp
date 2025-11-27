#include "exprs/constants/LgsUIntConst.h"

#include "exprs/constants/LgsStrConst.h"

std::string LgsUIntConst::asText() {
    return std::to_string(value);
}

Value* LgsUIntConst::castIR(LgsLLVMGen& cg, LgsType* toType) {
    assert(0);
}
