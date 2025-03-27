; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "arm64-apple-macosx14.0.0"

declare i32 @printf(ptr, ...)
declare ptr @malloc(i64)
declare ptr @realloc(ptr, i64)
declare void @free(ptr)

@str = private constant [4 x i8] c"%d\0A\00"
%arr = type {i64, i64, ptr}

define ptr @get_cap(ptr %arr_ptr) {
    %cap_ptr = getelementptr %arr, ptr %arr_ptr, i32 0, i32 0
    ret ptr %cap_ptr
}

define ptr @get_size(ptr %arr_ptr) {
    %size_ptr = getelementptr %arr, ptr %arr_ptr, i32 0, i32 1
    ret ptr %size_ptr
}

define ptr @get_data(ptr %arr_ptr) {
    %data_ptr = getelementptr %arr, ptr %arr_ptr, i32 0, i32 2
    ret ptr %data_ptr
}

define ptr @ArrayType_initArr() {
    %arr_ptr = call ptr @malloc(i64 16)

    %cap_ptr = call ptr @get_cap(ptr %arr_ptr)
    store i64 2, ptr %cap_ptr

    %size_ptr = call ptr @get_size(ptr %arr_ptr)
    store i64 0, ptr %size_ptr

    %data_ptr = call ptr @malloc(i64 16)
    %element = call ptr @get_data(ptr %arr_ptr)
    store ptr %data_ptr, ptr %element

    ret ptr %arr_ptr
}

define void @ArrayType_add_ArrayType_Int(ptr %arr_ptr, i32 %new_elem) {
entry:
    %cap_ptr = call ptr @get_cap(ptr %arr_ptr)
    %size_ptr = call ptr @get_size(ptr %arr_ptr)
    %capacity = load i64, ptr %cap_ptr
    %size = load i64, ptr %size_ptr
    %data_ptr = call ptr @get_data(ptr %arr_ptr)
    %data = load ptr, ptr %data_ptr

    %cmp = icmp eq i64 %size, %capacity
    br i1 %cmp, label %resize, label %insert

resize:
    %new_cap = mul i64 %capacity, 2
    %new_data = call ptr @realloc(ptr %data_ptr, i64 %new_cap)
    store i64 %new_cap, ptr %cap_ptr
    store ptr %new_data, ptr %data_ptr
    br label %insert

insert:
    %data_final = load ptr, ptr %data_ptr
    %elem_ptr = getelementptr i32, ptr %data_final, i64 %size
    store i32 %new_elem, ptr %elem_ptr

    %new_size = add i64 %size, 1
    store i64 %new_size, ptr %size_ptr
    ret void
}

define void @ArrayType_freeArr_ArrayType(ptr %arr_ptr) {
    %data_field = getelementptr %arr, ptr %arr_ptr, i32 0, i32 2
    %data_ptr = load ptr, ptr %data_field
    call void @free(ptr %data_ptr)
    call void @free(ptr %arr_ptr)
    ret void
}

define void @ArrayType_getElement_ArrayType_Int() {
    %arr_ptr = call ptr @ArrayType_initArr()
    %data_ptr = call ptr @get_data(ptr %arr_ptr)
    %data = load ptr, ptr %data_ptr
    %index = add i32 0, 3
    %element_ptr = getelementptr i32, ptr %data, i32 %index
    %element = load i32, ptr %element_ptr
    call i32(ptr, ...) @printf(ptr @str, i32 %element)
    ret void
}
