#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "types/LgsVoid.h"

string LgsFuncCall::getName() {
    return name;
}

string LgsFuncCall::format(string& indentStr) {
    return indentStr + name + "()";
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    return func->call(metadata, args);
}

void LgsFuncCall::free(CodeGenMetadata* metadata) {

}

LgsFuncCall::~LgsFuncCall() {
    const auto iterStart = parentName == "" ? 0 : 1;
    for (int i = iterStart; i < args.size(); ++i) {
        delete args[i];
    }
}
