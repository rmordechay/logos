#include "funcs/LgsParam.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

std::string LgsParam::getName() {
    return name;
}

Value* LgsParam::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

json::value LgsParam::asJsonStr() {
    json::object obj;
    obj["name"] = name;
    return obj;
}
