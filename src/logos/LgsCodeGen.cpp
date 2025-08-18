#include "logos/LgsCodeGen.h"
#include "configs/LgsConfig.h"
#include "configs/LgsDefinitions.h"
#include "exprs/unary/LgsFuncCall.h"
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

void LgsCodeGen::setupModule(const std::string& moduleName, const DataLayout& dataLayout) {
    IRModule = new Module(moduleName, context);
    IRModule->setTargetTriple(sys::getDefaultTargetTriple());
    IRModule->setDataLayout(dataLayout);
    if (debugger.isDebugMode) {
        debugger.diBuilder = new DIBuilder(*IRModule);
        debugger.diFile = debugger.diBuilder->createFile(moduleName, "");
        debugger.compileUnit = debugger.diBuilder->createCompileUnit(dwarf::DW_LANG_lo_user, debugger.diFile, "", false, "", 0);
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

void LgsCodeGen::startBlock(BasicBlock* block) {
    block->insertInto(stack.currentFunc()->getIRFunc(this));
    builder.SetInsertPoint(block);
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

Function* LgsCodeGen::getThunkFunc(const LgsFuncCall* fc, Type* ctxTy) {
    auto func = IRModule->getFunction(fc->name + "_thunk");
    if (func) return func;

    savedIP = builder.saveIP();
    const auto ft = FunctionType::get(voidTy(), {ptrTy()}, false);
    func = Function::Create(ft, Function::PrivateLinkage, fc->name + "_thunk", IRModule);
    const auto entryBlock = BasicBlock::Create(context, BLOCK_NAME_ENTRY);
    entryBlock->insertInto(func);
    builder.SetInsertPoint(entryBlock);

    std::vector<Value*> args;
    for (int i = 0; i < fc->args.size(); i++) {
        const auto fieldTy = dyn_cast<StructType>(ctxTy)->getElementType(i);
        const auto fieldPtr = builder.CreateStructGEP(ctxTy, func->arg_begin(), i);
        const auto v = builder.CreateLoad(fieldTy, fieldPtr);
        args.push_back(v);
    }
    const auto deferFunc = fc->func->getIRFunc(this);
    builder.CreateCall(deferFunc, args);
    builder.CreateRetVoid();

    builder.restoreIP(savedIP);
    return func;
}

Value* LgsCodeGen::getThunkCtxValue(const LgsFuncCall* fc, Type* ctxTy) {
    if (fc->args.empty()) return null();
    const auto ctx = builder.CreateAlloca(ctxTy);
    for (int i = 0; i < fc->args.size(); i++) {
        const auto v = fc->args[i]->getIRValue(this);
        storeValueInStruct(dyn_cast<StructType>(ctxTy), ctx, i, v);
    }
    return ctx;
}

Type* LgsCodeGen::getThunkCtxType(const LgsFuncCall* fc) {
    if (fc->args.empty()) return ptrTy();
    std::vector<Value*> args;
    std::vector<Type*> types;
    for (const auto& arg : fc->args) {
        types.push_back(arg->type->getIRType(this));
    }
    return getStructType(types, fc->name + "_thunk_type");
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

Value* LgsCodeGen::callCwd() {
    const auto ft = FunctionType::get(voidTy(), {i32Ty()}, false);
    const auto value = builder.CreateAlloca(ArrayType::get(i8Ty(), 1024));
    callFunc("getcwd", ft, {value});
    return value;
}

Value* LgsCodeGen::callCoresNum() {
    const auto ft = FunctionType::get(i64Ty(), {i32Ty()}, false);
    return callFunc("sysconf", ft, {i32(58)});
}

Value* LgsCodeGen::callStrLen(Value* str) {
    const auto ft = FunctionType::get(i64Ty(), {ptrTy()}, false);
    return callFunc("strlen", ft, {str});
}

Value* LgsCodeGen::callSqrt(Value* radicant) {
    auto d = builder.CreateSIToFP(radicant, doubleTy());
    const auto ft = FunctionType::get(doubleTy(), {doubleTy()}, false);
    return callFunc("sqrt", ft, {d});
}

void LgsCodeGen::callCopyMem(Value* src, Value* dest, const size_t n) {
    const auto memCpy = Intrinsic::getDeclaration(IRModule, Intrinsic::memcpy, {ptrTy(), ptrTy(), ptrTy()});
    builder.CreateCall(memCpy, {dest, src, i64(n), builder.getFalse()});
}

void LgsCodeGen::callStackPush() {
    callLgsFunc("Stack_push", FunctionType::get(voidTy(), false));
}

void LgsCodeGen::callPopStack() {
    callLgsFunc("Stack_pop", FunctionType::get(voidTy(), false));
}

void LgsCodeGen::callDefers() {
    branchAndStartBlock(createBlock(BLOCK_NAME_DEFER));
    const auto ft = FunctionType::get(voidTy(), false);
    callLgsFunc("Stack_callDefers", ft);
}

void LgsCodeGen::addDeferFunc(Value* deferFuncPtr, Value* ctx) {
    const auto ft = FunctionType::get(voidTy(), {ptrTy(), ptrTy()}, false);
    callLgsFunc("Stack_addDefer", ft, {deferFuncPtr, ctx});
}

void LgsCodeGen::addCoro(Value* coroPtr, Value* ctx) {
    const auto ft = FunctionType::get(voidTy(), {ptrTy(), ptrTy()}, false);
    callLgsFunc("Stack_addCoro", ft, {coroPtr, ctx});
}

Value* LgsCodeGen::callCoroIDFunc() {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_id);
    return builder.CreateCall(func, {i32Zero(), null(), null(), null()});
}

Value* LgsCodeGen::callSuspendFunc() {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_suspend);
    return builder.CreateCall(func, {ConstantTokenNone::get(context), builder.getFalse()});
}

Value* LgsCodeGen::callResumeFunc(Value* handle) {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_resume);
    return builder.CreateCall(func, {handle});
}

Value* LgsCodeGen::callCoroSizeFunc() {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_size, {i32Ty()});
    return builder.CreateCall(func);
}

Value* LgsCodeGen::callCoroBeginFunc(Value* coroID, Value* frameSize) {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_begin);
    const auto sizeValue = builder.CreateMalloc(i32Ty(), i8Ty(), frameSize, nullptr);
    return builder.CreateCall(func, {coroID, sizeValue});
}

Value* LgsCodeGen::callCoroEndFunc(Value* handle) {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_end);
    return builder.CreateCall(func, {handle, builder.getFalse(), ConstantTokenNone::get(context)});
}

Value* LgsCodeGen::callCoroDestroyFunc(Value* handle) {
    const auto func = Intrinsic::getDeclaration(IRModule, Intrinsic::coro_destroy);
    return builder.CreateCall(func, {handle});
}

Value* LgsCodeGen::callHashStr(Value* value) {
    return callLgsFunc("hash", FunctionType::get(i32Ty(), {ptrTy()}, false), {value});
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
    if (debugger.diBuilder) {
        assert(debugger.isDebugMode);
        debugger.diBuilder->finalize();
        std::error_code EC;
        raw_fd_ostream file("logosdbg.bc", EC, sys::fs::OF_None);
        WriteBitcodeToFile(*IRModule, file);
        file.flush();
        delete debugger.diBuilder;
        debugger.diBuilder = nullptr;
    }
}
