#include "data/LgsDefinitions.h"
#include "files/LgsFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include <llvm/Support/FileSystem.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

void LgsLLVMGen::setupModule(const LgsFile& file, const bool debugMode) {
    IRModule = new Module(file.name, context);
    IRModule->setTargetTriple(sys::getDefaultTargetTriple());
    IRModule->setDataLayout(targetMachine->createDataLayout());
    if (debugMode) {
        diBuilder = new DIBuilder(*IRModule);
        diFile = diBuilder->createFile(file.path.string(), "");
        compileUnit = diBuilder->createCompileUnit(dwarf::DW_LANG_lo_user, diFile, "", false, "", 0);
        IRModule->addModuleFlag(Module::Warning, "Dwarf Version", 5);
        IRModule->addModuleFlag(Module::Warning, "Debug Info Version", DEBUG_METADATA_VERSION);
    }
}

Value* LgsLLVMGen::getIRStr(const std::string& value) {
    for (auto& globals : IRModule->globals()) {
        if (!globals.hasInitializer()) continue;
        const auto dataArray = dyn_cast<ConstantDataArray>(globals.getInitializer());
        if (!dataArray || !dataArray->isCString() || dataArray->getAsCString() != value) continue;
        return &globals;
    }
    const auto strConstant = ConstantDataArray::getString(context, value, true);
    const auto globalVar = new GlobalVariable(*IRModule, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
    globalVar->setUnnamedAddr(GlobalValue::UnnamedAddr::Global);
    return globalVar;
}

GlobalVariable* LgsLLVMGen::createGlobal(Type* type, ConstantAggregateZero* zeroInit, const std::string& name) const {
    return new GlobalVariable(*IRModule, type, false, GlobalValue::ExternalLinkage, zeroInit, name);
}

GlobalVariable* LgsLLVMGen::createConstGlobal(Type* type, Constant* zeroInit, const std::string& name) const {
    return new GlobalVariable(*IRModule, type, true, GlobalValue::PrivateLinkage, zeroInit, name);
}

StructType* LgsLLVMGen::getStructType(const std::vector<Type*>& fields, const std::string& name) {
    const auto structType = StructType::getTypeByName(context, name);
    if (!structType) {
        return StructType::create(context, fields, name);
    }
    return structType;
}

BasicBlock* LgsLLVMGen::createBlock(const std::string& name, Function* parent) {
    return BasicBlock::Create(context, name, parent);
}

void LgsLLVMGen::branchIfNeeded(BasicBlock* block) {
    if (!lastInstTerminator()) {
        builder.CreateBr(block);
    }
}

void LgsLLVMGen::startBlock(BasicBlock* block, Function* func) {
    block->insertInto(func);
    builder.SetInsertPoint(block);
}

void LgsLLVMGen::branchAndStartBlock(BasicBlock* block, Function* func) {
    branchIfNeeded(block);
    startBlock(block, func);
}

bool LgsLLVMGen::lastInstTerminator() const {
    return builder.GetInsertBlock()->getTerminator();
}

FunctionType* LgsLLVMGen::getFT(Type* rt, const std::vector<Type*>& params, const bool isVariadic) {
    return FunctionType::get(rt, params, isVariadic);
}

Function* LgsLLVMGen::getFunc(const std::string& funcName, FunctionType* ft, GlobalValue::LinkageTypes linkage) const {
    const auto func = IRModule->getFunction(funcName);
    if (func) return func;
    return Function::Create(ft, linkage, funcName, IRModule);
}

Value* LgsLLVMGen::callFunc(const std::string& funcName, FunctionType* ft, const std::vector<Value*>& args) {
    const auto func = getFunc(funcName, ft);
    return builder.CreateCall(func, args);
}

Value* LgsLLVMGen::callLgsFunc(const std::string& funcName, FunctionType* ft, const std::vector<Value*>& args) {
    return callFunc(LGS_RUNTIME_NAMES_PREFIX + funcName, ft, args);
}

Value* LgsLLVMGen::callMalloc(const size_t size, const bool isOwner, const Lgs_RTType type) {
    assert(type != RTT_UNKNOWN);
    const auto ptr = builder.CreateMalloc(sizeTy(), sizeTy(), usize(size), nullptr);
    if (isOwner) callLgsFunc("runtime_addOwner", getFT(voidTy(), {ptrTy(), i32Ty()}), {ptr, i32(type)});
    else callLgsFunc("runtime_addOrphan", getFT(voidTy(), {ptrTy(), i32Ty()}), {ptr, i32(type)});
    return ptr;
}

Value* LgsLLVMGen::callPrintf(const std::vector<Value*>& args) {
    return callFunc("printf", getFT(i32Ty(), {ptrTy()}, true), args);
}

Value* LgsLLVMGen::callSleep(Value* time) {
    return callFunc("sleep", getFT(i32Ty(), {i32Ty()}), {time});
}

Value* LgsLLVMGen::callExit(Value* exitCode) {
    return callFunc("exit", getFT(voidTy(), {i32Ty()}), {exitCode});
}

Value* LgsLLVMGen::callGetEnv(Value* name) {
    return callFunc("getenv", getFT(ptrTy(), {ptrTy()}), {name});
}

Value* LgsLLVMGen::callGetPid() {
    return callFunc("getpid", getFT(sizeTy()));
}

Value* LgsLLVMGen::callCwd() {
    const auto value = builder.CreateAlloca(ArrayType::get(i8Ty(), 1024));
    callFunc("getcwd", getFT(voidTy(), {i32Ty()}), {value});
    return value;
}

Value* LgsLLVMGen::callCoresNum() {
    return callFunc("sysconf", getFT(i64Ty(), {i32Ty()}), {i32(58)});
}

Value* LgsLLVMGen::callStrLen(Value* str) {
    return callFunc("strlen", getFT(i64Ty(), {ptrTy()}), {str});
}

Value* LgsLLVMGen::callSqrt(Value* radicant) {
    auto d = builder.CreateSIToFP(radicant, doubleTy());
    return callFunc("sqrt", getFT(doubleTy(), {doubleTy()}), {d});
}

void LgsLLVMGen::callMemCpy(Value* dest, Value* src, Value* size) {
    const auto dataLayout = targetMachine->createDataLayout();
    const auto memCpy = Intrinsic::getDeclaration(IRModule, Intrinsic::memcpy, {ptrTy(), ptrTy(), sizeTy()});
    builder.CreateCall(memCpy, {dest, src, size, builder.getFalse()});
}

void LgsLLVMGen::callRuntimeInit() {
    callLgsFunc("runtime_init", getFT(voidTy()));
}

void LgsLLVMGen::removeOwner(Value* ptr) {
    callLgsFunc("runtime_removeOwner", getFT(voidTy(), {ptrTy()}), {ptr});
}

void LgsLLVMGen::callFuncCleanup() {
    callLgsFunc("runtime_funcCleanup", getFT(voidTy()));
}

void LgsLLVMGen::callStackPush() {
    callLgsFunc("stack_push", getFT(voidTy()));
}

void LgsLLVMGen::callPopStack() {
    callLgsFunc("stack_pop", getFT(voidTy()));
}

void LgsLLVMGen::callDefers() {
    const auto ft = getFT(voidTy());
    callLgsFunc("stack_callDefers", ft);
}

void LgsLLVMGen::addDeferFunc(Value* deferFuncPtr, Value* ctx) {
    callLgsFunc("stack_addDefer", getFT(voidTy(), {ptrTy(), ptrTy()}), {deferFuncPtr, ctx});
}

void LgsLLVMGen::addPtrToVtable(Value* instancePtr, Value* name, Value* ptr) {
    callLgsFunc("vtable_add", getFT(voidTy(), {ptrTy(), ptrTy(), ptrTy()}), {instancePtr, name, ptr});
}

Value* LgsLLVMGen::getPtrFromVtable(Value* instancePtr, Value* name) {
    return callLgsFunc("vtable_get", getFT(ptrTy(), {ptrTy(), ptrTy()}), {instancePtr, name});
}

void LgsLLVMGen::addCoro(Value* coroPtr, Value* ctx) {
    callLgsFunc("stack_addCoro", getFT(voidTy(), {ptrTy(), ptrTy()}), {coroPtr, ctx});
}

void LgsLLVMGen::callSpawn(Value* task, Value* ctx) {
    callLgsFunc("scheduler_yield", getFT(voidTy(), {ptrTy(), ptrTy()}), {task, ctx});
}

void LgsLLVMGen::callYield() {
    callLgsFunc("scheduler_yield", getFT(voidTy()), {});
}

void LgsLLVMGen::callShutdown() {
    callLgsFunc("scheduler_shutdown", getFT(voidTy()), {});
}

Value* LgsLLVMGen::callHashStr(Value* value) {
    return callLgsFunc("hash", getFT(i32Ty(), {ptrTy()}), {value});
}

Type* LgsLLVMGen::i1Ty() {
    return IntegerType::getInt1Ty(context);
}

Type* LgsLLVMGen::i8Ty() {
    return IntegerType::getInt8Ty(context);
}

Type* LgsLLVMGen::i16Ty() {
    return IntegerType::getInt16Ty(context);
}

Type* LgsLLVMGen::i32Ty() {
    return IntegerType::getInt32Ty(context);
}

Type* LgsLLVMGen::i64Ty() {
    return IntegerType::getInt64Ty(context);
}

Type* LgsLLVMGen::floatTy() {
    return builder.getFloatTy();
}

Type* LgsLLVMGen::doubleTy() {
    return builder.getDoubleTy();
}

Type* LgsLLVMGen::voidTy() {
    return Type::getVoidTy(context);
}

Type* LgsLLVMGen::iNTy(const unsigned n) {
    return IntegerType::getIntNTy(context, n);
}

IntegerType* LgsLLVMGen::sizeTy() {
    return IRModule->getDataLayout().getIntPtrType(context);
}

PointerType* LgsLLVMGen::ptrTy() {
    return PointerType::getUnqual(context);
}

Value* LgsLLVMGen::null() {
    return ConstantPointerNull::get(ptrTy());
}

ConstantInt* LgsLLVMGen::i1(const bool v) {
    return builder.getInt1(v);
}

ConstantInt* LgsLLVMGen::i8(const int8_t v) {
    return builder.getInt8(v);
}

ConstantInt* LgsLLVMGen::i16(const int16_t v) {
    return builder.getInt16(v);
}

ConstantInt* LgsLLVMGen::i32(const int32_t v) {
    return builder.getInt32(v);
}

ConstantInt* LgsLLVMGen::i64(const int64_t v) {
    return builder.getInt64(v);
}

Constant* LgsLLVMGen::floatv(const float_t v) {
    return ConstantFP::get(floatTy(), v);
}

Constant* LgsLLVMGen::doublev(const double_t v) {
    return ConstantFP::get(doubleTy(), v);
}

ConstantInt* LgsLLVMGen::usize(const size_t v) {
    return ConstantInt::get(sizeTy(), v);
}

ConstantInt* LgsLLVMGen::i32Zero() {
    return builder.getInt32(0);
}

ConstantInt* LgsLLVMGen::i64Zero() {
    return builder.getInt64(0);
}

ConstantInt* LgsLLVMGen::sizeZero() {
    return ConstantInt::get(sizeTy(), 0);
}

ConstantInt* LgsLLVMGen::iN(const unsigned size, const size_t v) {
    return builder.getIntN(size, v);
}

TypeSize LgsLLVMGen::typeSize(StructType* v) const {
    return IRModule->getDataLayout().getTypeStoreSize(v);
}

StructType* LgsLLVMGen::getIteratorIRType(const std::string& name) {
    return getStructType({ptrTy(), i64Ty(), ptrTy(), ptrTy(), ptrTy(), ptrTy()}, name);
}

void LgsLLVMGen::printStr(const std::string& str) {
    callPrintf({getIRStr("%s"), getIRStr(str)});
}

void LgsLLVMGen::printPtr(Value* ptr, const std::string& text) {
    if (text != "") printStr(text);
    callPrintf({getIRStr(LGS_ANY.strFormatPart() + '\n'), ptr});
}

void LgsLLVMGen::printInt(Value* number, const std::string& text) {
    if (text != "") printStr(text);
    callPrintf({getIRStr("%d\n"), number});
}

void LgsLLVMGen::initLLVM() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    LLVMInitializeAArch64TargetInfo();
}

TargetMachine* LgsLLVMGen::getTargetMachine() {
    std::string error;
    const auto targetTriple = sys::getDefaultTargetTriple();
    const auto target = TargetRegistry::lookupTarget(targetTriple, error);
    return target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), std::nullopt);
}


void LgsLLVMGen::finalizeDebugger() {
    if (!diBuilder) return;
    diBuilder->finalize();
    std::error_code EC;
    raw_fd_ostream file("logosdbg.bc", EC, sys::fs::OF_None);
    WriteBitcodeToFile(*IRModule, file);
    file.flush();
    delete diBuilder;
    diBuilder = nullptr;
}
