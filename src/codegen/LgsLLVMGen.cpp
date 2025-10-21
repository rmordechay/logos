#include "data/LgsDefinitions.h"
#include "files/LgsFile.h"
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
    IRModule = new Module(file.path.filename().string(), context);
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

void LgsLLVMGen::loop(Value* loopLength, const std::function<void(Value*, BasicBlock*)>& body) {
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

void LgsLLVMGen::startBlock(BasicBlock* block) {
    block->insertInto(builder.GetInsertBlock()->getParent());
    builder.SetInsertPoint(block);
}

void LgsLLVMGen::branchAndStartBlock(BasicBlock* block) {
    branchIfNeeded(block);
    startBlock(block);
}

bool LgsLLVMGen::lastInstTerminator() const {
    return builder.GetInsertBlock()->getTerminator();
}

void LgsLLVMGen::createBoundsGuard(Value* len, Value* index) {
    const auto condition = builder.CreateICmpUGE(extendToSize(index), extendToSize(len));
    const auto validBlock = createBlock();
    const auto invalidBlock = createBlock();
    builder.CreateCondBr(condition, invalidBlock, validBlock);
    startBlock(invalidBlock);
    callFunc("Lgs_printError", voidTy(), {ptrTy()}, {getIRStr(E10003.msg)});
    callFunc("exit", voidTy(), {i32Ty()}, {i32(1)});
    branchAndStartBlock(validBlock);
}

FunctionType* LgsLLVMGen::getFT(Type* rt, const std::vector<Type*>& params, const bool isVariadic) {
    return FunctionType::get(rt, params, isVariadic);
}

Function* LgsLLVMGen::getFunc(const std::string& funcName, FunctionType* ft, const GlobalValue::LinkageTypes linkage) const {
    const auto func = IRModule->getFunction(funcName);
    if (func) return func;
    return Function::Create(ft, linkage, funcName, IRModule);
}

Value* LgsLLVMGen::callFunc(const std::string& funcName, FunctionType* ft, const std::vector<Value*>& args) {
    const auto func = IRModule->getOrInsertFunction(funcName, ft);
    return builder.CreateCall(func, args);
}

Value* LgsLLVMGen::callFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes, const std::vector<Value*>& args) {
    const auto func = IRModule->getOrInsertFunction(funcName, FunctionType::get(rt, paramTypes, false));
    return builder.CreateCall(func, args);
}

Value* LgsLLVMGen::callLgsFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes, const std::vector<Value*>& args) {
    return callFunc(LGS_RUNTIME_NAMES_PREFIX + funcName, rt, paramTypes, args);
}

Value* LgsLLVMGen::getPtrTo(Value* v) {
    if (const auto gepInst = dyn_cast<GetElementPtrInst>(v)) {
        const auto elementType = gepInst->getResultElementType();
        if (elementType && (elementType->isPointerTy() || elementType->isArrayTy())) {
            return builder.CreateLoad(ptrTy(), gepInst);
        }
        return v;
    }
    if (v->getType()->isPointerTy()) return v;
    if (v->getType()->isIntegerTy()) {
        return builder.CreateIntToPtr(v, ptrTy());
    }
    assert(0);
}

Value* LgsLLVMGen::callHash(Value* v) {
    return callLgsFunc("hash", i32Ty(), {ptrTy()}, {v});
}

Value* LgsLLVMGen::callPrintf(const std::vector<Value*>& args) {
    return callFunc("printf", getFT(i32Ty(), {ptrTy()}, true), args);
}

Value* LgsLLVMGen::callSprintf(const std::vector<Value*>& args) {
    return callFunc("sprintf", getFT(i32Ty(), {ptrTy()}, true), args);
}

Value* LgsLLVMGen::callStrLen(Value* str) {
    return callFunc("strlen", i64Ty(), {ptrTy()}, {str});
}

void LgsLLVMGen::callMemCpy(Value* dest, Value* src, Value* size) {
    const auto dataLayout = targetMachine->createDataLayout();
    const auto memCpy = Intrinsic::getDeclaration(IRModule, Intrinsic::memcpy, {ptrTy(), ptrTy(), sizeTy()});
    builder.CreateCall(memCpy, {dest, src, size, false_()});
}

Value* LgsLLVMGen::callMalloc(const size_t size, const bool isOwner, const Lgs_rttype type) {
    assert(type != RTT_UNKNOWN);
    const auto ptr = builder.CreateMalloc(sizeTy(), sizeTy(), usize(size), nullptr);
    if (isOwner) callLgsFunc("stack_addOwner", voidTy(), {ptrTy(), i32Ty()}, {ptr, i32(type)});
    else callLgsFunc("stack_addOrphan", voidTy(), {ptrTy(), i32Ty()}, {ptr, i32(type)});
    return ptr;
}

void LgsLLVMGen::callStackPush(const bool hasDefers, const bool needsCleanup) {
    if (needsCleanup || hasDefers) {
        callLgsFunc("stack_push", voidTy());
    }
}

void LgsLLVMGen::callPopStack(const bool hasDefers, const bool needsCleanup) {
    if (needsCleanup || hasDefers) {
        callLgsFunc("stack_pop", voidTy(), {i1Ty()}, {i1(needsCleanup)});
    }
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

ConstantInt* LgsLLVMGen::true_() {
    return builder.getTrue();
}

ConstantInt* LgsLLVMGen::false_() {
    return builder.getFalse();
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

Value* LgsLLVMGen::extendToSize(Value* v) {
    return builder.CreateZExt(v, sizeTy());
}

Constant* LgsLLVMGen::floatv(const float_t v) {
    return ConstantFP::get(floatTy(), v);
}

Constant* LgsLLVMGen::doublev(const double_t v) {
    return ConstantFP::get(doubleTy(), v);
}

TypeSize LgsLLVMGen::typeSize(Type* v) const {
    return IRModule->getDataLayout().getTypeStoreSize(v);
}

void LgsLLVMGen::printStr(const std::string& str) {
    callPrintf({getIRStr("%s"), getIRStr(str)});
}

void LgsLLVMGen::printPtr(Value* ptr, const std::string& text) {
    if (text != "") printStr(text);
    callPrintf({getIRStr("%p\n"), ptr});
}

void LgsLLVMGen::printInt(Value* number, const std::string& text) {
    if (text != "") printStr(text);
    callPrintf({getIRStr("%d\n"), number});
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
