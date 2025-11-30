#include "exprs/LgsTypeExpr.h"

#include "LgsType.h"

std::string LgsTypeExpr::asText() {
    return type->pname();
}
