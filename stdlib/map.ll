declare ptr @malloc(i64)
declare ptr @realloc(ptr, i64)
declare void @free(ptr)
declare void @printf(ptr, ...)

%map_entry = type {ptr, ptr}
%map = type { [100 x %map_entry] }

@str = constant [3 x i8] c"ro\00"
@format = constant [4 x i8] c"%c\0A\00"
@format2 = constant [4 x i8] c"%d\0A\00"

define i32 @hash(ptr %key) {
entry:
    %hash_ptr = alloca i32
    store i32 5381, ptr %hash_ptr
    %hash_v = load i32, ptr %hash_ptr
    ret i32 0
}

define i32 @main() {
entry:
    %i_ptr = alloca i32
    store i32 0, ptr %i_ptr
    br label %loop_condition
loop_condition:
    %i = load i32, ptr %i_ptr
    %char_ptr = getelementptr inbounds i8, ptr @str, i32 %i
    %char = load i8, ptr %char_ptr
    %is_null = icmp eq i8 %char, 0
    br i1 %is_null, label %loop_exit, label %loop_body
loop_body:
    call void (ptr, ...) @printf(ptr @format2, i32 %i)
    call void (ptr, ...) @printf(ptr @format, i8 %char)
    %i_inc = add i32 %i, 1
    store i32 %i_inc, ptr %i_ptr
    br label %loop_condition
loop_exit:
    ret i32 0
}