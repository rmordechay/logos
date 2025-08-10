#include "logos/LgsCodeGen.h"
#include "funcs/LgsFunc.h"
#include "logos/LgsPaths.h"
#include "types/LgsAny.h"
#include "utils/LgsUtils.h"

void LgsCodeGen::setIRModule(const string& moduleName) {
    const auto module = new Module(moduleName, context);
    module->setTargetTriple(sys::getDefaultTargetTriple());
    module->setDataLayout(getTargetMachine()->createDataLayout());
    IRModule = module;
}

GlobalVariable* LgsCodeGen::createPrivateGlobal(Constant* initializer) const {
    return new GlobalVariable(*IRModule, initializer->getType(), true, GlobalValue::PrivateLinkage, initializer);
}

GlobalVariable* LgsCodeGen::createPublicGlobal(Type* type) const {
    const auto zeroInitializer = ConstantAggregateZero::get(type);
    return new GlobalVariable(*IRModule, type, false, GlobalValue::ExternalLinkage, zeroInitializer);
}

Value* LgsCodeGen::getIRStr(const string& value) {
    for (auto& globals : IRModule->globals()) {
        if (!globals.hasInitializer()) continue;
        const auto dataArray = dyn_cast<ConstantDataArray>(globals.getInitializer());
        if (!dataArray || !dataArray->isCString() || dataArray->getAsCString() != value) continue;
        return &globals;
    }
    const auto strConstant = ConstantDataArray::getString(context, value, true);
    const auto globalVariable = createPrivateGlobal(strConstant);
    globalVariable->setUnnamedAddr(GlobalValue::UnnamedAddr::Global);
    return globalVariable;
}

StructType* LgsCodeGen::getIRStructType(const string& name, const vector<Type*>& fields) {
    const auto structType = StructType::getTypeByName(context, name);
    if (!structType) {
        return StructType::create(context, fields, name);
    }
    return structType;
}

BasicBlock* LgsCodeGen::createBlock(const string& name, Function* parent) {
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

void LgsCodeGen::callCopyMem(Value* src, Value* dest, const size_t n) {
    const auto memCpy = Intrinsic::getDeclaration(IRModule, Intrinsic::memcpy, {ptrTy(), ptrTy(), ptrTy()});
    builder.CreateCall(memCpy, {dest, src, i64(n), builder.getFalse()});
}

Value* LgsCodeGen::callPrintf(const vector<Value*>& args) {
    const auto ft = FunctionType::get(i32Ty(), {ptrTy()}, true);
    return callFunc("printf", ft, args);
}

Value* LgsCodeGen::callSnprintf(const vector<Value*>& args) {
    const auto ft = FunctionType::get(i32Ty(), {ptrTy(), i64Ty(), ptrTy()}, true);
    return callFunc("snprintf", ft, args);
}

Value* LgsCodeGen::callStrHash(Value* value) {
    const auto ft = FunctionType::get(i32Ty(), {ptrTy()}, false);
    return callFunc("Str_hash", ft, {value});
}

Value* LgsCodeGen::callFunc(const string& funcName, FunctionType* ft, const vector<Value*>& args) {
    const auto func = IRModule->getOrInsertFunction(funcName, ft);
    return builder.CreateCall(func, args);
}

Value* LgsCodeGen::callMalloc(const size_t size) {
    return builder.CreateMalloc(sizeTy(), sizeTy(), isize(size), nullptr);
}

void LgsCodeGen::callPrintError(const string& msg) {
    const auto ft = FunctionType::get(voidTy(), {ptrTy()}, false);
    const auto func = IRModule->getOrInsertFunction("print_error", ft);
    builder.CreateCall(func, {getIRStr(msg)});
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

Value* LgsCodeGen::callBeginFunc(Value* coroID, Value* frameSize) {
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

PointerType* LgsCodeGen::ptrTy() {
    return PointerType::getUnqual(context);
}

Value* LgsCodeGen::null() {
    return ConstantPointerNull::get(ptrTy());
}

IntegerType* LgsCodeGen::sizeTy() {
    return IRModule->getDataLayout().getIntPtrType(context);
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

void LgsCodeGen::printPtr(Value* ptr, const string& text = "") {
    assert(ptr->getType()->isPointerTy());
    if (text != "") printStr(text);
    callPrintf({getIRStr(LGS_ANY.getStrFormatPart() + '\n'), ptr});
}

void LgsCodeGen::printInt(Value* number, const string& text = "") {
    if (text != "") printStr(text);
    callPrintf({getIRStr("%d\n"), number});
}

void LgsCodeGen::printStr(const string& str) {
    callPrintf({getIRStr("%s"), getIRStr(str)});
}

void LgsCodeGen::initLLVM() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    LLVMInitializeAArch64TargetInfo();
    findLibC();
}

TargetMachine* LgsCodeGen::getTargetMachine() {
    if (targetMachine) return targetMachine;
    const auto targetTriple = sys::getDefaultTargetTriple();
    string error;
    const auto target = TargetRegistry::lookupTarget(targetTriple, error);
    lock_guard lock(mtx);
    targetMachine = target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), nullopt);
    return targetMachine;
}
