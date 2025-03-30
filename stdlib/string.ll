declare i32 @strcmp(ptr, ptr)
declare i32 @strlen(ptr)

define i1 @Str_compare_Str_Str(ptr %self, ptr %other) {
    %equal = call i32 @strcmp(ptr %self, ptr %other)
    %cmp = icmp eq i32 %equal, 0
    ret i1 %cmp
}

define i32 @Str_len_Str(ptr %self) {
    %len = call i32 @strlen(ptr %self)
    ret i32 %len
}