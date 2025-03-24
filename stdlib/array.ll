; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "arm64-apple-macosx14.0.0"

declare i32 @printf(ptr, ...)
declare ptr @malloc(i64)
declare ptr @realloc(ptr, i64)
declare void @free(ptr)

@str = private constant [4 x i8] c"%d\0A\00"
%arr = type {i32, i32, ptr}
%struct = type {i32, i32}


define ptr @get_capacity(ptr %arr_ptr) {
    %capacity_ptr = getelementptr %arr, ptr %arr_ptr, i32 0, i32 0
    ret ptr %capacity_ptr
}

define ptr @get_size(ptr %arr_ptr) {
    %size_ptr = getelementptr %arr, ptr %arr_ptr, i32 0, i32 1
    ret ptr %size_ptr
}

define ptr @get_data(ptr %arr_ptr) {
    %data_ptr = getelementptr %arr, ptr %arr_ptr, i32 0, i32 2
    ret ptr %data_ptr
}

define ptr @init_array(i32 %size) {
    %arr_ptr = call ptr @malloc(i64 16)

    %capacity_ptr = call ptr @get_capacity(ptr %arr_ptr)
    store i64 2, ptr %capacity_ptr

    %size_ptr = call ptr @get_size(ptr %arr_ptr)
    store i64 0, ptr %size_ptr

    %data_ptr = call ptr @malloc(i64 16)
    %element = call ptr @get_data(ptr %arr_ptr)
    store ptr %data_ptr, ptr %element

    ret ptr %arr_ptr
}

define void @resize_array(ptr %arr_ptr) {
    ret void
}

define void @add_element(ptr %arr_ptr, ptr %value) {
    %element = call ptr @get_data(ptr %arr_ptr)
    store ptr %element, ptr %value
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

    call i32 (ptr, ...) @printf(ptr @str, i32 %field_value)

    %arr = call ptr @init_array(ptr %arr_ptr, ptr %value, i32 8)
    call void @add_element(ptr )

    call void @free_arr(ptr %arr)

    ret i32 0
}