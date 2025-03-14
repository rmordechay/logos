#include "unary/LgsMethodCall.h"

#include "LgsInstance.h"
#include "funcs/LgsMethodImpl.h"

Value* LgsMethodCall::createIRValue(CodeGenMetadata* metadata) {
    return methodImpl->call(metadata, args);
}

string LgsMethodCall::getName() {
    return name;
}

LgsMethodCall::~LgsMethodCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
