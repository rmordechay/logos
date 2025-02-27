; ModuleID = 'Print'
source_filename = "Print"

declare i64 @printf(ptr, ...)

@formatInt = private constant [4 x i8] c"%d\0A\00"
@formatString = private constant [4 x i8] c"%s\0A\00"

define void @printInt(ptr noundef %x) {
  call i32 (ptr, ...) @printf(ptr noundef @formatInt, ptr noundef %x)
  ret void
}

define void @printString(i32 noundef %x) {
  call i32 (ptr, ...) @printf(ptr noundef @formatString, i32 noundef %x)
  ret void
}
