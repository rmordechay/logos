#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cassert>
#include <unistd.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>
#include <json/json.hpp>

#include <logos/LgsRuntime.h>
#include <types/LgsType.h>

#endif //PCH_H
