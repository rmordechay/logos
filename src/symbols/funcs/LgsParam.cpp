#include "funcs/LgsParam.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

std::string LgsParam::pname() {
    return name;
}

Value* LgsParam::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

json::value LgsParam::asJSON() {
    json::object obj;
    obj["name"] = name;
    return obj;
}
