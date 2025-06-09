#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cassert>
#include <unistd.h>
#include <thread>
#include <filesystem>

#include <Token.h>
#include <json/json.hpp>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include "llvm/IR/Verifier.h"
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/MC/TargetRegistry.h>
#include <lld/Common/Driver.h>

using namespace std;
using namespace filesystem;
using namespace nlohmann;
using namespace llvm;

#include "LgsLocation.h"
#include "data/LgsErrors.h"
#include "data/LgsWarnings.h"
#include "data/LgsDefinitions.h"
#include "logos/LgsErrHandler.h"
#include "utils/LgsUtils.h"
#include "utils/ThreadPool.h"
#include "parser/LogosParser.h"
#include "parser/LogosLexer.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
