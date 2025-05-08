; ModuleID = 'HashMap.c'
source_filename = "HashMap.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "arm64-apple-macosx15.0.0"

%struct.Entry = type { ptr, ptr, ptr }
%struct.HashMap = type { ptr, i32 }

@FNV_PRIME = constant i32 16777619, align 4
@HASH = constant i32 -2128831035, align 4
@.str = private unnamed_addr constant [7 x i8] c"answer\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @hash(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  store ptr %0, ptr %2, align 8
  store i32 -2128831035, ptr %3, align 4
  br label %4

4:                                                ; preds = %8, %1
  %5 = load ptr, ptr %2, align 8
  %6 = load i8, ptr %5, align 1
  %7 = icmp ne i8 %6, 0
  br i1 %7, label %8, label %17

8:                                                ; preds = %4
  %9 = load ptr, ptr %2, align 8
  %10 = getelementptr inbounds i8, ptr %9, i32 1
  store ptr %10, ptr %2, align 8
  %11 = load i8, ptr %9, align 1
  %12 = zext i8 %11 to i32
  %13 = load i32, ptr %3, align 4
  %14 = xor i32 %13, %12
  store i32 %14, ptr %3, align 4
  %15 = load i32, ptr %3, align 4
  %16 = mul i32 %15, 16777619
  store i32 %16, ptr %3, align 4
  br label %4, !llvm.loop !6

17:                                               ; preds = %4
  %18 = load i32, ptr %3, align 4
  %19 = urem i32 %18, 1024
  ret i32 %19
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define ptr @new_entry(ptr noundef %0, ptr noundef %1, ptr noundef %2) #0 {
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca ptr, align 8
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  store ptr %2, ptr %6, align 8
  %8 = call ptr @malloc(i64 noundef 24) #6
  store ptr %8, ptr %7, align 8
  %9 = load ptr, ptr %5, align 8
  %10 = call ptr @strdup(ptr noundef %9) #7
  %11 = load ptr, ptr %7, align 8
  %12 = getelementptr inbounds %struct.Entry, ptr %11, i32 0, i32 0
  store ptr %10, ptr %12, align 8
  %13 = load ptr, ptr %4, align 8
  %14 = getelementptr inbounds %struct.HashMap, ptr %13, i32 0, i32 1
  %15 = load i32, ptr %14, align 8
  %16 = zext i32 %15 to i64
  %17 = call ptr @malloc(i64 noundef %16) #6
  %18 = load ptr, ptr %7, align 8
  %19 = getelementptr inbounds %struct.Entry, ptr %18, i32 0, i32 1
  store ptr %17, ptr %19, align 8
  %20 = load ptr, ptr %7, align 8
  %21 = getelementptr inbounds %struct.Entry, ptr %20, i32 0, i32 1
  %22 = load ptr, ptr %21, align 8
  %23 = load ptr, ptr %6, align 8
  %24 = load ptr, ptr %4, align 8
  %25 = getelementptr inbounds %struct.HashMap, ptr %24, i32 0, i32 1
  %26 = load i32, ptr %25, align 8
  %27 = zext i32 %26 to i64
  %28 = load ptr, ptr %7, align 8
  %29 = getelementptr inbounds %struct.Entry, ptr %28, i32 0, i32 1
  %30 = load ptr, ptr %29, align 8
  %31 = call i64 @llvm.objectsize.i64.p0(ptr %30, i1 false, i1 true, i1 false)
  %32 = call ptr @__memcpy_chk(ptr noundef %22, ptr noundef %23, i64 noundef %27, i64 noundef %31) #7
  %33 = load ptr, ptr %7, align 8
  %34 = getelementptr inbounds %struct.Entry, ptr %33, i32 0, i32 2
  store ptr null, ptr %34, align 8
  %35 = load ptr, ptr %7, align 8
  ret ptr %35
}

; Function Attrs: allocsize(0)
declare ptr @malloc(i64 noundef) #1

; Function Attrs: nounwind
declare ptr @strdup(ptr noundef) #2

; Function Attrs: nounwind
declare ptr @__memcpy_chk(ptr noundef, ptr noundef, i64 noundef, i64 noundef) #2

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i64 @llvm.objectsize.i64.p0(ptr, i1 immarg, i1 immarg, i1 immarg) #3

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define ptr @Map_new_Int(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca ptr, align 8
  store i32 %0, ptr %2, align 4
  %4 = call ptr @malloc(i64 noundef 16) #6
  store ptr %4, ptr %3, align 8
  %5 = load i32, ptr %2, align 4
  %6 = load ptr, ptr %3, align 8
  %7 = getelementptr inbounds %struct.HashMap, ptr %6, i32 0, i32 1
  store i32 %5, ptr %7, align 8
  %8 = call ptr @calloc(i64 noundef 1024, i64 noundef 8) #8
  %9 = load ptr, ptr %3, align 8
  %10 = getelementptr inbounds %struct.HashMap, ptr %9, i32 0, i32 0
  store ptr %8, ptr %10, align 8
  %11 = load ptr, ptr %3, align 8
  ret ptr %11
}

; Function Attrs: allocsize(0,1)
declare ptr @calloc(i64 noundef, i64 noundef) #4

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @Map_add_Map_Str_Any(ptr noundef %0, ptr noundef %1, ptr noundef %2) #0 {
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca i32, align 4
  %8 = alloca ptr, align 8
  %9 = alloca ptr, align 8
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  store ptr %2, ptr %6, align 8
  %10 = load ptr, ptr %5, align 8
  %11 = call i32 @hash(ptr noundef %10)
  store i32 %11, ptr %7, align 4
  %12 = load ptr, ptr %4, align 8
  %13 = getelementptr inbounds %struct.HashMap, ptr %12, i32 0, i32 0
  %14 = load ptr, ptr %13, align 8
  %15 = load i32, ptr %7, align 4
  %16 = zext i32 %15 to i64
  %17 = getelementptr inbounds ptr, ptr %14, i64 %16
  %18 = load ptr, ptr %17, align 8
  store ptr %18, ptr %8, align 8
  br label %19

19:                                               ; preds = %43, %3
  %20 = load ptr, ptr %8, align 8
  %21 = icmp ne ptr %20, null
  br i1 %21, label %22, label %47

22:                                               ; preds = %19
  %23 = load ptr, ptr %8, align 8
  %24 = getelementptr inbounds %struct.Entry, ptr %23, i32 0, i32 0
  %25 = load ptr, ptr %24, align 8
  %26 = load ptr, ptr %5, align 8
  %27 = call i32 @strcmp(ptr noundef %25, ptr noundef %26) #7
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %29, label %43

29:                                               ; preds = %22
  %30 = load ptr, ptr %8, align 8
  %31 = getelementptr inbounds %struct.Entry, ptr %30, i32 0, i32 1
  %32 = load ptr, ptr %31, align 8
  %33 = load ptr, ptr %6, align 8
  %34 = load ptr, ptr %4, align 8
  %35 = getelementptr inbounds %struct.HashMap, ptr %34, i32 0, i32 1
  %36 = load i32, ptr %35, align 8
  %37 = zext i32 %36 to i64
  %38 = load ptr, ptr %8, align 8
  %39 = getelementptr inbounds %struct.Entry, ptr %38, i32 0, i32 1
  %40 = load ptr, ptr %39, align 8
  %41 = call i64 @llvm.objectsize.i64.p0(ptr %40, i1 false, i1 true, i1 false)
  %42 = call ptr @__memcpy_chk(ptr noundef %32, ptr noundef %33, i64 noundef %37, i64 noundef %41) #7
  br label %68

43:                                               ; preds = %22
  %44 = load ptr, ptr %8, align 8
  %45 = getelementptr inbounds %struct.Entry, ptr %44, i32 0, i32 2
  %46 = load ptr, ptr %45, align 8
  store ptr %46, ptr %8, align 8
  br label %19, !llvm.loop !8

47:                                               ; preds = %19
  %48 = load ptr, ptr %4, align 8
  %49 = load ptr, ptr %5, align 8
  %50 = load ptr, ptr %6, align 8
  %51 = call ptr @new_entry(ptr noundef %48, ptr noundef %49, ptr noundef %50)
  store ptr %51, ptr %9, align 8
  %52 = load ptr, ptr %4, align 8
  %53 = getelementptr inbounds %struct.HashMap, ptr %52, i32 0, i32 0
  %54 = load ptr, ptr %53, align 8
  %55 = load i32, ptr %7, align 4
  %56 = zext i32 %55 to i64
  %57 = getelementptr inbounds ptr, ptr %54, i64 %56
  %58 = load ptr, ptr %57, align 8
  %59 = load ptr, ptr %9, align 8
  %60 = getelementptr inbounds %struct.Entry, ptr %59, i32 0, i32 2
  store ptr %58, ptr %60, align 8
  %61 = load ptr, ptr %9, align 8
  %62 = load ptr, ptr %4, align 8
  %63 = getelementptr inbounds %struct.HashMap, ptr %62, i32 0, i32 0
  %64 = load ptr, ptr %63, align 8
  %65 = load i32, ptr %7, align 4
  %66 = zext i32 %65 to i64
  %67 = getelementptr inbounds ptr, ptr %64, i64 %66
  store ptr %61, ptr %67, align 8
  br label %68

68:                                               ; preds = %47, %29
  ret void
}

; Function Attrs: nounwind
declare i32 @strcmp(ptr noundef, ptr noundef) #2

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define ptr @Map_get_Map_Str(ptr noundef %0, ptr noundef %1) #0 {
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  %7 = load ptr, ptr %4, align 8
  %8 = getelementptr inbounds %struct.HashMap, ptr %7, i32 0, i32 0
  %9 = load ptr, ptr %8, align 8
  %10 = load ptr, ptr %5, align 8
  %11 = call i32 @hash(ptr noundef %10)
  %12 = zext i32 %11 to i64
  %13 = getelementptr inbounds ptr, ptr %9, i64 %12
  %14 = load ptr, ptr %13, align 8
  store ptr %14, ptr %6, align 8
  br label %15

15:                                               ; preds = %29, %2
  %16 = load ptr, ptr %6, align 8
  %17 = icmp ne ptr %16, null
  br i1 %17, label %18, label %33

18:                                               ; preds = %15
  %19 = load ptr, ptr %6, align 8
  %20 = getelementptr inbounds %struct.Entry, ptr %19, i32 0, i32 0
  %21 = load ptr, ptr %20, align 8
  %22 = load ptr, ptr %5, align 8
  %23 = call i32 @strcmp(ptr noundef %21, ptr noundef %22) #7
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %25, label %29

25:                                               ; preds = %18
  %26 = load ptr, ptr %6, align 8
  %27 = getelementptr inbounds %struct.Entry, ptr %26, i32 0, i32 1
  %28 = load ptr, ptr %27, align 8
  store ptr %28, ptr %3, align 8
  br label %34

29:                                               ; preds = %18
  %30 = load ptr, ptr %6, align 8
  %31 = getelementptr inbounds %struct.Entry, ptr %30, i32 0, i32 2
  %32 = load ptr, ptr %31, align 8
  store ptr %32, ptr %6, align 8
  br label %15, !llvm.loop !9

33:                                               ; preds = %15
  store ptr null, ptr %3, align 8
  br label %34

34:                                               ; preds = %33, %25
  %35 = load ptr, ptr %3, align 8
  ret ptr %35
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @Map_free_Map(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  store i32 0, ptr %3, align 4
  br label %6

6:                                                ; preds = %33, %1
  %7 = load i32, ptr %3, align 4
  %8 = icmp slt i32 %7, 1024
  br i1 %8, label %9, label %36

9:                                                ; preds = %6
  %10 = load ptr, ptr %2, align 8
  %11 = getelementptr inbounds %struct.HashMap, ptr %10, i32 0, i32 0
  %12 = load ptr, ptr %11, align 8
  %13 = load i32, ptr %3, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds ptr, ptr %12, i64 %14
  %16 = load ptr, ptr %15, align 8
  store ptr %16, ptr %4, align 8
  br label %17

17:                                               ; preds = %20, %9
  %18 = load ptr, ptr %4, align 8
  %19 = icmp ne ptr %18, null
  br i1 %19, label %20, label %32

20:                                               ; preds = %17
  %21 = load ptr, ptr %4, align 8
  store ptr %21, ptr %5, align 8
  %22 = load ptr, ptr %4, align 8
  %23 = getelementptr inbounds %struct.Entry, ptr %22, i32 0, i32 2
  %24 = load ptr, ptr %23, align 8
  store ptr %24, ptr %4, align 8
  %25 = load ptr, ptr %5, align 8
  %26 = getelementptr inbounds %struct.Entry, ptr %25, i32 0, i32 0
  %27 = load ptr, ptr %26, align 8
  call void @free(ptr noundef %27)
  %28 = load ptr, ptr %5, align 8
  %29 = getelementptr inbounds %struct.Entry, ptr %28, i32 0, i32 1
  %30 = load ptr, ptr %29, align 8
  call void @free(ptr noundef %30)
  %31 = load ptr, ptr %5, align 8
  call void @free(ptr noundef %31)
  br label %17, !llvm.loop !10

32:                                               ; preds = %17
  br label %33

33:                                               ; preds = %32
  %34 = load i32, ptr %3, align 4
  %35 = add nsw i32 %34, 1
  store i32 %35, ptr %3, align 4
  br label %6, !llvm.loop !11

36:                                               ; preds = %6
  %37 = load ptr, ptr %2, align 8
  %38 = getelementptr inbounds %struct.HashMap, ptr %37, i32 0, i32 0
  %39 = load ptr, ptr %38, align 8
  call void @free(ptr noundef %39)
  %40 = load ptr, ptr %2, align 8
  call void @free(ptr noundef %40)
  ret void
}

declare void @free(ptr noundef) #5

attributes #0 = { noinline nounwind optnone ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #1 = { allocsize(0) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #2 = { nounwind "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #3 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #4 = { allocsize(0,1) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #5 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #6 = { allocsize(0) }
attributes #7 = { nounwind }
attributes #8 = { allocsize(0,1) }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 2]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Homebrew clang version 19.1.7"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
!11 = distinct !{!11, !7}
