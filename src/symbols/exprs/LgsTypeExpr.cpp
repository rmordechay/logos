#include "exprs/LgsTypeExpr.h"

#include "LgsType.h"

std::string LgsTypeExpr::getName() {
    return type->pname();
}
