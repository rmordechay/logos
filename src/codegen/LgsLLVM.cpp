#include "codegen/LgsCodeGen.h"
#include "configs/LgsDefinitions.h"
#include "exprs/unary/LgsFuncCall.h"
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

void LgsLLVM::setupModule(const LgsFile& file, const bool debugMode) {
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

Value* LgsLLVM::getIRStr(const std::string& value) {
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

GlobalVariable* LgsLLVM::createGlobal(Type* type, ConstantAggregateZero* zeroInit, const std::string& name) const {
    return new GlobalVariable(*IRModule, type, false, GlobalValue::ExternalLinkage, zeroInit, name);
}

GlobalVariable* LgsLLVM::createConstGlobal(Type* type, Constant* zeroInit, const std::string& name) const {
    return new GlobalVariable(*IRModule, type, true, GlobalValue::PrivateLinkage, zeroInit, name);
}

StructType* LgsLLVM::getStructType(const std::vector<Type*>& fields, const std::string& name) {
    const auto structType = StructType::getTypeByName(context, name);
    if (!structType) {
        return StructType::create(context, fields, name);
    }
    return structType;
}

void LgsLLVM::storeValueInStruct(StructType* ty, Value* ptr, const int i, Value* v) {
    const auto fieldPtr = builder.CreateStructGEP(ty, ptr, i);
    builder.CreateStore(v, fieldPtr);
}

Value* LgsLLVM::loadValueFromStruct(Type* ty, Value* ptr, const int i) {
    const auto gep = builder.CreateStructGEP(ty, ptr, i);
    return builder.CreateLoad(ty->getStructElementType(i), gep);
}

BasicBlock* LgsLLVM::createBlock(const std::string& name, Function* parent) {
    return BasicBlock::Create(context, name, parent);
}

void LgsLLVM::branchIfNeeded(BasicBlock* block) {
    if (!lastInstTerminator()) {
        builder.CreateBr(block);
    }
}

bool LgsLLVM::lastInstTerminator() const {
    return builder.GetInsertBlock()->getTerminator();
}

FunctionType* LgsLLVM::getFT(Type* rt, const std::vector<Type*>& params, const bool isVariadic) {
    return FunctionType::get(rt, params, isVariadic);
}

Function* LgsLLVM::getFunc(const std::string& funcName, FunctionType* ft, GlobalValue::LinkageTypes linkage) const {
    const auto func = IRModule->getFunction(funcName);
    if (func) return func;
    return Function::Create(ft, linkage, funcName, IRModule);
}

Value* LgsLLVM::callFunc(const std::string& funcName, FunctionType* ft, const std::vector<Value*>& args) {
    const auto func = getFunc(funcName, ft);
    return builder.CreateCall(func, args);
}

Value* LgsLLVM::callLgsFunc(const std::string& funcName, FunctionType* ft, const std::vector<Value*>& args) {
    return callFunc(LGS_RUNTIME_NAMES_PREFIX + funcName, ft, args);
}

Value* LgsLLVM::callMalloc(const size_t size) {
    return builder.CreateMalloc(sizeTy(), sizeTy(), isize(size), nullptr);
}

Value* LgsLLVM::callPrintf(const std::vector<Value*>& args) {
    return callFunc("printf", getFT(i32Ty(), {ptrTy()}, true), args);
}

Value* LgsLLVM::callSleep(Value* time) {
    return callFunc("sleep", getFT(i32Ty(), {i32Ty()}), {time});
}

Value* LgsLLVM::callExit(Value* exitCode) {
    return callFunc("exit", getFT(voidTy(), {i32Ty()}), {exitCode});
}

Value* LgsLLVM::callGetEnv(Value* name) {
    return callFunc("getenv", getFT(ptrTy(), {ptrTy()}), {name});
}

Value* LgsLLVM::callGetPid() {
    return callFunc("getpid", getFT(i32Ty()));
}

Value* LgsLLVM::callCwd() {
    const auto value = builder.CreateAlloca(ArrayType::get(i8Ty(), 1024));
    callFunc("getcwd", getFT(voidTy(), {i32Ty()}), {value});
    return value;
}

Value* LgsLLVM::callCoresNum() {
    return callFunc("sysconf", getFT(i64Ty(), {i32Ty()}), {i32(58)});
}

Value* LgsLLVM::callStrLen(Value* str) {
    return callFunc("strlen", getFT(i64Ty(), {ptrTy()}), {str});
}

Value* LgsLLVM::callSqrt(Value* radicant) {
    auto d = builder.CreateSIToFP(radicant, doubleTy());
    return callFunc("sqrt", getFT(doubleTy(), {doubleTy()}), {d});
}

void LgsLLVM::callCopyMem(Value* dest, Value* src, ArrayType* at) {
    const auto dataLayout = targetMachine->createDataLayout();
    const auto size = dataLayout.getTypeAllocSize(at);
    const auto align = dataLayout.getABITypeAlign(at).value();
    builder.CreateMemCpy(dest, MaybeAlign(align), src, MaybeAlign(align), size);
}

void LgsLLVM::callRuntimeInit() {
    callLgsFunc("Runtime_init", getFT(voidTy()));
}

void LgsLLVM::callStackPush() {
    callLgsFunc("Stack_push", getFT(voidTy()));
}

void LgsLLVM::callPopStack() {
    callLgsFunc("Stack_pop", getFT(voidTy()));
}

void LgsLLVM::callDefers() {
    const auto ft = getFT(voidTy());
    callLgsFunc("Stack_callDefers", ft);
}

void LgsLLVM::addDeferFunc(Value* deferFuncPtr, Value* ctx) {
    callLgsFunc("Stack_addDefer", getFT(voidTy(), {ptrTy(), ptrTy()}), {deferFuncPtr, ctx});
}

void LgsLLVM::addPtrToVtable(Value* instancePtr, Value* name, Value* ptr) {
    callLgsFunc("Vtable_add", getFT(voidTy(), {ptrTy(), ptrTy(), ptrTy()}), {instancePtr, name, ptr});
}

Value* LgsLLVM::getPtrFromVtable(Value* instancePtr, Value* name) {
    return callLgsFunc("Vtable_get", getFT(ptrTy(), {ptrTy(), ptrTy()}), {instancePtr, name});
}

void LgsLLVM::addCoro(Value* coroPtr, Value* ctx) {
    callLgsFunc("Stack_addCoro", getFT(voidTy(), {ptrTy(), ptrTy()}), {coroPtr, ctx});
}

void LgsLLVM::callSpawn(Value* task, Value* ctx) {
    callLgsFunc("Scheduler_yield", getFT(voidTy(), {ptrTy(), ptrTy()}), {task, ctx});
}

void LgsLLVM::callYield() {
    callLgsFunc("Scheduler_yield", getFT(voidTy()), {});
}

void LgsLLVM::callShutdown() {
    callLgsFunc("Scheduler_shutdown", getFT(voidTy()), {});
}

Value* LgsLLVM::callHashStr(Value* value) {
    return callLgsFunc("hash", getFT(i32Ty(), {ptrTy()}), {value});
}

Type* LgsLLVM::i1Ty() {
    return IntegerType::getInt1Ty(context);
}

Type* LgsLLVM::i8Ty() {
    return IntegerType::getInt8Ty(context);
}

Type* LgsLLVM::i16Ty() {
    return IntegerType::getInt16Ty(context);
}

Type* LgsLLVM::i32Ty() {
    return IntegerType::getInt32Ty(context);
}

Type* LgsLLVM::i64Ty() {
    return IntegerType::getInt64Ty(context);
}

Type* LgsLLVM::floatTy() {
    return builder.getFloatTy();
}

Type* LgsLLVM::doubleTy() {
    return builder.getDoubleTy();
}

Type* LgsLLVM::voidTy() {
    return Type::getVoidTy(context);
}

Type* LgsLLVM::iNTy(const unsigned n) {
    return IntegerType::getIntNTy(context, n);
}

IntegerType* LgsLLVM::sizeTy() {
    return IRModule->getDataLayout().getIntPtrType(context);
}

PointerType* LgsLLVM::ptrTy() {
    return PointerType::getUnqual(context);
}

Value* LgsLLVM::null() {
    return ConstantPointerNull::get(ptrTy());
}

ConstantInt* LgsLLVM::i1(const bool v) {
    return builder.getInt1(v);
}

ConstantInt* LgsLLVM::i8(const int8_t v) {
    return builder.getInt8(v);
}

ConstantInt* LgsLLVM::i16(const int16_t v) {
    return builder.getInt16(v);
}

ConstantInt* LgsLLVM::i32(const int32_t v) {
    return builder.getInt32(v);
}

ConstantInt* LgsLLVM::i64(const int64_t v) {
    return builder.getInt64(v);
}

Constant* LgsLLVM::floatv(const float_t v) {
    return ConstantFP::get(floatTy(), v);
}

Constant* LgsLLVM::doublev(const double_t v) {
    return ConstantFP::get(doubleTy(), v);
}

ConstantInt* LgsLLVM::isize(const size_t v) {
    return ConstantInt::get(sizeTy(), v);
}

ConstantInt* LgsLLVM::i32Zero() {
    return builder.getInt32(0);
}

ConstantInt* LgsLLVM::i64Zero() {
    return builder.getInt64(0);
}

ConstantInt* LgsLLVM::sizeZero() {
    return ConstantInt::get(sizeTy(), 0);
}

ConstantInt* LgsLLVM::iN(const unsigned size, const size_t v) {
    return builder.getIntN(size, v);
}

TypeSize LgsLLVM::typeSize(StructType* v) const {
    return IRModule->getDataLayout().getTypeStoreSize(v);
}

void LgsLLVM::printPtr(Value* ptr, const std::string& text = "") {
    assert(ptr->getType()->isPointerTy());
    if (text != "") printStr(text);
    callPrintf({getIRStr(LGS_ANY.strFormatPart() + '\n'), ptr});
}

void LgsLLVM::printInt(Value* number, const std::string& text = "") {
    if (text != "") printStr(text);
    callPrintf({getIRStr("%d\n"), number});
}

void LgsLLVM::printStr(const std::string& str) {
    callPrintf({getIRStr("%s"), getIRStr(str)});
}

void LgsLLVM::initLLVM() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    LLVMInitializeAArch64TargetInfo();
}

TargetMachine* LgsLLVM::getTargetMachine() {
    std::string error;
    const auto targetTriple = sys::getDefaultTargetTriple();
    const auto target = TargetRegistry::lookupTarget(targetTriple, error);
    return target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), std::nullopt);
}

LgsLLVM::~LgsLLVM() {
    if (!diBuilder) return;
    diBuilder->finalize();
    std::error_code EC;
    raw_fd_ostream file("logosdbg.bc", EC, sys::fs::OF_None);
    WriteBitcodeToFile(*IRModule, file);
    file.flush();
    delete diBuilder;
    diBuilder = nullptr;
}
