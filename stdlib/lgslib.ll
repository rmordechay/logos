; ModuleID = 'stdlib'

declare i64 @printf(ptr, ...)

@formatInt = private constant [4 x i8] c"%d\0A\00"
@formatString = private constant [4 x i8] c"%s\0A\00"

define void @print_Void_Int(ptr noundef %x) {
  call i32 (ptr, ...) @printf(ptr noundef @formatInt, ptr noundef %x)
  ret void
}

define void @print_Void_Str(i32 noundef %x) {
  call i32 (ptr, ...) @printf(ptr noundef @formatString, i32 noundef %x)
  ret void
}

define i1 @Int_isOdd_Bool(i32 %n) {
entry:
  %rem = and i32 %n, 1
  %result = icmp ne i32 %rem, 0
  ret i1 %result
}

define i1 @Int_isEven_Bool(i32 %n) {
entry:
  %rem = and i32 %n, 1
  %result = icmp eq i32 %rem, 0
  ret i1 %result
}

define i1 @Str_isAscii_Bool(ptr %str) {
entry:
  %ch = load i8, ptr %str
  %cmp = icmp ult i8 %ch, 128
  ret i1 %cmp
}