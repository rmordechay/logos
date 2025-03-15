#include "unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"

string LgsFuncCall::getName() {
    return name;
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    return func->call(metadata, args);
}

LgsFuncCall::~LgsFuncCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
