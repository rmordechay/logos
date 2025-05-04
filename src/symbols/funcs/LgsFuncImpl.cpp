#include "funcs/LgsFuncImpl.h"

#include "exprs/unary/LgsFuncCall.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

bool LgsFuncImpl::equals(const LgsFuncCall* other) {
    return funcType.equals(other);
}
