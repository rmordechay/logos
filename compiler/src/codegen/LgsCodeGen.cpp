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

inline TargetMachine* targetMachine;

void LgsCodeGen::setupModule(const fs::path& file, const bool debugMode) {
    IRModule = new Module(file.stem().string(), context);
    if (!debugMode) return;
    debugger.diBuilder = new DIBuilder(*IRModule);
    debugger.diFile = debugger.diBuilder->createFile(fs::canonical(file).string(), "");
    debugger.compileUnit = debugger.diBuilder->createCompileUnit(dwarf::DW_LANG_C, debugger.diFile, "Logos", false, "", 0);
    IRModule->addModuleFlag(Module::Warning, "Dwarf Version", 5);
    IRModule->addModuleFlag(Module::Warning, "Debug Info Version", DEBUG_METADATA_VERSION);
}

bool LgsCodeGen::writeIRModule(const LgsPaths& paths, uint8_t optLevel) const {
    if (verifyModule(*IRModule, &errs())) {
        IRModule->print(outs(), nullptr);
        return false;
    }
    // Write IR to file
    auto moduleName = IRModule->getName().str();
    if (lgsConfigs.writeIRFiles) {
        const auto filePath = (paths.buildDirIR / moduleName).string() + ".ll";
        if (fs::exists(filePath)) fs::remove(filePath);
        std::error_code EC;
        raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
        IRModule->print(textFile, nullptr);
    }

    // Run passes
    PassBuilder passBuilder(targetMachine);
    LoopAnalysisManager loopAnalyser;
    FunctionAnalysisManager funcAnalyser;
    CGSCCAnalysisManager CGAnalyser;
    ModuleAnalysisManager analysisManager;
    passBuilder.registerModuleAnalyses(analysisManager);
    passBuilder.registerFunctionAnalyses(funcAnalyser);
    passBuilder.registerLoopAnalyses(loopAnalyser);
    passBuilder.registerCGSCCAnalyses(CGAnalyser);
    passBuilder.crossRegisterProxies(loopAnalyser, funcAnalyser, CGAnalyser, analysisManager);
    auto passManager = passBuilder.buildPerModuleDefaultPipeline(getOptLevel(optLevel));
    passManager.run(*IRModule, analysisManager);

    // Create bc file
    const std::string outputPath = paths.buildDirObjs / moduleName;
    if (fs::exists(outputPath)) fs::remove(outputPath);
    std::error_code ec;
    raw_fd_ostream bitcodeStream(outputPath + ".bc", ec, sys::fs::OF_None);
    if (ec.value() != 0) assert(0);
    WriteBitcodeToFile(*IRModule, bitcodeStream);
    bitcodeStream.flush();
    bitcodeStream.close();
    return true;
}

Constant* LgsCodeGen::getString(const std::string& value, const bool addNull) {
    for (auto& globals : IRModule->globals()) {
        if (!globals.hasInitializer()) continue;
        const auto dataArray = llvm::dyn_cast<ConstantDataArray>(globals.getInitializer());
        if (!dataArray || !dataArray->isCString() || dataArray->getAsCString() != value) continue;
        return &globals;
    }
    const auto strConstant = ConstantDataArray::getString(context, value, addNull);
    return new GlobalVariable(*IRModule, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
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
    const auto loopStart = builder.CreateSExt(zeroSize(), sizeTy());
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

Value* LgsCodeGen::loadPtr(Value* value) {
    return builder.CreateLoad(ptrTy(), value);
}

Value* LgsCodeGen::loadSize(Value* value) {
    return builder.CreateLoad(sizeTy(), value);
}

Value* LgsCodeGen::isNull(Value* value) {
    return builder.CreateIsNull(value);
}

Value* LgsCodeGen::getLevel(Value* v) {
    return load(sizeTy(), v);
}

Value* LgsCodeGen::emptyBuffer(const size_t size) {
    return builder.CreateAlloca(ArrayType::get(i8Ty(), size > 0 ? size : LGS_STR_BUFFER_SIZE));
}

void LgsCodeGen::incSize(Value* bufferOffset, Value* ptr) {
    store(builder.CreateAdd(bufferOffset, usize(1)), ptr);
}

void LgsCodeGen::addNullTerminate(Value* strPtr, Value* pos) {
    store(zero8(), builder.CreateInBoundsGEP(i8Ty(), strPtr, {pos}));
}

Value* LgsCodeGen::allocaAndStore(Type* type, Value* v, const std::string& name) {
    const auto ptr = builder.CreateAlloca(type, nullptr, name);
    builder.CreateStore(v, ptr);
    return ptr;
}

Value* LgsCodeGen::loadField(Type* parentType, Value* parentPtr, const size_t position, Type* ty) {
    assert(ty && parentPtr);
    return builder.CreateLoad(ty, builder.CreateStructGEP(parentType, parentPtr, position));
}

void LgsCodeGen::storeField(Type* parentType, Value* parentPtr, const size_t position, Value* v) {
    store(v, builder.CreateStructGEP(parentType, parentPtr, position));
}

StructType* LgsCodeGen::getStructType(const std::vector<Type*>& types, const std::string& name) {
    const auto structType = StructType::getTypeByName(context, name);
    if (!structType) {
        return StructType::create(context, types, name);
    }
    return structType;
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

Value* LgsCodeGen::callHash(Value* type, Value* arg) {
    return callRuntimeFunc("hashValue", sizeTy(), {ptrTy(), ptrTy()}, {type, arg});
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

Value* LgsCodeGen::allocStr(Value* strPtr) {
    return callRuntimeFunc("allocStr", ptrTy(), {ptrTy()}, {strPtr});
}

Value* LgsCodeGen::allocEmptyStr(Value* length) {
    return callRuntimeFunc("allocEmptyStr", ptrTy(), {sizeTy()}, {length});
}

Value* LgsCodeGen::reallocate(Value* ptr, Value* size, Value* level) {
    return callRuntimeFunc("reallocate", ptrTy(), {ptrTy(), sizeTy(), sizeTy()}, {ptr, toSize(size), toSize(level)});
}

Value* LgsCodeGen::moveValue(const std::string& baseName, Value* v, Value* toLevel) {
    const std::vector args = {v, toLevel};
    const std::vector<Type*> params = {ptrTy(), sizeTy()};
    return callRuntimeFunc("move" + baseName, ptrTy(), params, args);
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

void LgsCodeGen::startFunc(Function* parent) {
    const auto entryBlock = BasicBlock::Create(context, BLOCK_ENTRY, parent);
    builder.SetInsertPoint(entryBlock);
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

void LgsCodeGen::assertGuard(Value* cond) {
    ifStmt(cond, [this] {callFunc("abort", voidTy());});
}

void LgsCodeGen::createNullPtrGuard(Value* value) {
    ifStmt(isNull(value), [this]{throwError(E10111);});
}

void LgsCodeGen::createIndexBoundsGuard(Value* len, Value* index) {
    const auto cond = builder.CreateICmpUGE(toSize(index), toSize(len));
    ifStmt(cond, [this, &index]{throwError(E10003, {index});});
}

void LgsCodeGen::createArrBoundsGuard(Value* maxLen, Value* arrLen) {
    const auto cond = builder.CreateICmpUGT(toSize(arrLen), toSize(maxLen));
    ifStmt(cond, [this, &maxLen]{throwError(E10105, {callSnprintf("%d", {maxLen})});});
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

Value* LgsCodeGen::callIntrinsics(const Intrinsic::ID intrinsicID, const std::vector<Type*>& types, const std::vector<Value*>& args) {
    const auto declaration = Intrinsic::getOrInsertDeclaration(IRModule, intrinsicID, types);
    return builder.CreateCall(declaration, args);
}

Value* LgsCodeGen::callLgsFunc(const std::string& baseName, const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes, const std::vector<Value*>& args) {
    if (baseName == "") return callFunc(LGS_PREFIX + funcName, rt, paramTypes, args);
    return callFunc(LGS_PREFIX + baseName + '_' + funcName, rt, paramTypes, args);
}

Value* LgsCodeGen::callRuntimeFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes, const std::vector<Value*>& args, const bool isVariadic) {
    if (debugger.diBuilder) {
        const auto savedDbg = builder.getCurrentDebugLocation();
        builder.SetCurrentDebugLocation(DebugLoc());
        const auto v = callFunc(LGS_PREFIX"Runtime_" + funcName, rt, paramTypes, args, isVariadic);
        builder.SetCurrentDebugLocation(savedDbg);
        return v;
    }
    return callFunc(LGS_PREFIX"Runtime_" + funcName, rt, paramTypes, args, isVariadic);
}

Value* LgsCodeGen::callPrintf(const std::vector<Value*>& args) {
    return callFunc("printf", i32Ty(), {ptrTy()}, args, true);
}

Value* LgsCodeGen::callPrintf(const std::string& fmt, const std::vector<Value*>& args) {
    auto argsCpy = args;
    argsCpy.insert(argsCpy.begin(), getString(fmt));
    return callFunc("printf", i32Ty(), {ptrTy()}, argsCpy, true);
}

Value* LgsCodeGen::callSnprintf(const std::string& fmt, const std::vector<Value*>& args) {
    const auto buffer = emptyBuffer();
    std::vector<Value*> tempArgs = {buffer, usize(LGS_STR_BUFFER_SIZE), getString(fmt)};
    tempArgs.insert(tempArgs.end(), args.begin(), args.end());
    callFunc("snprintf", i32Ty(), {ptrTy(), sizeTy(), ptrTy()}, tempArgs, true);
    return buffer;
}

Value* LgsCodeGen::callSnprintf(const std::string& fmt, Value* buffer, Value* size, Value* ptr) {
    const std::vector<Value*> args = {buffer, size, getString(fmt), ptr};
    return callFunc("snprintf", i32Ty(), {ptrTy(), sizeTy(), ptrTy()}, args, true);
}

Value* LgsCodeGen::callStrlen(Value* str) {
    return callFunc("strlen", i64Ty(), {ptrTy()}, {str});
}

Value* LgsCodeGen::strsEqual(Value* str1, Value* str2) {
    const auto strEq = callFunc("strcmp", i32Ty(), {ptrTy(), ptrTy()}, {str1, str2});
    return builder.CreateICmpEQ(strEq, zero32());
}

Value* LgsCodeGen::strsNotEqual(Value* str1, Value* str2) {
    const auto strEq = callFunc("strcmp", i32Ty(), {ptrTy(), ptrTy()}, {str1, str2});
    return builder.CreateICmpNE(strEq, zero32());
}

void LgsCodeGen::callMemset(Value* dest, Value* src, Value* size) {
    builder.CreateMemSet(dest, src, size, MaybeAlign());
}

void LgsCodeGen::callMemcpy(Value* dest, Value* src, Value* size) {
    builder.CreateMemCpy(dest, MaybeAlign(), src, MaybeAlign(), size);
}

StructType* LgsCodeGen::getRTTStruct() {
    return getStructType({ptrTy(), sizeTy(), i32Ty(), i1Ty(), i1Ty(), ptrTy()}, "RTI");
}

void LgsCodeGen::printStr(const std::string& value, const std::string& prefix) {
    if (prefix != "") printStr(prefix);
    callPrintf("%s", {getString(value)});
}

void LgsCodeGen::printStr(Value* value, const std::string& prefix) {
    if (prefix != "") printStr(prefix);
    callPrintf("%s\n", { value});
}

void LgsCodeGen::printInt(Value* value, const std::string& prefix) {
    if (prefix != "") printStr(prefix);
    callPrintf("%d\n", { value});
}

void LgsCodeGen::printFloat(Value* value, const std::string& prefix) {
    if (prefix != "") printStr(prefix);
    callPrintf("%f\n", { value});
}

void LgsCodeGen::printLong(Value* value, const std::string& prefix) {
    if (prefix != "") printStr(prefix);
    callPrintf("%ld\n", { value});
}

void LgsCodeGen::printPtr(Value* value, const std::string& prefix) {
    if (prefix != "") printStr(prefix);
    callPrintf("%p\n", { value});
}

void LgsCodeGen::printBytes(Value* value, Value* size, const std::string& prefix) {
    if (prefix != "") printStr(prefix);
    callRuntimeFunc("printBytes", voidTy(), {ptrTy(), sizeTy()}, {value, size});
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
    raw_fd_ostream file((buildPath / "logosdbg.bc").string(), EC, sys::fs::OF_None);
    WriteBitcodeToFile(*IRModule, file);
    file.flush();
}

DILocation* LgsCodeGen::getDebugLoc(const LgsLocation& location) {
    return DILocation::get(
        context,
        location.lineStart + 1,
        location.columnStart,
        debugger.subprogram,
        debugger.subprogram->getScope()
    );
}

void LgsCodeGen::initLLVM() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    std::string error;
    const auto targetTriple = Triple(sys::getDefaultTargetTriple());
    const auto target = TargetRegistry::lookupTarget(targetTriple, error);
    targetMachine = target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), std::nullopt);
}

OptimizationLevel LgsCodeGen::getOptLevel(const uint8_t optLevel) {
    if (optLevel == 0) return OptimizationLevel::O0;
    if (optLevel == 1) return OptimizationLevel::O1;
    if (optLevel == 2) return OptimizationLevel::O2;
    if (optLevel == 3) return OptimizationLevel::O3;
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

ConstantInt* LgsCodeGen::getTypeSize(Type* ty) {
    return usize(IRModule->getDataLayout().getTypeAllocSize(ty));
}

Constant* LgsCodeGen::null() {
    return ConstantPointerNull::get(ptrTy());
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

Constant* LgsCodeGen::floatv(const float_t v) {
    return ConstantFP::get(floatTy(), v);
}

Constant* LgsCodeGen::doublev(const double_t v) {
    return ConstantFP::get(doubleTy(), v);
}

ConstantInt* LgsCodeGen::zero8() {
    return builder.getInt8(0);
}

ConstantInt* LgsCodeGen::zero32() {
    return builder.getInt32(0);
}

ConstantInt* LgsCodeGen::zero64() {
    return builder.getInt64(0);
}

ConstantInt* LgsCodeGen::zeroSize() {
    return ConstantInt::get(sizeTy(), 0);
}

Value* LgsCodeGen::toFloat(Value* v) {
    return builder.CreateSIToFP(v, floatTy());
}

Value* LgsCodeGen::toInt(Value* v) {
    return builder.CreateFPToSI(v, i32Ty());
}

Value* LgsCodeGen::toSize(Value* v) {
    return builder.CreateZExt(v, sizeTy());
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

void LgsStrBuilder::add(Value* value, Value* size) const {
    const auto currentOffset = cg.loadSize(index);
    const auto gep = cg.builder.CreatePtrAdd(buffer, currentOffset);
    cg.callMemcpy(gep, value, size);
    cg.store(cg.builder.CreateAdd(currentOffset, size), index);
}

void LgsStrBuilder::add(const std::string& value) const {
    add(cg.getString(value, false), cg.usize(value.length()));
}

void LgsStrBuilder::finalize() const {
    cg.addNullTerminate(buffer, cg.loadSize(index));
}
