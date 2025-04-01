declare ptr @malloc(i64)
declare ptr @realloc(ptr, i64)
declare void @free(ptr)
declare void @printf(ptr, ...)

%map_entry = type {ptr, ptr}
%map = type { [100 x %map_entry] }

@str = constant [4 x i8] c"ro\0A\00"
@format = constant [4 x i8] c"%s\0A\00"

define i32 @hash(ptr %key) {
entry:
    %hash_ptr = alloca i32
    store i32 5381, ptr %hash_ptr
    %hash_v = load i32, ptr %hash_ptr
    ret i32 0
}

define i32 @main() {
    %map_ptr = alloca %map
    call void (ptr, ...) @printf(ptr @format, ptr @str)
    ret i32 0
}