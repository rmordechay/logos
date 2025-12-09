#include "LgsDefinitions.h"
#include "files/LgsFile.h"
#include "LgsConfigs.h"
#include "LgsUtils.h"
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
#include <iostream>
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

void LgsCgModule::loop(Value* loopLength, const std::function<void(Value*, BasicBlock*)>& body) {
    const auto condBlock = createBlock(BLOCK_NAME_LOOP_COND);
    const auto bodyBlock = createBlock(BLOCK_NAME_LOOP_BODY);
    const auto exitBlock = createBlock(BLOCK_NAME_LOOP_EXIT);
    const auto iPtr = builder.CreateAlloca(sizeTy());
    const auto loopStart = builder.CreateSExt(sizeZero(), sizeTy());
    builder.CreateStore(loopStart, iPtr);
    builder.CreateBr(condBlock);

    // Condition
    startBlock(condBlock);
    auto iValue = builder.CreateLoad(sizeTy(), iPtr);
    const auto loopEnd = builder.CreateSExt(loopLength, sizeTy());
    const auto condition = builder.CreateICmpSLT(iValue, loopEnd);
    builder.CreateCondBr(condition, bodyBlock, exitBlock);

    // Body
    startBlock(bodyBlock);
    body(iValue, exitBlock);
    if (lastInstTerminator()) return;
    iValue = builder.CreateLoad(sizeTy(), iPtr);
    const auto inc = builder.CreateAdd(iValue, usize(1));
    builder.CreateStore(inc, iPtr);
    builder.CreateBr(condBlock);
    startBlock(exitBlock);
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
    if (const auto gepInst = dyn_cast<llvm::GetElementPtrInst>(v)) {
        const auto elementType = gepInst->getResultElementType();
        if (elementType && (elementType->isPointerTy() || elementType->isArrayTy())) {
            return builder.CreateLoad(ptrTy(), gepInst);
        }
        return v;
    }
    if (const auto ce = llvm::dyn_cast<llvm::ConstantExpr>(v)) {
        if (ce->getOpcode() == llvm::Instruction::GetElementPtr) {
            return builder.CreateLoad(ptrTy(), ce);
        }
    }
    if (v->getType()->isPointerTy()) return v;
    const auto ptr = builder.CreateAlloca(v->getType());
    builder.CreateStore(v, ptr);
    return ptr;
}

GlobalVariable* LgsCgModule::createGlobal(const std::string& name, Type* type, Constant* args, const bool isConst, const GlobalValue::LinkageTypes linkage) const {
    if (const auto var = IRModule->getGlobalVariable(name)) return var;
    return new GlobalVariable(*IRModule, type, isConst, linkage, args, name);
}

StructType* LgsCgModule::getStructType(const std::vector<Type*>& fields, const std::string& name) {
    const auto structType = StructType::getTypeByName(context, name);
    if (!structType) {
        return StructType::create(context, fields, name);
    }
    return structType;
}

llvm::AllocaInst* LgsCgModule::getEmptyBuffer() {
    return builder.CreateAlloca(ArrayType::get(i8Ty(), STRING_BUFFER_SIZE));
}

Constant* LgsCgModule::getRTTypeInfo(const std::string& name, const size_t size, const size_t alignment, const Lgs_TypeKind kind, Constant* extra) {
    const auto typeInfo = getRTBaseType();
    const auto v = llvm::ConstantStruct::get(typeInfo, {usize(size), usize(alignment), usize(kind), extra});
    if (isRTTModule) return createGlobal(LGS_TYPEINFO_PREFIX + name, typeInfo, v);
    return createGlobal(LGS_TYPEINFO_PREFIX + name, typeInfo, nullptr);
}

StructType* LgsCgModule::getRTBaseType() {
    const auto typeInfoMatrix = getStructType({sizeTy(), sizeTy(), ptrTy()}, "Matrix"); // Biggest
    return getStructType({sizeTy(), sizeTy(), ptrTy(), typeInfoMatrix}, "RTI");
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

void LgsCgModule::createBoundsGuard(Value* len, Value* index) {
    const auto condition = builder.CreateICmpUGE(extendToSize(index), extendToSize(len));
    const auto validBlock = createBlock();
    const auto invalidBlock = createBlock();
    builder.CreateCondBr(condition, invalidBlock, validBlock);
    startBlock(invalidBlock);
    callRuntimeFunc("throwError", voidTy(), {ptrTy()}, {getString(E10003.msg)});
    branchAndStartBlock(validBlock);
}

FunctionType* LgsCgModule::getFT(Type* rt, const std::vector<Type*>& params, const bool isVariadic) {
    return FunctionType::get(rt, params, isVariadic);
}

Function* LgsCgModule::getFunc(const std::string& funcName, FunctionType* ft, const GlobalValue::LinkageTypes linkage) const {
    const auto func = IRModule->getFunction(funcName);
    if (func) return func;
    return Function::Create(ft, linkage, funcName, IRModule);
}

Value* LgsCgModule::callFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes, const std::vector<Value*>& args, const bool isVariadic) {
    const auto func = IRModule->getOrInsertFunction(funcName, FunctionType::get(rt, paramTypes, isVariadic));
    return builder.CreateCall(func, args);
}

Value* LgsCgModule::callIntrinsics(const llvm::Intrinsic::ID intrinsicID, const std::vector<Type*>& types, const std::vector<Value*>& args) {
    const auto declaration = llvm::Intrinsic::getDeclaration(IRModule, intrinsicID, types);
    return builder.CreateCall(declaration, args);
}

Value* LgsCgModule::callLgsFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes, const std::vector<Value*>& args) {
    return callFunc(LGS_RUNTIME_PREFIX + funcName, rt, paramTypes, args);
}

Value* LgsCgModule::callRuntimeFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes, const std::vector<Value*>& args) {
    if (debugger.diBuilder) {
        const auto savedDbg = builder.getCurrentDebugLocation();
        builder.SetCurrentDebugLocation(llvm::DebugLoc());
        const auto v = callFunc(LGS_RUNTIME_PREFIX"Runtime_" + funcName, rt, paramTypes, args);
        builder.SetCurrentDebugLocation(savedDbg);
        return v;
    }
    return callFunc(LGS_RUNTIME_PREFIX"Runtime_" + funcName, rt, paramTypes, args);
}

Value* LgsCgModule::callHash(Value* arg) {
    return callLgsFunc("hash", i32Ty(), {ptrTy()}, {arg});
}

Constant* LgsCgModule::hashConst(const std::string& str) {
    return i64(hashString(str));
}

Value* LgsCgModule::callPrintf(const std::vector<Value*>& args) {
    return callFunc("printf", i32Ty(), {ptrTy()}, args, true);
}

Value* LgsCgModule::callSnprintf(Value* buffer, Value* fmt, const std::vector<Value*>& args) {
    std::vector<Value*> tempArgs = {buffer, usize(STRING_BUFFER_SIZE), fmt};
    tempArgs.insert(tempArgs.end(), args.begin(), args.end());
    return callFunc("snprintf", i32Ty(), {ptrTy(), sizeTy(), ptrTy()}, tempArgs, true);
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

Value* LgsCgModule::allocate(Value* size, Constant* type, const bool isOwner, const bool isReturnExpr) {
    if (isReturnExpr) {
        return callRuntimeFunc("allocateReturn", ptrTy(), {sizeTy(), ptrTy()}, {extendToSize(size), type});
    }
    const auto name = isOwner ? "allocateOwner" : "allocateOrphan";
    return callRuntimeFunc(name, ptrTy(), {sizeTy(), ptrTy()}, {extendToSize(size), type});
}

void LgsCgModule::callStackPush() {
    callRuntimeFunc("push", voidTy());
}

void LgsCgModule::callPopStack() {
    callRuntimeFunc("pop", voidTy());
}

void LgsCgModule::addToVTable(Value* instance, Value* key, Value* ptr) {
    callRuntimeFunc("addToVTable", voidTy(), {ptrTy(), i32Ty(), ptrTy()}, {instance, key, ptr});
}

Value* LgsCgModule::getFromVTable(Value* instance, Value* key) {
    return callRuntimeFunc("getFromVTable", ptrTy(), {ptrTy(), i32Ty()}, {instance, key});
}

void LgsCgModule::addNullTerminate(Value* strPtr, Value* pos) {
    builder.CreateStore(i8Zero(), builder.CreateGEP(i8Ty(), strPtr, pos));
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
    const auto ty = ArrayType::get(i8Ty(), 1);
    return createGlobal("empty_string", ty, ConstantAggregateZero::get(ty));
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
    LLVMInitializeAArch64TargetInfo();

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
