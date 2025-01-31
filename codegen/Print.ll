; ModuleID = 'Print'
source_filename = "Print"

declare i64 @write(i32, ptr, i32)

define void @printInt(ptr %arg, i32 %n) {
  call i64 @write(i32 1, ptr %arg, i32 %n)
  ret void
}