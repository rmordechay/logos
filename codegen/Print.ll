; ModuleID = 'Print'
source_filename = "Print"

declare i32 @printf(ptr, ...)

@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00"

define void @printInt(i32 noundef %arg) {
  %2 = alloca i32, align 4
  store i32 %arg, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  %4 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %3)
  ret void
}