#include "loops/LgsForeachLoop.h"
#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsDArray.h"
#include "exprs/unary/LgsIterator.h"
#include "types/LgsMap.h"

LgsForeachLoop::~LgsForeachLoop() {
    if (iterExpr) {
        delete iterExpr;
    }
}
