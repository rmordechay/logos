declare i32 @printf(ptr, ...)

@formatInt = private constant [4 x i8] c"%d\0A\00"
@formatLong = private constant [5 x i8] c"%ld\0A\00"
@formatFloat = private constant [4 x i8] c"%f\0A\00"
@formatString = private constant [4 x i8] c"%s\0A\00"
@formatChar = private constant [4 x i8] c"%c\0A\00"
@formatPtr = private constant [4 x i8] c"%p\0A\00"

define void @print_Int(i32 noundef %x) {
  call void (ptr, ...) @printf(ptr noundef @formatInt, i32 noundef %x)
  ret void
}

define void @print_Long(i64 noundef %x) {
  call void (ptr, ...) @printf(ptr noundef @formatLong, i64 noundef %x)
  ret void
}

define void @print_Float(float noundef %x) {
  call void (ptr, ...) @printf(ptr noundef @formatFloat, float noundef %x)
  ret void
}

define void @print_Str(ptr noundef %x) {
  call void (ptr, ...) @printf(ptr noundef @formatString, ptr noundef %x)
  ret void
}

define void @print_Char(i8 noundef %x) {
  call void (ptr, ...) @printf(ptr noundef @formatChar, i8 noundef %x)
  ret void
}

define void @print_Bool(i1 noundef %x) {
  call void (ptr, ...) @printf(ptr noundef @formatInt, i1 noundef %x)
  ret void
}

define void @print_Ptr(ptr noundef %x) {
  call void (ptr, ...) @printf(ptr noundef @formatPtr, ptr noundef %x)
  ret void
}
