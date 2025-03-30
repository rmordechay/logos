declare i32 @strcmp(ptr, ptr)

declare void @print_Char(i8)
declare void @print_Bool(i1 %x)

@str1 = private constant [6 x i8] c"asdd\0A\00"
@str2 = private constant [6 x i8] c"asdd\0A\00"

define i1 @Str_compare(ptr %self, ptr %other) {
    %equal = call i32 @strcmp(ptr %self, ptr %other)
    %cmp = icmp eq i32 %equal, 0
    ret i1 %cmp
}