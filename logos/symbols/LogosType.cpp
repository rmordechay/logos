#include "LogosType.h"

LogosType* LogosType::inferBinaryType(const LogosType* other, Operator op) {
    if (getName() == other->getName()) {
        return this;
    }
    return nullptr;
}