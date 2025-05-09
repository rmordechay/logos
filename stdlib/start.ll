declare i32 @main(i32, ptr)
declare void @exit(i32) noreturn

define void @_start() {
entry:
  %argc = alloca i32
  store i32 0, ptr %argc
  %argv = alloca ptr
  store ptr null, ptr %argv
  %argc_val = load i32, ptr %argc
  %argv_val = load ptr, ptr %argv
  %ret = call i32 @main(i32 %argc_val, ptr %argv_val)
  call void @exit(i32 %ret)
  unreachable
}