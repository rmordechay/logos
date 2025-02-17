; ModuleID = 'Print'
source_filename = "Print"

declare i64 @printf(ptr, ...)

@formatInt = private constant [4 x i8] c"%d\0A\00"

define void @printInt(i32 noundef %x) {
  %2 = alloca i32
  store i32 %x, ptr %2
  %3 = load i32, ptr %2
  %4 = call i32 (ptr, ...) @printf(ptr noundef @formatInt, i32 noundef %3)
  ret void
}
