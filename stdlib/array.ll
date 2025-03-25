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
%struct = type {i32, i32}


define ptr @get_capacity(ptr %arr_ptr) {
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

define ptr @init_array() {
    %arr_ptr = call ptr @malloc(i64 16)

    %cap_ptr = call ptr @get_capacity(ptr %arr_ptr)
    store i64 2, ptr %cap_ptr

    %size_ptr = call ptr @get_size(ptr %arr_ptr)
    store i64 0, ptr %size_ptr

    %data_ptr = call ptr @malloc(i64 16)
    %element = call ptr @get_data(ptr %arr_ptr)
    store ptr %data_ptr, ptr %element

    ret ptr %arr_ptr
}

define void @add_element(ptr %arr_ptr, ptr %new_elem) {
entry:
    %cap_ptr = call ptr @get_capacity(ptr %arr_ptr)
    %size_ptr = call ptr @get_size(ptr %arr_ptr)
    %data_ptr = call ptr @malloc(i64 16)
    %capacity = load i64, ptr %cap_ptr
    %size = load i64, ptr %size_ptr
    %data = load ptr, ptr %data_ptr

    %cmp = icmp eq i64 %size, %capacity
    br i1 %cmp, label %resize, label %insert

resize:
    %new_cap = mul i64 %size, 2
    %new_data = call ptr @realloc(ptr %data, i64 %new_cap)
    store i64 %new_cap, ptr %cap_ptr
    store ptr %new_data, ptr %data_ptr
    br label %insert

insert:
    %data_final = load ptr, ptr %data_ptr
    %offset = mul i64 %size, 8   ; Assuming elements are 8 bytes
    %elem_ptr = getelementptr i64, ptr %data_final, i64 %offset
    store ptr %new_elem, ptr %elem_ptr

    %new_size = add i64 %size, 1
    store i64 %new_size, ptr %size_ptr
    ret void
}

define void @free_arr(ptr %arr_ptr) {
    %data_field = getelementptr %arr, ptr %arr_ptr, i32 0, i32 2
    %data_ptr = load ptr, ptr %data_field
    call void @free(ptr %data_ptr)
    call void @free(ptr %arr_ptr)
    ret void
}

define i32 @main() {
    %obj = alloca %struct
    %field = getelementptr %struct, ptr %obj, i32 0, i32 0
    store i32 10, ptr %field
    %field_value = load i32, ptr %field

    %arr_ptr = call ptr @init_array()
    %new_elem = alloca i32
    store i32 8, ptr %new_elem
    call void @add_element(ptr %arr_ptr, ptr %new_elem)

    call void @free_arr(ptr %arr_ptr)
    ret i32 0
}