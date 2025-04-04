declare ptr @malloc(i64)
declare ptr @realloc(ptr, i64)
declare void @free(ptr)

%arr = type {i64, i64, ptr}

define ptr @ArrayType_initArr_Long(i64 %initial_cap) {
    %self = call ptr @malloc(i64 16)
    %cap_ptr = call ptr @get_cap(ptr %self)
    %size_ptr = call ptr @get_size(ptr %self)
    %cmp = icmp sgt i64 %initial_cap, 0
    br i1 %cmp, label %init_with_initial_cap, label %init_with_default_cap

init_with_initial_cap:
    store i64 %initial_cap, ptr %cap_ptr
    br label %init_array

init_with_default_cap:
    store i64 2, ptr %cap_ptr
    br label %init_array

init_array:
    store i64 0, ptr %size_ptr
    %cap = load i64, ptr %cap_ptr
    %data_size = mul i64 %cap, 4
    %data = call ptr @malloc(i64 %data_size)
    %data_ptr = call ptr @get_data(ptr %self)
    store ptr %data, ptr %data_ptr

    ret ptr %self
}

define ptr @ArrayType_getElement_ArrayType_Int(ptr %self, i32 %index) {
entry:
    %data_ptr = call ptr @get_data(ptr %self)
    %element_ptr = getelementptr ptr, ptr %data_ptr, i32 %index
    %element = load ptr, ptr %element_ptr
    ret ptr %element
}

define void @ArrayType_add_ArrayType_Int(ptr %self, ptr %new_elem) {
entry:
    %cap_ptr = call ptr @get_cap(ptr %self)
    %size_ptr = call ptr @get_size(ptr %self)
    %data_ptr = call ptr @get_data(ptr %self)
    %capacity = load i64, ptr %cap_ptr
    %size = load i64, ptr %size_ptr

    %cmp = icmp eq i64 %size, %capacity
    br i1 %cmp, label %resize, label %insert

resize:
    %new_cap = mul i64 %capacity, 2
    %new_data = call ptr @realloc(ptr %data_ptr, i64 %new_cap)
    store i64 %new_cap, ptr %cap_ptr
    store ptr %new_data, ptr %data_ptr
    br label %insert

insert:
    %elem_ptr = getelementptr ptr, ptr %data_ptr, i64 %size
    store ptr %new_elem, ptr %elem_ptr

    %new_size = add i64 %size, 1
    store i64 %new_size, ptr %size_ptr
    ret void
}

define void @ArrayType_freeArr_ArrayType(ptr %self) {
    %data_ptr = call ptr @get_data(ptr %self)
    call void @free(ptr %data_ptr)
    call void @free(ptr %self)
    ret void
}

define ptr @get_cap(ptr %self) {
    %cap_ptr = getelementptr %arr, ptr %self, i32 0, i32 0
    ret ptr %cap_ptr
}

define ptr @get_size(ptr %self) {
    %size_ptr = getelementptr %arr, ptr %self, i32 0, i32 1
    ret ptr %size_ptr
}

define ptr @get_data(ptr %self) {
    %data_ptr = getelementptr %arr, ptr %self, i32 0, i32 2
    ret ptr %data_ptr
}