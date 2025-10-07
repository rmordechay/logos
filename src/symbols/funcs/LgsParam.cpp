#include "funcs/LgsParam.h"

#include "LgsType.h"
#include "utils/LgsUtils.h"

Value* LgsParam::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsParam::getName() {
    return name;
}

void LgsParam::parseAsJSON(std::stringstream& json) {
    openJsonObject(json);
    addJsonKeyValue(json, "name", name, true);
    addJsonKeyValue(json, "type", type->getName());
    closeJsonObject(json);
}

