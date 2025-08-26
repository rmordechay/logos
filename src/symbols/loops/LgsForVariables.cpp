#include "loops/LgsLoopMetaVar.h"

std::string LgsLoopMetaVar::pname() {
    switch (varType) {
    case FOR_I:
        return FOR_I_NAME;
    case FOR_IS_FIRST:
        return FOR_IS_FIRST_NAME;
    case FOR_IS_LAST:
        return FOR_IS_LAST_NAME;
    }
    assert(0);
}

json::value LgsLoopMetaVar::asJSON() {
    return json::value(pname());
}
