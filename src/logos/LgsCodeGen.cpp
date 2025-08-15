#include "logos/LgsCodeGen.h"
#include "configs/LgsConfig.h"
#include "configs/LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include <llvm/Support/FileSystem.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/IR/DIBuilder.h>

void LgsCodeGen::setupModule(const std::string& moduleName, const DataLayout& dataLayout) {
    IRModule = new Module(moduleName, context);
    IRModule->setTargetTriple(sys::getDefaultTargetTriple());
    IRModule->setDataLayout(dataLayout);
    setRuntimePtr();
    if (isDebug) {
        diBuilder = new DIBuilder(*IRModule);
        const auto currentFunc = stack.currentFunc();
        const auto diFile = diBuilder->createFile(moduleName, "");
        const auto compileUnit = diBuilder->createCompileUnit(dwarf::DW_LANG_lo_user, diFile, "", false, "", 0);
        const auto dbInt32 = diBuilder->createBasicType("int", 32, dwarf::DW_ATE_signed);
        const auto subroutine = diBuilder->createSubroutineType(diBuilder->getOrCreateTypeArray({dbInt32}));
        const auto subprogram = diBuilder->createFunction(compileUnit, currentFunc->funcType->name, "", diFile, 1, subroutine, 1, DINode::FlagPrototyped, DISubprogram::SPFlagDefinition);
        currentFunc->getIRFunc(this)->setSubprogram(subprogram);
        const auto loc = DILocation::get(context, 1, 1, subprogram, subprogram->getScope());
        builder.SetCurrentDebugLocation(loc);
    }
}

void LgsCodeGen::setRuntimePtr() {
    const auto localsArr = ArrayType::get(ptrTy(), LOCALS_CAPACITY);
    const auto stackFrameStruct = getStructType({localsArr, i32Ty()}, "stack_frame_ty");
    const auto stackCapacity = ArrayType::get(stackFrameStruct, STACK_FRAMES_CAPACITY);
    const auto stackStruct = getStructType({stackCapacity, i32Ty()}, "stack_ty");
    const auto runtimeTy = getStructType({stackStruct}, "runtime_ty");
    if (IRModule->getName() == LGS_MAIN_FILE_NAME) {
        runtimePtr = createGlobal(runtimeTy, ConstantAggregateZero::get(runtimeTy), "runtime");
    } else {
        runtimePtr = createGlobal(runtimeTy, nullptr, "runtime");
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

BasicBlock* LgsCodeGen::createBlock(const std::string& name, Function* parent) {
    return BasicBlock::Create(context, name, parent);
}

void LgsCodeGen::branchIfNeeded(BasicBlock* block) {
    if (!lastInstTerminator()) {
        builder.CreateBr(block);
    }
}

void LgsCodeGen::branchAndStartBlock(BasicBlock* block) {
    branchIfNeeded(block);
    startBlock(block);
}

void LgsCodeGen::startBlock(BasicBlock* block) {
    block->insertInto(stack.currentFunc()->getIRFunc(this));
    builder.SetInsertPoint(block);
}

bool LgsCodeGen::lastInstTerminator() const {
    return builder.GetInsertBlock()->getTerminator();
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

void LgsCodeGen::callStackPush() {
    const auto ft = FunctionType::get(voidTy(), {ptrTy()}, false);
    callLgsFunc("Stack_push", ft, {runtimePtr});
}

void LgsCodeGen::callPopStack() {
    const auto ft = FunctionType::get(voidTy(), {ptrTy()}, false);
    callLgsFunc("Stack_pop", ft, {runtimePtr});
}

void LgsCodeGen::addDeferFunc(Value* deferFuncPtr, Value* ctx) {
    const auto ft = FunctionType::get(voidTy(), {ptrTy(), ptrTy(), ptrTy()}, false);
    callLgsFunc("Stack_addDefer", ft, {runtimePtr, deferFuncPtr, ctx});
}

void LgsCodeGen::callDefers() {
    branchAndStartBlock(createBlock(BLOCK_NAME_DEFER));
    const auto ft = FunctionType::get(voidTy(), false);
    callLgsFunc("Stack_callDefers", ft, {runtimePtr});
}

Value* LgsCodeGen::callMalloc(const size_t size) {
    return builder.CreateMalloc(sizeTy(), sizeTy(), isize(size), nullptr);
}

Value* LgsCodeGen::callPrintf(const std::vector<Value*>& args) {
    const auto ft = FunctionType::get(i32Ty(), {ptrTy()}, true);
    return callFunc("printf", ft, args);
}

Value* LgsCodeGen::callSnprintf(const std::vector<Value*>& args) {
    const auto ft = FunctionType::get(i32Ty(), {ptrTy(), i64Ty(), ptrTy()}, true);
    return callFunc("snprintf", ft, args);
}

Value* LgsCodeGen::callSleep(Value* time) {
    const auto ft = FunctionType::get(voidTy(), {sizeTy()}, false);
    return callFunc("sleep", ft, {time});
}

Value* LgsCodeGen::callExit(Value* exitCode) {
    const auto ft = FunctionType::get(voidTy(), {i32Ty()}, false);
    return callFunc("exit", ft, {exitCode});
}

Value* LgsCodeGen::callGetEnv(Value* name) {
    const auto ft = FunctionType::get(ptrTy(), {ptrTy()}, false);
    return callFunc("getenv", ft, {name});
}

Value* LgsCodeGen::callGetPid() {
    const auto ft = FunctionType::get(i32Ty(), false);
    return callFunc("getpid", ft);
}

Value* LgsCodeGen::callCoresNum() {
    const auto ft = FunctionType::get(i64Ty(), {i32Ty()}, false);
    return callFunc("sysconf", ft, {i32(58)});
}

Value* LgsCodeGen::callCwd() {
    const auto ft = FunctionType::get(voidTy(), {i32Ty()}, false);
    const auto value = builder.CreateAlloca(ArrayType::get(i8Ty(), 1024));
    callFunc("getcwd", ft, {value});
    return value;
}

void LgsCodeGen::callCopyMem(Value* src, Value* dest, const size_t n) {
    const auto memCpy = Intrinsic::getDeclaration(IRModule, Intrinsic::memcpy, {ptrTy(), ptrTy(), ptrTy()});
    builder.CreateCall(memCpy, {dest, src, i64(n), builder.getFalse()});
}

Value* LgsCodeGen::callStrLen(Value* str) {
    const auto ft = FunctionType::get(i64Ty(), {ptrTy()}, false);
    return callFunc("strlen", ft, {str});
}

Value* LgsCodeGen::callHashStr(Value* value) {
    return callLgsFunc("hash", FunctionType::get(i32Ty(), {ptrTy()}, false), {value});
}

Value* LgsCodeGen::callCoroIDFunc() {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_id);
    return builder.CreateCall(func, {i32Zero(), null(), null(), null()});
}

Value* LgsCodeGen::callCoroBeginFunc(Value* coroID, Value* frameSize) {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_begin);
    const auto sizeValue = builder.CreateMalloc(i32Ty(), i8Ty(), frameSize, nullptr);
    return builder.CreateCall(func, {coroID, sizeValue});
}

Value* LgsCodeGen::callCoroSizeFunc() {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_size, {i32Ty()});
    return builder.CreateCall(func);
}

Value* LgsCodeGen::callSuspendFunc() {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_suspend);
    return builder.CreateCall(func, {ConstantTokenNone::get(context), builder.getFalse()});
}

Value* LgsCodeGen::callResumeFunc(Value* handle) {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_resume);
    return builder.CreateCall(func, {handle});
}

Value* LgsCodeGen::callCoroEndFunc(Value* handle) {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_end);
    return builder.CreateCall(func, {handle, builder.getFalse(), ConstantTokenNone::get(context)});
}

Value* LgsCodeGen::callCoroDestroyFunc(Value* handle) {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_destroy);
    return builder.CreateCall(func, {handle});
}

void LgsCodeGen::storeValueInStruct(StructType* ty, Value* ptr, const int i, Value* v) {
    const auto fieldPtr = builder.CreateStructGEP(ty, ptr, i);
    builder.CreateStore(v, fieldPtr);
}

Value* LgsCodeGen::loadValueFromStruct(Type* ty, Value* ptr, const int i) {
    const auto gep = builder.CreateStructGEP(ty, ptr, i);
    return builder.CreateLoad(ty->getStructElementType(i), gep);
}

PointerType* LgsCodeGen::ptrTy() {
    return PointerType::getUnqual(context);
}

Value* LgsCodeGen::null() {
    return ConstantPointerNull::get(ptrTy());
}

IntegerType* LgsCodeGen::sizeTy() {
    return IRModule->getDataLayout().getIntPtrType(context);
}

Type* LgsCodeGen::iNTy(const unsigned n) {
    return IntegerType::getIntNTy(context, n);
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

Type* LgsCodeGen::voidTy() {
    return Type::getVoidTy(context);
}

ConstantInt* LgsCodeGen::iN(const unsigned size, const size_t v) {
    return builder.getIntN(size, v);
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

ConstantInt* LgsCodeGen::isize(const size_t v) {
    return ConstantInt::get(sizeTy(), v);
}

TypeSize LgsCodeGen::typeSize(StructType* v) const {
    return IRModule->getDataLayout().getTypeStoreSize(v);
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

LgsCodeGen::~LgsCodeGen() {
    if (diBuilder) {
        assert(isDebug);
        diBuilder->finalize();
        std::error_code EC;
        raw_fd_ostream file("logosdbg.bc", EC, sys::fs::OF_None);
        WriteBitcodeToFile(*IRModule, file);
        file.flush();
        delete diBuilder;
        diBuilder = nullptr;
    }
}
