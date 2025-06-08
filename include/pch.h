#pragma once

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
#include "llvm/IR/Verifier.h"
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/MC/TargetRegistry.h>
#include <json/json.hpp>

#include "logos/Platform.h"
#include <logos/LgsRuntime.h>
#include "logos/LgsErrHandler.h"
#include "types/LgsType.h"
#include "data/LgsDefinitions.h"


