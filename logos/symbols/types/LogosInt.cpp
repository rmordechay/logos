#include "LogosInt.h"

std::string LogosInt::getName() const {
    return name;
}

LogosTypedValue* LogosInt::applyOperation(LogosTypedValue* other) {
    return new LogosInt();
}
