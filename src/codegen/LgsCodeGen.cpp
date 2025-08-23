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
#include <llvm/Target/TargetOptions.h>

void LgsCodeGen::setupModule(const LgsFile& file, const DataLayout& dataLayout, const bool debugMode) {
    IRModule = new Module(file.name, context);
    IRModule->setTargetTriple(sys::getDefaultTargetTriple());
    IRModule->setDataLayout(dataLayout);
    if (debugMode) {
        diBuilder = new DIBuilder(*IRModule);
        diFile = diBuilder->createFile(file.path.string(), "");
        compileUnit = diBuilder->createCompileUnit(dwarf::DW_LANG_lo_user, diFile, "", false, "", 0);
        IRModule->addModuleFlag(Module::Warning, "Dwarf Version", 5);
        IRModule->addModuleFlag(Module::Warning, "Debug Info Version", DEBUG_METADATA_VERSION);
    }
}

Value* LgsCodeGen::getIRStr(const std::string& value) {
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

GlobalVariable* LgsCodeGen::createGlobal(Type* type, ConstantAggregateZero* zeroInit, const std::string& name) const {
    return new GlobalVariable(*IRModule, type, false, GlobalValue::ExternalLinkage, zeroInit, name);
}

StructType* LgsCodeGen::getStructType(const std::vector<Type*>& fields, const std::string& name) {
    const auto structType = StructType::getTypeByName(context, name);
    if (!structType) {
        return StructType::create(context, fields, name);
    }
    return structType;
}

void LgsCodeGen::storeValueInStruct(StructType* ty, Value* ptr, const int i, Value* v) {
    const auto fieldPtr = builder.CreateStructGEP(ty, ptr, i);
    builder.CreateStore(v, fieldPtr);
}

Value* LgsCodeGen::loadValueFromStruct(Type* ty, Value* ptr, const int i) {
    const auto gep = builder.CreateStructGEP(ty, ptr, i);
    return builder.CreateLoad(ty->getStructElementType(i), gep);
}

BasicBlock* LgsCodeGen::createBlock(const std::string& name, Function* parent) {
    return BasicBlock::Create(context, name, parent);
}

void LgsCodeGen::branchIfNeeded(BasicBlock* block) {
    if (!lastInstTerminator()) {
        builder.CreateBr(block);
    }
}

bool LgsCodeGen::lastInstTerminator() const {
    return builder.GetInsertBlock()->getTerminator();
}

FunctionType* LgsCodeGen::getFT(Type* rt, const std::vector<Type*>& params, const bool isVariadic) {
    return FunctionType::get(rt, params, isVariadic);
}

Function* LgsCodeGen::getFunc(const std::string& funcName, FunctionType* ft, GlobalValue::LinkageTypes linkage) const {
    const auto func = IRModule->getFunction(funcName);
    if (func) return func;
    return Function::Create(ft, linkage, funcName, IRModule);
}

Value* LgsCodeGen::callFunc(const std::string& funcName, FunctionType* ft, const std::vector<Value*>& args) {
    const auto func = getFunc(funcName, ft);
    return builder.CreateCall(func, args);
}

Value* LgsCodeGen::callLgsFunc(const std::string& funcName, FunctionType* ft, const std::vector<Value*>& args) {
    return callFunc(LGS_RUNTIME_NAMES_PREFIX + funcName, ft, args);
}

Value* LgsCodeGen::callMalloc(const size_t size) {
    return builder.CreateMalloc(sizeTy(), sizeTy(), isize(size), nullptr);
}

Value* LgsCodeGen::callPrintf(const std::vector<Value*>& args) {
    return callFunc("printf", getFT(i32Ty(), {ptrTy()}, true), args);
}

Value* LgsCodeGen::callSleep(Value* time) {
    return callFunc("sleep", getFT(i32Ty(), {i32Ty()}), {time});
}

Value* LgsCodeGen::callExit(Value* exitCode) {
    return callFunc("exit", getFT(voidTy(), {i32Ty()}), {exitCode});
}

Value* LgsCodeGen::callGetEnv(Value* name) {
    return callFunc("getenv", getFT(ptrTy(), {ptrTy()}), {name});
}

Value* LgsCodeGen::callGetPid() {
    return callFunc("getpid", getFT(i32Ty()));
}

Value* LgsCodeGen::callCwd() {
    const auto value = builder.CreateAlloca(ArrayType::get(i8Ty(), 1024));
    callFunc("getcwd", getFT(voidTy(), {i32Ty()}), {value});
    return value;
}

Value* LgsCodeGen::callCoresNum() {
    return callFunc("sysconf", getFT(i64Ty(), {i32Ty()}), {i32(58)});
}

Value* LgsCodeGen::callStrLen(Value* str) {
    return callFunc("strlen", getFT(i64Ty(), {ptrTy()}), {str});
}

Value* LgsCodeGen::callSqrt(Value* radicant) {
    auto d = builder.CreateSIToFP(radicant, doubleTy());
    return callFunc("sqrt", getFT(doubleTy(), {doubleTy()}), {d});
}

void LgsCodeGen::callCopyMem(Value* src, Value* dest, const size_t n) {
    const auto memCpy = Intrinsic::getDeclaration(IRModule, Intrinsic::memcpy, {ptrTy(), ptrTy(), ptrTy()});
    builder.CreateCall(memCpy, {dest, src, i64(n), builder.getFalse()});
}

void LgsCodeGen::callRuntimeInit() {
    callLgsFunc("Runtime_init", getFT(voidTy()));
}

void LgsCodeGen::callStackPush() {
    callLgsFunc("Stack_push", getFT(voidTy()));
}

void LgsCodeGen::callPopStack() {
    callLgsFunc("Stack_pop", getFT(voidTy()));
}

void LgsCodeGen::callDefers() {
    const auto ft = getFT(voidTy());
    callLgsFunc("Stack_callDefers", ft);
}

void LgsCodeGen::addDeferFunc(Value* deferFuncPtr, Value* ctx) {
    callLgsFunc("Stack_addDefer", getFT(voidTy(), {ptrTy(), ptrTy()}), {deferFuncPtr, ctx});
}

void LgsCodeGen::addPtrToVtable(Value* instancePtr, Value* name, Value* ptr) {
    callLgsFunc("Vtable_add", getFT(voidTy(), {ptrTy(), ptrTy(), ptrTy()}), {instancePtr, name, ptr});
}

Value* LgsCodeGen::getPtrFromVtable(Value* instancePtr, Value* name) {
    return callLgsFunc("Vtable_get", getFT(ptrTy(), {ptrTy(), ptrTy()}), {instancePtr, name});
}

void LgsCodeGen::addCoro(Value* coroPtr, Value* ctx) {
    callLgsFunc("Stack_addCoro", getFT(voidTy(), {ptrTy(), ptrTy()}), {coroPtr, ctx});
}

void LgsCodeGen::callSpawn(Value* task, Value* ctx) {
    callLgsFunc("Scheduler_yield", getFT(voidTy(), {ptrTy(), ptrTy()}), {task, ctx});
}

void LgsCodeGen::callYield() {
    callLgsFunc("Scheduler_yield", getFT(voidTy()), {});
}

void LgsCodeGen::callShutdown() {
    callLgsFunc("Scheduler_shutdown", getFT(voidTy()), {});
}

Value* LgsCodeGen::callHashStr(Value* value) {
    return callLgsFunc("hash", getFT(i32Ty(), {ptrTy()}), {value});
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

Type* LgsCodeGen::iNTy(const unsigned n) {
    return IntegerType::getIntNTy(context, n);
}

IntegerType* LgsCodeGen::sizeTy() {
    return IRModule->getDataLayout().getIntPtrType(context);
}

PointerType* LgsCodeGen::ptrTy() {
    return PointerType::getUnqual(context);
}

Value* LgsCodeGen::null() {
    return ConstantPointerNull::get(ptrTy());
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

Constant* LgsCodeGen::floatv(const float_t v) {
    return ConstantFP::get(floatTy(), v);
}

Constant* LgsCodeGen::doublev(const double_t v) {
    return ConstantFP::get(doubleTy(), v);
}

ConstantInt* LgsCodeGen::isize(const size_t v) {
    return ConstantInt::get(sizeTy(), v);
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

ConstantInt* LgsCodeGen::iN(const unsigned size, const size_t v) {
    return builder.getIntN(size, v);
}

TypeSize LgsCodeGen::typeSize(StructType* v) const {
    return IRModule->getDataLayout().getTypeStoreSize(v);
}

void LgsCodeGen::printPtr(Value* ptr, const std::string& text = "") {
    assert(ptr->getType()->isPointerTy());
    if (text != "") printStr(text);
    callPrintf({getIRStr(LGS_ANY.strFormatPart() + '\n'), ptr});
}

void LgsCodeGen::printInt(Value* number, const std::string& text = "") {
    if (text != "") printStr(text);
    callPrintf({getIRStr("%d\n"), number});
}

void LgsCodeGen::printStr(const std::string& str) {
    callPrintf({getIRStr("%s"), getIRStr(str)});
}

void LgsCodeGen::initLLVM() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    LLVMInitializeAArch64TargetInfo();
}

TargetMachine* LgsCodeGen::getTargetMachine() {
    std::string error;
    const auto targetTriple = sys::getDefaultTargetTriple();
    const auto target = TargetRegistry::lookupTarget(targetTriple, error);
    return target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), std::nullopt);
}

LgsCodeGen::~LgsCodeGen() {
    if (!diBuilder) return;
    diBuilder->finalize();
    std::error_code EC;
    raw_fd_ostream file("logosdbg.bc", EC, sys::fs::OF_None);
    WriteBitcodeToFile(*IRModule, file);
    file.flush();
    delete diBuilder;
    diBuilder = nullptr;
}
