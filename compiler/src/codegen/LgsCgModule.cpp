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

void LgsCgModule::setupModule(const fs::path& file, const bool debugMode) {
    IRModule = new Module(file.stem().string(), context);
    IRModule->setTargetTriple(llvm::sys::getDefaultTargetTriple());
    IRModule->setDataLayout(targetMachine->createDataLayout());
    if (debugMode && !isRTTModule) {
        debugger.diBuilder = new DIBuilder(*IRModule);
        debugger.diFile = debugger.diBuilder->createFile(fs::canonical(file).string(), "");
        debugger.compileUnit = debugger.diBuilder->createCompileUnit(llvm::dwarf::DW_LANG_C, debugger.diFile, "Logos", false, "", 0);
        IRModule->addModuleFlag(Module::Warning, "Dwarf Version", 5);
        IRModule->addModuleFlag(Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);
    }
}

bool LgsCgModule::writeIRModule(const LgsPaths& paths, uint8_t optLevel) const {
    if (verifyModule(*IRModule, &llvm::errs())) return false;
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

Constant* LgsCgModule::getString(const std::string& value) {
    for (auto& globals : IRModule->globals()) {
        if (!globals.hasInitializer()) continue;
        const auto dataArray = llvm::dyn_cast<llvm::ConstantDataArray>(globals.getInitializer());
        if (!dataArray || !dataArray->isCString() || dataArray->getAsCString() != value) continue;
        return &globals;
    }
    const auto strConstant = llvm::ConstantDataArray::getString(context, value, true);
    const auto globalVar = new GlobalVariable(*IRModule, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
    globalVar->setUnnamedAddr(GlobalValue::UnnamedAddr::Global);
    return globalVar;
}

Value* LgsCgModule::getPtrTo(Value* v) {
    if (v->getType()->isPointerTy()) return v;
    const auto ptr = builder.CreateAlloca(v->getType());
    builder.CreateStore(v, ptr);
    return ptr;
}

llvm::AllocaInst* LgsCgModule::getEmptyBuffer() {
    return builder.CreateAlloca(ArrayType::get(i8Ty(), STRING_BUFFER_SIZE));
}

GlobalVariable* LgsCgModule::createGlobal(const std::string& name, Type* type, Constant* initializer, const bool isConst, const GlobalValue::LinkageTypes linkage) const {
    if (const auto var = IRModule->getGlobalVariable(name)) return var;
    return new GlobalVariable(*IRModule, type, isConst, linkage, initializer, name);
}

void LgsCgModule::loop(Value* loopLength, const std::function<void(Value*, BasicBlock*)>& body) {
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

void LgsCgModule::store(Value* v, Value* ptr) {
    if (v == ptr) return;
    builder.CreateStore(v, ptr);
}

Value* LgsCgModule::load(Type* ty, Value* ptr) {
    assert(ty && ptr);
    return builder.CreateLoad(ty, ptr);
}

Value* LgsCgModule::allocaAndStore(Type* type, Value* v) {
    const auto ptr = builder.CreateAlloca(type);
    builder.CreateStore(v, ptr);
    return ptr;
}

StructType* LgsCgModule::getStructType(const std::vector<Type*>& fields, const std::string& name) {
    const auto structType = StructType::getTypeByName(context, name);
    if (!structType) {
        return StructType::create(context, fields, name);
    }
    return structType;
}

void LgsCgModule::storeStructField(Type* parentType, Value* parentPtr, const size_t position, Value* v) {
    const auto gep = builder.CreateStructGEP(parentType, parentPtr, position);
    store(v, gep);
}

void LgsCgModule::addNullTerminate(Value* strPtr, Value* pos) {
    store(i8Zero(), builder.CreateGEP(i8Ty(), strPtr, pos));
}

void LgsCgModule::callStackPush() {
    callRuntimeFunc("push", voidTy());
}

void LgsCgModule::callPopStack() {
    callRuntimeFunc("pop", voidTy());
}

Value* LgsCgModule::callHash(Value* arg) {
    return callLgsFunc("", "hash", i32Ty(), {ptrTy()}, {arg});
}

Constant* LgsCgModule::hashConst(const std::string& str) {
    return i64(hashString(str));
}

void LgsCgModule::addToVTable(Value* instance, Value* key, Value* ptr) {
    callRuntimeFunc("addToVTable", voidTy(), {ptrTy(), i32Ty(), ptrTy()}, {instance, key, ptr});
}

Value* LgsCgModule::getFromVTable(Value* instance, Value* key) {
    return callRuntimeFunc("getFromVTable", ptrTy(), {ptrTy(), i32Ty()}, {instance, key});
}

void LgsCgModule::freeValue(Value* ptr, Constant* type) {
    callRuntimeFunc("freeValue", voidTy(), {ptrTy(), ptrTy()}, {ptr, type});
}

Value* LgsCgModule::heapAllocate(Value* size, Constant* type, const bool isOwner, const bool isReturnExpr) {
    if (isReturnExpr) {
        return callRuntimeFunc("allocateReturn", ptrTy(), {sizeTy(), ptrTy()}, {extendToSize(size), type});
    }
    return callRuntimeFunc("allocate", ptrTy(), {sizeTy(), ptrTy()}, {extendToSize(size), type});
}

void LgsCgModule::callThrowError(const LgsBaseMsg& err, const std::vector<Value*>& args) {
    std::vector<Value*> irArgs = {usize(args.size()), getString(err.msg)};
    irArgs.insert(irArgs.end(), args.begin(), args.end());
    callRuntimeFunc("throwError", voidTy(), {sizeTy(), ptrTy()}, irArgs, true);
    builder.CreateUnreachable();
}

BasicBlock* LgsCgModule::createBlock(const std::string& name, Function* parent) {
    return BasicBlock::Create(context, name, parent);
}

void LgsCgModule::branchIfNeeded(BasicBlock* block) {
    if (!lastInstTerminator()) {
        builder.CreateBr(block);
    }
}

void LgsCgModule::startBlock(BasicBlock* block) {
    block->insertInto(builder.GetInsertBlock()->getParent());
    builder.SetInsertPoint(block);
}

void LgsCgModule::branchAndStartBlock(BasicBlock* block) {
    branchIfNeeded(block);
    startBlock(block);
}

bool LgsCgModule::lastInstTerminator() const {
    return builder.GetInsertBlock()->getTerminator();
}

void LgsCgModule::createIndexBoundsGuard(Value* len, Value* index) {
    const auto condition = builder.CreateICmpUGE(extendToSize(index), extendToSize(len));
    const auto validBlock = createBlock();
    const auto invalidBlock = createBlock();
    builder.CreateCondBr(condition, invalidBlock, validBlock);
    startBlock(invalidBlock);
    callThrowError(E10003);
    branchAndStartBlock(validBlock);
}

void LgsCgModule::createArrBoundsGuard(Value* maxLen, Value* arrLen) {
    const auto condition = builder.CreateICmpUGT(extendToSize(arrLen), extendToSize(maxLen));
    const auto validBlock = createBlock();
    const auto invalidBlock = createBlock();
    builder.CreateCondBr(condition, invalidBlock, validBlock);
    startBlock(invalidBlock);
    callThrowError(E10105, {callSnprintf("%d", {maxLen})});
    branchAndStartBlock(validBlock);
}

FunctionType* LgsCgModule::getFT(Type* rt, const std::vector<Type*>& params, const bool isVariadic) {
    assert(rt);
    return FunctionType::get(rt, params, isVariadic);
}

Function* LgsCgModule::getFunc(const std::string& funcName, FunctionType* ft, const GlobalValue::LinkageTypes linkage) const {
    const auto func = IRModule->getFunction(funcName);
    if (func) return func;
    return Function::Create(ft, linkage, funcName, IRModule);
}

Value* LgsCgModule::callFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes, const std::vector<Value*>& args, const bool isVariadic) {
    const auto func = IRModule->getOrInsertFunction(funcName, FunctionType::get(rt, paramTypes, isVariadic));
    if (!isVariadic) assert(args.size() == paramTypes.size());
    return builder.CreateCall(func, args);
}

Value* LgsCgModule::callIntrinsics(const llvm::Intrinsic::ID intrinsicID, const std::vector<Type*>& types, const std::vector<Value*>& args) {
    const auto declaration = llvm::Intrinsic::getDeclaration(IRModule, intrinsicID, types);
    return builder.CreateCall(declaration, args);
}

Value* LgsCgModule::callLgsFunc(const std::string& baseName, const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes, const std::vector<Value*>& args) {
    if (baseName == "") return callFunc(LGS_PREFIX + funcName, rt, paramTypes, args);
    return callFunc(LGS_PREFIX + baseName + '_' + funcName, rt, paramTypes, args);
}

Value* LgsCgModule::callRuntimeFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes, const std::vector<Value*>& args, bool isVariadic) {
    if (debugger.diBuilder) {
        const auto savedDbg = builder.getCurrentDebugLocation();
        builder.SetCurrentDebugLocation(llvm::DebugLoc());
        const auto v = callFunc(LGS_PREFIX"Runtime_" + funcName, rt, paramTypes, args, isVariadic);
        builder.SetCurrentDebugLocation(savedDbg);
        return v;
    }
    return callFunc(LGS_PREFIX"Runtime_" + funcName, rt, paramTypes, args, isVariadic);
}

Value* LgsCgModule::callPrintf(const std::vector<Value*>& args) {
    return callFunc("printf", i32Ty(), {ptrTy()}, args, true);
}

Value* LgsCgModule::callSnprintf(const std::string& fmt, const std::vector<Value*>& args) {
    const auto buffer = getEmptyBuffer();
    std::vector<Value*> tempArgs = {buffer, usize(STRING_BUFFER_SIZE), getString(fmt)};
    tempArgs.insert(tempArgs.end(), args.begin(), args.end());
    callFunc("snprintf", i32Ty(), {ptrTy(), sizeTy(), ptrTy()}, tempArgs, true);
    return buffer;
}

Value* LgsCgModule::callStrLen(Value* str) {
    return callFunc("strlen", i64Ty(), {ptrTy()}, {str});
}

void LgsCgModule::callMemSet(Value* dest, Value* src, Value* size) {
    builder.CreateMemSet(dest, src, size, llvm::MaybeAlign());
}

void LgsCgModule::callMemCpy(Value* dest, Value* src, Value* size) {
    builder.CreateMemCpy(dest, llvm::MaybeAlign(), src, llvm::MaybeAlign(), size);
}

Constant* LgsCgModule::getRTTypeInfo(const std::string& name, const size_t size, const Lgs_TypeKind kind, const bool isHeapAlloc, Constant* extra) {
    const auto typeInfo = getRTTBaseStruct();
    const auto prefixedName = LGS_TYPEINFO_PREFIX + name;
    if (isRTTModule) {
        return createGlobal(prefixedName, typeInfo, llvm::ConstantStruct::get(typeInfo, {usize(size), i32(kind), i1(isHeapAlloc), extra}));
    }
    return createGlobal(prefixedName, typeInfo, nullptr);
}

Constant* LgsCgModule::getRTTExtraStruct(const std::string& name, const std::vector<Type*>& fields, const std::vector<Constant*>& args) {
    const auto structName = LGS_TYPEINFO_PREFIX + name;
    auto st = StructType::getTypeByName(context, structName);
    if (!st) {
        st = StructType::create(context, fields, structName);
    }
    return llvm::ConstantStruct::get(st, args);
}

StructType* LgsCgModule::getRTTBaseStruct() {
    const auto typeInfoMatrix = getStructType({sizeTy(), ptrTy(), ptrTy(), ptrTy()}, LGS_TYPEINFO_PREFIX"FuncType"); // Biggest
    return getStructType({sizeTy(), i32Ty(), i1Ty(), typeInfoMatrix}, "RTI"); // size, kind, isHeap, type
}

Type* LgsCgModule::i1Ty() {
    return IntegerType::getInt1Ty(context);
}

Type* LgsCgModule::i8Ty() {
    return IntegerType::getInt8Ty(context);
}

Type* LgsCgModule::i16Ty() {
    return IntegerType::getInt16Ty(context);
}

Type* LgsCgModule::i32Ty() {
    return IntegerType::getInt32Ty(context);
}

Type* LgsCgModule::i64Ty() {
    return IntegerType::getInt64Ty(context);
}

Type* LgsCgModule::floatTy() {
    return builder.getFloatTy();
}

Type* LgsCgModule::doubleTy() {
    return builder.getDoubleTy();
}

Type* LgsCgModule::voidTy() {
    return Type::getVoidTy(context);
}

IntegerType* LgsCgModule::sizeTy() {
    return IRModule->getDataLayout().getIntPtrType(context);
}

PointerType* LgsCgModule::ptrTy() {
    return PointerType::getUnqual(context);
}

Constant* LgsCgModule::null() {
    return llvm::ConstantPointerNull::get(ptrTy());
}

ConstantInt* LgsCgModule::true_() {
    return builder.getTrue();
}

ConstantInt* LgsCgModule::false_() {
    return builder.getFalse();
}

ConstantInt* LgsCgModule::i1(const bool v) {
    return builder.getInt1(v);
}

ConstantInt* LgsCgModule::i8(const int8_t v) {
    return builder.getInt8(v);
}

ConstantInt* LgsCgModule::i16(const int16_t v) {
    return builder.getInt16(v);
}

ConstantInt* LgsCgModule::i32(const int32_t v) {
    return builder.getInt32(v);
}

ConstantInt* LgsCgModule::i64(const int64_t v) {
    return builder.getInt64(v);
}

ConstantInt* LgsCgModule::usize(const size_t v) {
    return ConstantInt::get(sizeTy(), v);
}

ConstantInt* LgsCgModule::i8Zero() {
    return builder.getInt8(0);
}

ConstantInt* LgsCgModule::i32Zero() {
    return builder.getInt32(0);
}

ConstantInt* LgsCgModule::i64Zero() {
    return builder.getInt64(0);
}

ConstantInt* LgsCgModule::sizeZero() {
    return ConstantInt::get(sizeTy(), 0);
}

Value* LgsCgModule::extendToSize(Value* v) {
    return builder.CreateZExt(v, sizeTy());
}

Constant* LgsCgModule::floatv(const float_t v) {
    return llvm::ConstantFP::get(floatTy(), v);
}

Constant* LgsCgModule::doublev(const double_t v) {
    return llvm::ConstantFP::get(doubleTy(), v);
}

TypeSize LgsCgModule::typeSize(Type* v) const {
    return IRModule->getDataLayout().getTypeStoreSize(v);
}

Value* LgsCgModule::emptyStr() {
    const auto name = LGS_PREFIX"emptyStr";
    const auto s = IRModule->getNamedGlobal(name);
    if (s) return s;
    const auto constant = getString("");
    constant->setName(name);
    return constant;
}

void LgsCgModule::printStr(const std::string& str) {
    callPrintf({getString("%s"), getString(str)});
}

void LgsCgModule::printPtr(Value* ptr, const std::string& text) {
    if (text != "") printStr(text);
    callPrintf({getString("%p\n"), ptr});
}

void LgsCgModule::printInt(Value* number, const std::string& text) {
    if (text != "") printStr(text);
    callPrintf({getString("%d\n"), number});
}

void LgsCgModule::finalizeDebugger(const fs::path& buildPath) const {
    if (!debugger.diBuilder) return;
    debugger.diBuilder->finalize();
    std::error_code EC;
    raw_fd_ostream file((buildPath / "logosdbg.bc").string(), EC, llvm::sys::fs::OF_None);
    WriteBitcodeToFile(*IRModule, file);
    file.flush();
}

llvm::DILocation* LgsCgModule::getDebugLoc(const LgsLocation& location) {
    return llvm::DILocation::get(
        context,
        location.lineStart + 1,
        location.columnStart,
        debugger.subprogram,
        debugger.subprogram->getScope()
        );
}

void LgsCgModule::initLLVM() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    std::string error;
    const auto targetTriple = llvm:: sys::getDefaultTargetTriple();
    const auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);
    targetMachine = target->createTargetMachine(targetTriple, "generic", "", llvm::TargetOptions(), std::nullopt);
}

llvm::OptimizationLevel LgsCgModule::getOptLevel(const uint8_t optLevel) {
    if (optLevel == 0) return llvm::OptimizationLevel::O0;
    if (optLevel == 1) return llvm::OptimizationLevel::O1;
    if (optLevel == 2) return llvm::OptimizationLevel::O2;
    if (optLevel == 3) return llvm::OptimizationLevel::O3;
    assert(0);
}

LgsCgModule::~LgsCgModule() {
    if (debugger.diBuilder) {
        delete debugger.diBuilder;
        debugger.diBuilder = nullptr;
    }
}
