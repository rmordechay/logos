#include "LogosInt.h"

std::string LogosInt::getName() const {
    return name;
}

LogosType* LogosInt::inferType(LogosType* other) {
    return new LogosInt();
}
