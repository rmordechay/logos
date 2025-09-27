#include "loops/LgsLoopMetaVar.h"

Value* LgsLoopMetaVar::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsLoopMetaVar::pname() {
    switch (varType) {
    case FOR_I:
        return "for.i";
    case FOR_IS_FIRST:
        return "for.isFirst";
    case FOR_IS_LAST:
        return "for.isLast";
    case FOR_PREV:
        return "for.prev";
    case FOR_NEXT:
        return "for.next";
    }
    assert(0);
}

json::value LgsLoopMetaVar::asJsonStr() {
    return json::value(pname());
}
