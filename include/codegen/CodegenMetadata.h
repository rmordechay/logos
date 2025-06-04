#ifndef CODEGENMETADATA_H
#define CODEGENMETADATA_H

#include "logos/LgsActiveEnv.h"
#include <json/json.hpp>
#include <llvm/TargetParser/Host.h>

using namespace llvm;
using namespace nlohmann;

inline LgsActiveEnv activeEnv;
inline std::string targetTriple = sys::getDefaultTargetTriple();

#endif //CODEGENMETADATA_H
