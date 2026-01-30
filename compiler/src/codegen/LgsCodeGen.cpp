#include "LgsDefinitions.h"
#include "files/LgsFile.h"
#include "LgsConfigs.h"
#include "LgsUtils.h"
#include "errors/LgsErrors.h"
#include "logos/LgsPaths.h"
#include <llvm/Support/FileSystem.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <string>
#include <llvm/Analysis/CGSCCPassManager.h>
#include <llvm/Analysis/LoopAnalysisManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Passes/PassBuilder.h>

#define GENERATE_OBJ_CMD "clang -fstack-protector-strong -Wno-override-module -target %s -c -o %s %s.bc"

void LgsCodeGen::setupModule(const fs::path& file, const bool debugMode) {
    IRModule = new Module(file.stem().string(), context);
    IRModule->setTargetTriple(llvm::sys::getDefaultTargetTriple());
    IRModule->setDataLayout(targetMachine->createDataLayout());
    if (debugMode && mode == CG_MODE_RTTYPES) {
        debugger.diBuilder = new DIBuilder(*IRModule);
        debugger.diFile = debugger.diBuilder->createFile(fs::canonical(file).string(), "");
        debugger.compileUnit = debugger.diBuilder->createCompileUnit(llvm::dwarf::DW_LANG_C, debugger.diFile, "Logos", false, "", 0);
        IRModule->addModuleFlag(Module::Warning, "Dwarf Version", 5);
        IRModule->addModuleFlag(Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);
    }
}

bool LgsCodeGen::writeIRModule(const LgsPaths& paths, uint8_t optLevel) const {
    if (verifyModule(*IRModule, &llvm::errs())) {
        IRModule->print(llvm::outs(), nullptr);
        return false;
    }
    // Write IR to file
    auto moduleName = IRModule->getName().str();
    if (lgsConfigs.writeIRFiles) {
        const auto filePath = (paths.buildDirIR / moduleName).string() + ".ll";
        if (fs::exists(filePath)) fs::remove(filePath);
        std::error_code EC;
        raw_fd_ostream textFile(filePath, EC, llvm::sys::fs::OF_None);
        IRModule->print(textFile, nullptr);
    }

    // Run pass
    llvm::PassBuilder passBuilder(targetMachine);
    llvm::LoopAnalysisManager loopAnalyser;
    llvm::FunctionAnalysisManager funcAnalyser;
    llvm::CGSCCAnalysisManager CGAnalyser;
    llvm::ModuleAnalysisManager analysisManager;
    passBuilder.registerModuleAnalyses(analysisManager);
    passBuilder.registerFunctionAnalyses(funcAnalyser);
    passBuilder.registerLoopAnalyses(loopAnalyser);
    passBuilder.registerCGSCCAnalyses(CGAnalyser);
    passBuilder.crossRegisterProxies(loopAnalyser, funcAnalyser, CGAnalyser, analysisManager);

    auto passManager = passBuilder.buildPerModuleDefaultPipeline(getOptLevel(optLevel));
    passManager.run(*IRModule, analysisManager);

    // Create bc file
    std::error_code ec;
    const std::string outputPath = paths.buildDirObjs / (moduleName + ".o");
    if (fs::exists(outputPath)) fs::remove(outputPath);
    raw_fd_ostream bitcodeStream(outputPath + ".bc", ec, llvm::sys::fs::OF_None);
    assert(!ec);
    llvm::WriteBitcodeToFile(*IRModule, bitcodeStream);
    bitcodeStream.flush();
    bitcodeStream.close();
    // Create object
    char cmd[1024*4];
    const auto triple = llvm::sys::getDefaultTargetTriple();
    std::snprintf(
        cmd,
        sizeof(cmd),
        GENERATE_OBJ_CMD,
        triple.c_str(),
        outputPath.c_str(),
        outputPath.c_str()
    );
    if (!runCmd(cmd)) assert(0);
    fs::remove(outputPath + ".bc");
    return true;
}

Constant* LgsCodeGen::getString(const std::string& value) {
    for (auto& globals : IRModule->globals()) {
        if (!globals.hasInitializer()) continue;
        const auto dataArray = llvm::dyn_cast<llvm::ConstantDataArray>(globals.getInitializer());
        if (!dataArray || !dataArray->isCString() || dataArray->getAsCString() != value) continue;
        return &globals;
    }
    const auto strConstant = llvm::ConstantDataArray::getString(context, value, true);
    return new GlobalVariable(*IRModule, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
}

llvm::AllocaInst* LgsCodeGen::emptyBuffer() {
    return builder.CreateAlloca(ArrayType::get(i8Ty(), LGS_STR_BUFFER_SIZE));
}

size_t LgsCodeGen::getAllocSize(Type* type) const {
    return IRModule->getDataLayout().getTypeAllocSize(type);
}

GlobalVariable* LgsCodeGen::createGlobal(const std::string& name, Type* type, Constant* initializer, const bool isConst, const GlobalValue::LinkageTypes linkage) const {
    if (const auto var = IRModule->getGlobalVariable(name)) return var;
    return new GlobalVariable(*IRModule, type, isConst, linkage, initializer, name);
}

void LgsCodeGen::loop(Value* loopLength, const std::function<void(Value*, BasicBlock*)>& body) {
    const auto condBlock = createBlock(BLOCK_LOOP_COND);
    const auto bodyBlock = createBlock(BLOCK_LOOP_BODY);
    const auto exitBlock = createBlock(BLOCK_LOOP_EXIT);
    const auto iPtr = builder.CreateAlloca(sizeTy());
    const auto loopStart = builder.CreateSExt(sizeZero(), sizeTy());
    store(loopStart, iPtr);
    builder.CreateBr(condBlock);

    // Condition
    startBlock(condBlock);
    auto iValue = load(sizeTy(), iPtr);
    const auto loopEnd = builder.CreateSExt(loopLength, sizeTy());
    const auto condition = builder.CreateICmpSLT(iValue, loopEnd);
    builder.CreateCondBr(condition, bodyBlock, exitBlock);

    // Body
    startBlock(bodyBlock);
    body(iValue, exitBlock);
    if (lastInstTerminator()) return;
    iValue = load(sizeTy(), iPtr);
    const auto inc = builder.CreateAdd(iValue, usize(1));
    store(inc, iPtr);
    builder.CreateBr(condBlock);
    startBlock(exitBlock);
}

void LgsCodeGen::ifStmt(Value* cond, const std::function<void()>& body) {
    const auto IRBlockIfTrue = createBlock(BLOCK_TRUE);
    const auto IRExitBlock = createBlock(BLOCK_EXIT);
    builder.CreateCondBr(cond, IRBlockIfTrue, IRExitBlock);
    startBlock(IRBlockIfTrue);
    body();
    branchAndStartBlock(IRExitBlock);
}

void LgsCodeGen::ifElseStmt(Value* cond, const std::function<void()>& ifBody, const std::function<void()>& elseBody) {
    const auto trueBlock = createBlock(BLOCK_TRUE);
    const auto falseBlock = createBlock(BLOCK_FALSE);
    const auto exitBlock = createBlock(BLOCK_EXIT);
    builder.CreateCondBr(cond, trueBlock, falseBlock);
    startBlock(trueBlock);
    ifBody();
    branch(exitBlock);
    startBlock(falseBlock);
    elseBody();
    branchAndStartBlock(exitBlock);
}

void LgsCodeGen::store(Value* v, Value* ptr) {
    assert(v && ptr);
    if (v == ptr) return;
    builder.CreateStore(v, ptr);
}

Value* LgsCodeGen::load(Type* ty, Value* ptr) {
    assert(ty && ptr);
    return builder.CreateLoad(ty, ptr);
}

void LgsCodeGen::incSize(Value* bufferOffset, Value* ptr) {
    store(builder.CreateAdd(bufferOffset, usize(1)), ptr);
}

Value* LgsCodeGen::allocaAndStore(Type* type, Value* v, const std::string& name) {
    const auto ptr = builder.CreateAlloca(type, nullptr, name);
    builder.CreateStore(v, ptr);
    return ptr;
}

StructType* LgsCodeGen::getStructType(const std::vector<Type*>& types, const std::string& name) {
    const auto structType = StructType::getTypeByName(context, name);
    if (!structType) {
        return StructType::create(context, types, name);
    }
    return structType;
}

void LgsCodeGen::storeStructField(Type* parentType, Value* parentPtr, const size_t position, Value* v) {
    store(v, builder.CreateStructGEP(parentType, parentPtr, position));
}

Value* LgsCodeGen::loadStructField(Type* parentType, Value* parentPtr, const size_t position, Type* ty) {
    assert(ty && parentPtr);
    return builder.CreateLoad(ty, builder.CreateStructGEP(parentType, parentPtr, position));
}

void LgsCodeGen::addNullTerminate(Value* strPtr, Value* pos) {
    store(i8Zero(), builder.CreateInBoundsGEP(i8Ty(), strPtr, {pos}));
}

void LgsCodeGen::callStackPush() {
    callRuntimeFunc("push", sizeTy());
}

void LgsCodeGen::callPopStack() {
    callRuntimeFunc("pop", voidTy());
}

Value* LgsCodeGen::getCurrentLevel() {
    return callRuntimeFunc("getCurrentLevel", sizeTy());
}

Value* LgsCodeGen::callHash(Value* arg) {
    return callRuntimeFunc("hash", sizeTy(), {ptrTy()}, {arg});
}

Value* LgsCodeGen::getVField(Value* objType, Value* objInstance, Value* fieldName) {
    return callRuntimeFunc("getVField", ptrTy(), {ptrTy(), ptrTy(), ptrTy()}, {objType, fieldName, objInstance});
}

Value* LgsCodeGen::getVFunc(Value* objType, Value* funcName) {
    return callRuntimeFunc("getVFunc", ptrTy(), {ptrTy(), ptrTy()}, {objType, funcName});
}

Value* LgsCodeGen::allocInCurrent(Value* size, const bool setLevel) {
    assert(size);
    return callRuntimeFunc("allocInCurrent", ptrTy(), {sizeTy(), i1Ty()}, {size, i1(setLevel)});
}

Value* LgsCodeGen::allocInLevel(Value* size, Value* level, const bool setLevel) {
    assert(size && level);
    return callRuntimeFunc("allocInLevel", ptrTy(), {sizeTy(), sizeTy(), i1Ty()}, {size, level, i1(setLevel)});
}

Value* LgsCodeGen::allocObject(Value* type) {
    return callRuntimeFunc("allocObject", ptrTy(), {ptrTy()}, {type});
}

Value* LgsCodeGen::allocDArr(Value* baseType) {
    return callRuntimeFunc("allocDArr", ptrTy(), {ptrTy()}, {baseType});
}

Value* LgsCodeGen::allocStrConst(Value* strPtr) {
    return callRuntimeFunc("allocStrConst", ptrTy(), {ptrTy()}, {strPtr});
}

Value* LgsCodeGen::reallocate(Value* ptr, Value* size, Value* level) {
    return callRuntimeFunc("reallocate", ptrTy(), {ptrTy(), sizeTy(), sizeTy()}, {ptr, extendToSize(size), extendToSize(level)});
}

Value* LgsCodeGen::moveArrElement(Value* iterable, Value* element, Constant* type) {
    const std::vector<Type*> params = {ptrTy(), ptrTy(), ptrTy()};
    const std::vector<Value*> args = {iterable, element, type};
    return callRuntimeFunc("moveArrElement", ptrTy(), params, args);
}

void LgsCodeGen::throwError(const LgsBaseMsg& err, const std::vector<Value*>& args) {
    std::vector<Value*> irArgs = {usize(args.size()), getString(err.msg)};
    irArgs.insert(irArgs.end(), args.begin(), args.end());
    callRuntimeFunc("throwError", voidTy(), {sizeTy(), ptrTy()}, irArgs, true);
    builder.CreateUnreachable();
}

BasicBlock* LgsCodeGen::createBlock(const std::string& name, Function* parent) {
    return BasicBlock::Create(context, name, parent);
}

void LgsCodeGen::branch(BasicBlock* block) {
    if (!lastInstTerminator()) {
        builder.CreateBr(block);
    }
}

void LgsCodeGen::startBlock(BasicBlock* block) {
    block->insertInto(builder.GetInsertBlock()->getParent());
    builder.SetInsertPoint(block);
}

void LgsCodeGen::branchAndStartBlock(BasicBlock* block) {
    branch(block);
    startBlock(block);
}

Instruction* LgsCodeGen::lastInstTerminator() const {
    return builder.GetInsertBlock()->getTerminator();
}

void LgsCodeGen::createIndexBoundsGuard(Value* len, Value* index) {
    const auto condition = builder.CreateICmpUGE(extendToSize(index), extendToSize(len));
    const auto validBlock = createBlock("valid_block");
    const auto invalidBlock = createBlock("invalid_block");
    builder.CreateCondBr(condition, invalidBlock, validBlock);
    startBlock(invalidBlock);
    throwError(E10003);
    branchAndStartBlock(validBlock);
}

void LgsCodeGen::createArrBoundsGuard(Value* maxLen, Value* arrLen) {
    const auto condition = builder.CreateICmpUGT(extendToSize(arrLen), extendToSize(maxLen));
    const auto validBlock = createBlock();
    const auto invalidBlock = createBlock();
    builder.CreateCondBr(condition, invalidBlock, validBlock);
    startBlock(invalidBlock);
    throwError(E10105, {callSnprintf("%d", {maxLen})});
    branchAndStartBlock(validBlock);
}

FunctionType* LgsCodeGen::getFT(Type* rt, const std::vector<Type*>& params, const bool isVariadic) {
    assert(rt);
    return FunctionType::get(rt, params, isVariadic);
}

Function* LgsCodeGen::getFunc(const std::string& funcName, FunctionType* ft, const GlobalValue::LinkageTypes linkage) const {
    const auto func = IRModule->getFunction(funcName);
    if (func) return func;
    return Function::Create(ft, linkage, funcName, IRModule);
}

Value* LgsCodeGen::callFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes, const std::vector<Value*>& args, const bool isVariadic) {
    const auto func = IRModule->getOrInsertFunction(funcName, FunctionType::get(rt, paramTypes, isVariadic));
    if (!isVariadic) assert(args.size() == paramTypes.size());
    return builder.CreateCall(func, args);
}

Value* LgsCodeGen::callIntrinsics(const llvm::Intrinsic::ID intrinsicID, const std::vector<Type*>& types, const std::vector<Value*>& args) {
    const auto declaration = llvm::Intrinsic::getDeclaration(IRModule, intrinsicID, types);
    return builder.CreateCall(declaration, args);
}

Value* LgsCodeGen::callLgsFunc(const std::string& baseName, const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes, const std::vector<Value*>& args) {
    if (baseName == "") return callFunc(LGS_PREFIX + funcName, rt, paramTypes, args);
    return callFunc(LGS_PREFIX + baseName + '_' + funcName, rt, paramTypes, args);
}

Value* LgsCodeGen::callRuntimeFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes, const std::vector<Value*>& args, const bool isVariadic) {
    if (debugger.diBuilder) {
        const auto savedDbg = builder.getCurrentDebugLocation();
        builder.SetCurrentDebugLocation(llvm::DebugLoc());
        const auto v = callFunc(LGS_PREFIX"Runtime_" + funcName, rt, paramTypes, args, isVariadic);
        builder.SetCurrentDebugLocation(savedDbg);
        return v;
    }
    return callFunc(LGS_PREFIX"Runtime_" + funcName, rt, paramTypes, args, isVariadic);
}

Value* LgsCodeGen::callPrintf(const std::vector<Value*>& args) {
    return callFunc("printf", i32Ty(), {ptrTy()}, args, true);
}

Value* LgsCodeGen::callSnprintf(const std::string& fmt, const std::vector<Value*>& args) {
    const auto buffer = emptyBuffer();
    std::vector<Value*> tempArgs = {buffer, usize(LGS_STR_BUFFER_SIZE), getString(fmt)};
    tempArgs.insert(tempArgs.end(), args.begin(), args.end());
    callFunc("snprintf", i32Ty(), {ptrTy(), sizeTy(), ptrTy()}, tempArgs, true);
    return buffer;
}

Value* LgsCodeGen::callStrlen(Value* str) {
    return callFunc("strlen", i64Ty(), {ptrTy()}, {str});
}

Value* LgsCodeGen::strsEqual(Value* str1, Value* str2) {
    const auto strEq = callFunc("strcmp", i32Ty(), {ptrTy(), ptrTy()}, {str1, str2});
    return builder.CreateICmpEQ(strEq, i32Zero());
}

Value* LgsCodeGen::strsNotEqual(Value* str1, Value* str2) {
    const auto strEq = callFunc("strcmp", i32Ty(), {ptrTy(), ptrTy()}, {str1, str2});
    return builder.CreateICmpNE(strEq, i32Zero());
}

void LgsCodeGen::callMemset(Value* dest, Value* src, Value* size) {
    builder.CreateMemSet(dest, src, size, llvm::MaybeAlign());
}

void LgsCodeGen::callMemcpy(Value* dest, Value* src, Value* size) {
    builder.CreateMemCpy(dest, llvm::MaybeAlign(), src, llvm::MaybeAlign(), size);
}

GlobalVariable* LgsCodeGen::getRTTypeInfo(const std::string& name, ConstantInt* size, const Lgs_TypeKind kind) {
    const auto baseStruct = getRTTStruct();
    const auto prefixedName = LGS_TYPEINFO_PREFIX + name;
    if (mode == CG_MODE_RTTYPES) {
        const auto initializer = llvm::ConstantStruct::get(baseStruct, {size, i32(kind)});
        return createGlobal(prefixedName, baseStruct, initializer);
    }
    return createGlobal(prefixedName, baseStruct, nullptr);
}

StructType* LgsCodeGen::getRTTStruct() {
    return getStructType({sizeTy(), i32Ty()}, "RTI");
}

void LgsCodeGen::printStr(const std::string& value, const std::string& prefix) {
    if (prefix != "") printStr(prefix);
    callPrintf({getString("%s"), getString(value)});
}

void LgsCodeGen::printStr(Value* value, const std::string& prefix) {
    if (prefix != "") printStr(prefix);
    callPrintf({getString("\"%s\"\n"), value});
}

void LgsCodeGen::printInt(Value* value, const std::string& prefix) {
    if (prefix != "") printStr(prefix);
    callPrintf({getString("%d\n"), value});
}

void LgsCodeGen::printFloat(Value* value, const std::string& prefix) {
    if (prefix != "") printStr(prefix);
    callPrintf({getString("%f\n"), value});
}

void LgsCodeGen::printLong(Value* value, const std::string& prefix) {
    if (prefix != "") printStr(prefix);
    callPrintf({getString("%ld\n"), value});
}

void LgsCodeGen::printPtr(Value* value, const std::string& prefix) {
    if (prefix != "") printStr(prefix);
    callPrintf({getString("%p\n"), value});
}

Value* LgsCodeGen::measureTimeStart() {
    return callRuntimeFunc("timeStart", i64Ty());
}

Value* LgsCodeGen::measureTimeEnd(Value* startTime) {
    return callRuntimeFunc("timeEnd", i64Ty(), {i64Ty()}, {startTime});
}

void LgsCodeGen::finalizeDebugger(const fs::path& buildPath) const {
    if (!debugger.diBuilder) return;
    debugger.diBuilder->finalize();
    std::error_code EC;
    raw_fd_ostream file((buildPath / "logosdbg.bc").string(), EC, llvm::sys::fs::OF_None);
    WriteBitcodeToFile(*IRModule, file);
    file.flush();
}

llvm::DILocation* LgsCodeGen::getDebugLoc(const LgsLocation& location) {
    return llvm::DILocation::get(
        context,
        location.lineStart + 1,
        location.columnStart,
        debugger.subprogram,
        debugger.subprogram->getScope()
    );
}

void LgsCodeGen::initLLVM() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    std::string error;
    const auto targetTriple = llvm:: sys::getDefaultTargetTriple();
    const auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);
    targetMachine = target->createTargetMachine(targetTriple, "generic", "", llvm::TargetOptions(), std::nullopt);
}

llvm::OptimizationLevel LgsCodeGen::getOptLevel(const uint8_t optLevel) {
    if (optLevel == 0) return llvm::OptimizationLevel::O0;
    if (optLevel == 1) return llvm::OptimizationLevel::O1;
    if (optLevel == 2) return llvm::OptimizationLevel::O2;
    if (optLevel == 3) return llvm::OptimizationLevel::O3;
    assert(0);
}

Type* LgsCodeGen::i1Ty() {
    return IntegerType::getInt1Ty(context);
}

Type* LgsCodeGen::i8Ty() {
    return IntegerType::getInt8Ty(context);
}

Type* LgsCodeGen::i16Ty() {
    return IntegerType::getInt16Ty(context);
}

Type* LgsCodeGen::i32Ty() {
    return IntegerType::getInt32Ty(context);
}

Type* LgsCodeGen::i64Ty() {
    return IntegerType::getInt64Ty(context);
}

Type* LgsCodeGen::floatTy() {
    return builder.getFloatTy();
}

Type* LgsCodeGen::doubleTy() {
    return builder.getDoubleTy();
}

Type* LgsCodeGen::voidTy() {
    return Type::getVoidTy(context);
}

IntegerType* LgsCodeGen::sizeTy() {
    return IRModule->getDataLayout().getIntPtrType(context);
}

PointerType* LgsCodeGen::ptrTy() {
    return PointerType::getUnqual(context);
}

Constant* LgsCodeGen::null() {
    return llvm::ConstantPointerNull::get(ptrTy());
}

ConstantInt* LgsCodeGen::true_() {
    return builder.getTrue();
}

ConstantInt* LgsCodeGen::false_() {
    return builder.getFalse();
}

ConstantInt* LgsCodeGen::i1(const bool v) {
    return builder.getInt1(v);
}

ConstantInt* LgsCodeGen::i8(const int8_t v) {
    return builder.getInt8(v);
}

ConstantInt* LgsCodeGen::i16(const int16_t v) {
    return builder.getInt16(v);
}

ConstantInt* LgsCodeGen::i32(const int32_t v) {
    return builder.getInt32(v);
}

ConstantInt* LgsCodeGen::i64(const int64_t v) {
    return builder.getInt64(v);
}

ConstantInt* LgsCodeGen::usize(const size_t v) {
    return ConstantInt::get(sizeTy(), v);
}

ConstantInt* LgsCodeGen::i8Zero() {
    return builder.getInt8(0);
}

ConstantInt* LgsCodeGen::i32Zero() {
    return builder.getInt32(0);
}

ConstantInt* LgsCodeGen::i64Zero() {
    return builder.getInt64(0);
}

ConstantInt* LgsCodeGen::sizeZero() {
    return ConstantInt::get(sizeTy(), 0);
}

Value* LgsCodeGen::extendToSize(Value* v) {
    return builder.CreateZExt(v, sizeTy());
}

Constant* LgsCodeGen::floatv(const float_t v) {
    return llvm::ConstantFP::get(floatTy(), v);
}

Constant* LgsCodeGen::doublev(const double_t v) {
    return llvm::ConstantFP::get(doubleTy(), v);
}

Constant* LgsCodeGen::emptyStr() {
    return getString("");
}

LgsCodeGen::~LgsCodeGen() {
    if (debugger.diBuilder) {
        delete debugger.diBuilder;
        debugger.diBuilder = nullptr;
    }
}
