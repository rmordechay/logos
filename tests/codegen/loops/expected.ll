define i32 @main() {
entry:
  %0 = alloca i32, align 4
  store i32 0, ptr %0, align 4
  br label %loop_condition

loop_condition:                                   ; preds = %loop_body, %entry
  %1 = load i32, ptr %0, align 4
  %2 = icmp slt i32 %1, 10
  br i1 %2, label %loop_body, label %loop_exit

loop_body:                                        ; preds = %loop_condition
  call void @print_Int(i32 %1)
  %3 = add i32 %1, 1
  store i32 %3, ptr %0, align 4
  br label %loop_condition

loop_exit:                                        ; preds = %loop_condition
  ret i32 0
}