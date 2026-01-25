#include "exprs/LgsMetaSelection.h"

Value* LgsMetaSelection::loadIR(LgsCodeGen& cg) {
    return IRValue;
}

void LgsMetaSelection::hashNode(size_t& oldHash) {
    assert(0);
}

void LgsMetaSelection::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsExpr* LgsMetaSelection::castExplicitly(LgsType* toType) {
    assert(0);
}

void LgsMetaSelection::castImplicitly(LgsType* toType) {

}

std::string LgsMetaSelection::asText() {
    assert(0);
}
