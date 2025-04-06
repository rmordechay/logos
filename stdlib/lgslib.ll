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

define i32 @hash_Str(ptr %str) {
entry:
    %hash = alloca i32, align 4
    store i32 2166136261, ptr %hash
    %i_ptr = alloca i64
    store i64 0, ptr %i_ptr
    br label %loop_condition

loop_condition:
    %i = load i64, ptr %i_ptr
    %char_ptr = getelementptr i8, ptr %str, i64 %i
    %current_char = load i8, ptr %char_ptr
    %is_null = icmp eq i8 %current_char, 0
    br i1 %is_null, label %loop_exit, label %loop_body

loop_body:
    %hash_value = load i32, ptr %hash
    %char_zext = zext i8 %current_char to i32
    %xored = xor i32 %hash_value, %char_zext
    %multiplied = mul i32 %xored, 16777619
    store i32 %multiplied, ptr %hash

    %next_i = add i64 %i, 1
    store i64 %next_i, ptr %i_ptr
    br label %loop_condition

loop_exit:
    %final = load i32, ptr %hash
    ret i32 %final
}
