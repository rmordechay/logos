declare i32 @strcmp(ptr, ptr)
declare i32 @strlen(ptr)

@str1 = private constant [6 x i8] c"asdd\0A\00"
@str2 = private constant [6 x i8] c"asdd\0A\00"

define i1 @Str_compare_Str_Str(ptr %self, ptr %other) {
    %equal = call i32 @strcmp(ptr %self, ptr %other)
    %cmp = icmp eq i32 %equal, 0
    ret i1 %cmp
}

define i32 @Str_length_Str(ptr %self) {
    %len = call i32 @strlen(ptr %self)
    ret i32 %len
}