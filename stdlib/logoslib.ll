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

define i1 @isOdd(i32 %n) {
entry:
  %rem = and i32 %n, 1
  %result = icmp ne i32 %rem, 0
  ret i1 %result
}
