%struct.stbds_array_header = type { i64, i64, ptr, i64 }
%struct.stbds_hash_index = type { ptr, i64, i64, i64, i64, i64, i64, i64, i64, %struct.stbds_string_arena, ptr }
%struct.stbds_string_arena = type { ptr, i64, i8, i8 }
%struct.stbds_string_block = type { ptr, [8 x i8] }
%struct.stbds_hash_bucket = type { [8 x i64], [8 x i64] }
%struct.Map = type { ptr, ptr }

@stbds_hash_seed = internal global i64 826366246, align 8

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define ptr @stbds_arrgrowf(ptr noundef %0, i64 noundef %1, i64 noundef %2, i64 noundef %3) #0 {
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca i64, align 8
  %8 = alloca i64, align 8
  %9 = alloca i64, align 8
  %10 = alloca %struct.stbds_array_header, align 8
  %11 = alloca ptr, align 8
  %12 = alloca i64, align 8
  store ptr %0, ptr %6, align 8
  store i64 %1, ptr %7, align 8
  store i64 %2, ptr %8, align 8
  store i64 %3, ptr %9, align 8
  call void @llvm.memset.p0.i64(ptr align 8 %10, i8 0, i64 32, i1 false)
  %13 = load ptr, ptr %6, align 8
  %14 = icmp ne ptr %13, null
  br i1 %14, label %15, label %20

15:                                               ; preds = %4
  %16 = load ptr, ptr %6, align 8
  %17 = getelementptr inbounds %struct.stbds_array_header, ptr %16, i64 -1
  %18 = getelementptr inbounds %struct.stbds_array_header, ptr %17, i32 0, i32 0
  %19 = load i64, ptr %18, align 8
  br label %21

20:                                               ; preds = %4
  br label %21

21:                                               ; preds = %20, %15
  %22 = phi i64 [ %19, %15 ], [ 0, %20 ]
  %23 = load i64, ptr %8, align 8
  %24 = add i64 %22, %23
  store i64 %24, ptr %12, align 8
  %25 = load i64, ptr %12, align 8
  %26 = load i64, ptr %9, align 8
  %27 = icmp ugt i64 %25, %26
  br i1 %27, label %28, label %30

28:                                               ; preds = %21
  %29 = load i64, ptr %12, align 8
  store i64 %29, ptr %9, align 8
  br label %30

30:                                               ; preds = %28, %21
  %31 = load i64, ptr %9, align 8
  %32 = load ptr, ptr %6, align 8
  %33 = icmp ne ptr %32, null
  br i1 %33, label %34, label %39

34:                                               ; preds = %30
  %35 = load ptr, ptr %6, align 8
  %36 = getelementptr inbounds %struct.stbds_array_header, ptr %35, i64 -1
  %37 = getelementptr inbounds %struct.stbds_array_header, ptr %36, i32 0, i32 1
  %38 = load i64, ptr %37, align 8
  br label %40

39:                                               ; preds = %30
  br label %40

40:                                               ; preds = %39, %34
  %41 = phi i64 [ %38, %34 ], [ 0, %39 ]
  %42 = icmp ule i64 %31, %41
  br i1 %42, label %43, label %45

43:                                               ; preds = %40
  %44 = load ptr, ptr %6, align 8
  store ptr %44, ptr %5, align 8
  br label %111

45:                                               ; preds = %40
  %46 = load i64, ptr %9, align 8
  %47 = load ptr, ptr %6, align 8
  %48 = icmp ne ptr %47, null
  br i1 %48, label %49, label %54

49:                                               ; preds = %45
  %50 = load ptr, ptr %6, align 8
  %51 = getelementptr inbounds %struct.stbds_array_header, ptr %50, i64 -1
  %52 = getelementptr inbounds %struct.stbds_array_header, ptr %51, i32 0, i32 1
  %53 = load i64, ptr %52, align 8
  br label %55

54:                                               ; preds = %45
  br label %55

55:                                               ; preds = %54, %49
  %56 = phi i64 [ %53, %49 ], [ 0, %54 ]
  %57 = mul i64 2, %56
  %58 = icmp ult i64 %46, %57
  br i1 %58, label %59, label %71

59:                                               ; preds = %55
  %60 = load ptr, ptr %6, align 8
  %61 = icmp ne ptr %60, null
  br i1 %61, label %62, label %67

62:                                               ; preds = %59
  %63 = load ptr, ptr %6, align 8
  %64 = getelementptr inbounds %struct.stbds_array_header, ptr %63, i64 -1
  %65 = getelementptr inbounds %struct.stbds_array_header, ptr %64, i32 0, i32 1
  %66 = load i64, ptr %65, align 8
  br label %68

67:                                               ; preds = %59
  br label %68

68:                                               ; preds = %67, %62
  %69 = phi i64 [ %66, %62 ], [ 0, %67 ]
  %70 = mul i64 2, %69
  store i64 %70, ptr %9, align 8
  br label %76

71:                                               ; preds = %55
  %72 = load i64, ptr %9, align 8
  %73 = icmp ult i64 %72, 4
  br i1 %73, label %74, label %75

74:                                               ; preds = %71
  store i64 4, ptr %9, align 8
  br label %75

75:                                               ; preds = %74, %71
  br label %76

76:                                               ; preds = %75, %68
  %77 = load ptr, ptr %6, align 8
  %78 = icmp ne ptr %77, null
  br i1 %78, label %79, label %82

79:                                               ; preds = %76
  %80 = load ptr, ptr %6, align 8
  %81 = getelementptr inbounds %struct.stbds_array_header, ptr %80, i64 -1
  br label %83

82:                                               ; preds = %76
  br label %83

83:                                               ; preds = %82, %79
  %84 = phi ptr [ %81, %79 ], [ null, %82 ]
  %85 = load i64, ptr %7, align 8
  %86 = load i64, ptr %9, align 8
  %87 = mul i64 %85, %86
  %88 = add i64 %87, 32
  %89 = call ptr @realloc(ptr noundef %84, i64 noundef %88) #7
  store ptr %89, ptr %11, align 8
  %90 = load ptr, ptr %11, align 8
  %91 = getelementptr inbounds i8, ptr %90, i64 32
  store ptr %91, ptr %11, align 8
  %92 = load ptr, ptr %6, align 8
  %93 = icmp eq ptr %92, null
  br i1 %93, label %94, label %104

94:                                               ; preds = %83
  %95 = load ptr, ptr %11, align 8
  %96 = getelementptr inbounds %struct.stbds_array_header, ptr %95, i64 -1
  %97 = getelementptr inbounds %struct.stbds_array_header, ptr %96, i32 0, i32 0
  store i64 0, ptr %97, align 8
  %98 = load ptr, ptr %11, align 8
  %99 = getelementptr inbounds %struct.stbds_array_header, ptr %98, i64 -1
  %100 = getelementptr inbounds %struct.stbds_array_header, ptr %99, i32 0, i32 2
  store ptr null, ptr %100, align 8
  %101 = load ptr, ptr %11, align 8
  %102 = getelementptr inbounds %struct.stbds_array_header, ptr %101, i64 -1
  %103 = getelementptr inbounds %struct.stbds_array_header, ptr %102, i32 0, i32 3
  store i64 0, ptr %103, align 8
  br label %105

104:                                              ; preds = %83
  br label %105

105:                                              ; preds = %104, %94
  %106 = load i64, ptr %9, align 8
  %107 = load ptr, ptr %11, align 8
  %108 = getelementptr inbounds %struct.stbds_array_header, ptr %107, i64 -1
  %109 = getelementptr inbounds %struct.stbds_array_header, ptr %108, i32 0, i32 1
  store i64 %106, ptr %109, align 8
  %110 = load ptr, ptr %11, align 8
  store ptr %110, ptr %5, align 8
  br label %111

111:                                              ; preds = %105, %43
  %112 = load ptr, ptr %5, align 8
  ret ptr %112
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #1

; Function Attrs: allocsize(1)
declare ptr @realloc(ptr noundef, i64 noundef) #2

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @stbds_arrfreef(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %struct.stbds_array_header, ptr %3, i64 -1
  call void @free(ptr noundef %4)
  ret void
}

declare void @free(ptr noundef) #3

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @stbds_rand_seed(i64 noundef %0) #0 {
  %2 = alloca i64, align 8
  store i64 %0, ptr %2, align 8
  %3 = load i64, ptr %2, align 8
  store i64 %3, ptr @stbds_hash_seed, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i64 @stbds_hash_string(ptr noundef %0, i64 noundef %1) #0 {
  %3 = alloca ptr, align 8
  %4 = alloca i64, align 8
  %5 = alloca i64, align 8
  store ptr %0, ptr %3, align 8
  store i64 %1, ptr %4, align 8
  %6 = load i64, ptr %4, align 8
  store i64 %6, ptr %5, align 8
  br label %7

7:                                                ; preds = %11, %2
  %8 = load ptr, ptr %3, align 8
  %9 = load i8, ptr %8, align 1
  %10 = icmp ne i8 %9, 0
  br i1 %10, label %11, label %22

11:                                               ; preds = %7
  %12 = load i64, ptr %5, align 8
  %13 = shl i64 %12, 9
  %14 = load i64, ptr %5, align 8
  %15 = lshr i64 %14, 55
  %16 = or i64 %13, %15
  %17 = load ptr, ptr %3, align 8
  %18 = getelementptr inbounds i8, ptr %17, i32 1
  store ptr %18, ptr %3, align 8
  %19 = load i8, ptr %17, align 1
  %20 = zext i8 %19 to i64
  %21 = add i64 %16, %20
  store i64 %21, ptr %5, align 8
  br label %7, !llvm.loop !6

22:                                               ; preds = %7
  %23 = load i64, ptr %4, align 8
  %24 = load i64, ptr %5, align 8
  %25 = xor i64 %24, %23
  store i64 %25, ptr %5, align 8
  %26 = load i64, ptr %5, align 8
  %27 = xor i64 %26, -1
  %28 = load i64, ptr %5, align 8
  %29 = shl i64 %28, 18
  %30 = add i64 %27, %29
  store i64 %30, ptr %5, align 8
  %31 = load i64, ptr %5, align 8
  %32 = load i64, ptr %5, align 8
  %33 = lshr i64 %32, 31
  %34 = load i64, ptr %5, align 8
  %35 = shl i64 %34, 33
  %36 = or i64 %33, %35
  %37 = xor i64 %31, %36
  %38 = load i64, ptr %5, align 8
  %39 = xor i64 %38, %37
  store i64 %39, ptr %5, align 8
  %40 = load i64, ptr %5, align 8
  %41 = mul i64 %40, 21
  store i64 %41, ptr %5, align 8
  %42 = load i64, ptr %5, align 8
  %43 = load i64, ptr %5, align 8
  %44 = lshr i64 %43, 11
  %45 = load i64, ptr %5, align 8
  %46 = shl i64 %45, 53
  %47 = or i64 %44, %46
  %48 = xor i64 %42, %47
  %49 = load i64, ptr %5, align 8
  %50 = xor i64 %49, %48
  store i64 %50, ptr %5, align 8
  %51 = load i64, ptr %5, align 8
  %52 = shl i64 %51, 6
  %53 = load i64, ptr %5, align 8
  %54 = add i64 %53, %52
  store i64 %54, ptr %5, align 8
  %55 = load i64, ptr %5, align 8
  %56 = lshr i64 %55, 22
  %57 = load i64, ptr %5, align 8
  %58 = shl i64 %57, 42
  %59 = or i64 %56, %58
  %60 = load i64, ptr %5, align 8
  %61 = xor i64 %60, %59
  store i64 %61, ptr %5, align 8
  %62 = load i64, ptr %5, align 8
  %63 = load i64, ptr %4, align 8
  %64 = add i64 %62, %63
  ret i64 %64
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i64 @stbds_hash_bytes(ptr noundef %0, i64 noundef %1, i64 noundef %2) #0 {
  %4 = alloca i64, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i64, align 8
  %7 = alloca i64, align 8
  %8 = alloca ptr, align 8
  %9 = alloca i32, align 4
  %10 = alloca i64, align 8
  store ptr %0, ptr %5, align 8
  store i64 %1, ptr %6, align 8
  store i64 %2, ptr %7, align 8
  %11 = load ptr, ptr %5, align 8
  store ptr %11, ptr %8, align 8
  %12 = load i64, ptr %6, align 8
  %13 = icmp eq i64 %12, 4
  br i1 %13, label %14, label %75

14:                                               ; preds = %3
  %15 = load ptr, ptr %8, align 8
  %16 = getelementptr inbounds i8, ptr %15, i64 0
  %17 = load i8, ptr %16, align 1
  %18 = zext i8 %17 to i32
  %19 = load ptr, ptr %8, align 8
  %20 = getelementptr inbounds i8, ptr %19, i64 1
  %21 = load i8, ptr %20, align 1
  %22 = zext i8 %21 to i32
  %23 = shl i32 %22, 8
  %24 = or i32 %18, %23
  %25 = load ptr, ptr %8, align 8
  %26 = getelementptr inbounds i8, ptr %25, i64 2
  %27 = load i8, ptr %26, align 1
  %28 = zext i8 %27 to i32
  %29 = shl i32 %28, 16
  %30 = or i32 %24, %29
  %31 = load ptr, ptr %8, align 8
  %32 = getelementptr inbounds i8, ptr %31, i64 3
  %33 = load i8, ptr %32, align 1
  %34 = zext i8 %33 to i32
  %35 = shl i32 %34, 24
  %36 = or i32 %30, %35
  store i32 %36, ptr %9, align 4
  %37 = load i64, ptr %7, align 8
  %38 = load i32, ptr %9, align 4
  %39 = zext i32 %38 to i64
  %40 = xor i64 %39, %37
  %41 = trunc i64 %40 to i32
  store i32 %41, ptr %9, align 4
  %42 = load i32, ptr %9, align 4
  %43 = xor i32 %42, 61
  %44 = load i32, ptr %9, align 4
  %45 = lshr i32 %44, 16
  %46 = xor i32 %43, %45
  store i32 %46, ptr %9, align 4
  %47 = load i32, ptr %9, align 4
  %48 = load i32, ptr %9, align 4
  %49 = shl i32 %48, 3
  %50 = add i32 %47, %49
  store i32 %50, ptr %9, align 4
  %51 = load i32, ptr %9, align 4
  %52 = load i32, ptr %9, align 4
  %53 = lshr i32 %52, 4
  %54 = xor i32 %51, %53
  store i32 %54, ptr %9, align 4
  %55 = load i32, ptr %9, align 4
  %56 = mul i32 %55, 668265261
  store i32 %56, ptr %9, align 4
  %57 = load i64, ptr %7, align 8
  %58 = load i32, ptr %9, align 4
  %59 = zext i32 %58 to i64
  %60 = xor i64 %59, %57
  %61 = trunc i64 %60 to i32
  store i32 %61, ptr %9, align 4
  %62 = load i32, ptr %9, align 4
  %63 = load i32, ptr %9, align 4
  %64 = lshr i32 %63, 15
  %65 = xor i32 %62, %64
  store i32 %65, ptr %9, align 4
  %66 = load i32, ptr %9, align 4
  %67 = zext i32 %66 to i64
  %68 = shl i64 %67, 16
  %69 = shl i64 %68, 16
  %70 = load i32, ptr %9, align 4
  %71 = zext i32 %70 to i64
  %72 = or i64 %69, %71
  %73 = load i64, ptr %7, align 8
  %74 = xor i64 %72, %73
  store i64 %74, ptr %4, align 8
  br label %180

75:                                               ; preds = %3
  %76 = load i64, ptr %6, align 8
  %77 = icmp eq i64 %76, 8
  br i1 %77, label %78, label %175

78:                                               ; preds = %75
  %79 = load ptr, ptr %8, align 8
  %80 = getelementptr inbounds i8, ptr %79, i64 0
  %81 = load i8, ptr %80, align 1
  %82 = zext i8 %81 to i32
  %83 = load ptr, ptr %8, align 8
  %84 = getelementptr inbounds i8, ptr %83, i64 1
  %85 = load i8, ptr %84, align 1
  %86 = zext i8 %85 to i32
  %87 = shl i32 %86, 8
  %88 = or i32 %82, %87
  %89 = load ptr, ptr %8, align 8
  %90 = getelementptr inbounds i8, ptr %89, i64 2
  %91 = load i8, ptr %90, align 1
  %92 = zext i8 %91 to i32
  %93 = shl i32 %92, 16
  %94 = or i32 %88, %93
  %95 = load ptr, ptr %8, align 8
  %96 = getelementptr inbounds i8, ptr %95, i64 3
  %97 = load i8, ptr %96, align 1
  %98 = zext i8 %97 to i32
  %99 = shl i32 %98, 24
  %100 = or i32 %94, %99
  %101 = sext i32 %100 to i64
  store i64 %101, ptr %10, align 8
  %102 = load ptr, ptr %8, align 8
  %103 = getelementptr inbounds i8, ptr %102, i64 4
  %104 = load i8, ptr %103, align 1
  %105 = zext i8 %104 to i32
  %106 = load ptr, ptr %8, align 8
  %107 = getelementptr inbounds i8, ptr %106, i64 5
  %108 = load i8, ptr %107, align 1
  %109 = zext i8 %108 to i32
  %110 = shl i32 %109, 8
  %111 = or i32 %105, %110
  %112 = load ptr, ptr %8, align 8
  %113 = getelementptr inbounds i8, ptr %112, i64 6
  %114 = load i8, ptr %113, align 1
  %115 = zext i8 %114 to i32
  %116 = shl i32 %115, 16
  %117 = or i32 %111, %116
  %118 = load ptr, ptr %8, align 8
  %119 = getelementptr inbounds i8, ptr %118, i64 7
  %120 = load i8, ptr %119, align 1
  %121 = zext i8 %120 to i32
  %122 = shl i32 %121, 24
  %123 = or i32 %117, %122
  %124 = sext i32 %123 to i64
  %125 = shl i64 %124, 16
  %126 = shl i64 %125, 16
  %127 = load i64, ptr %10, align 8
  %128 = or i64 %127, %126
  store i64 %128, ptr %10, align 8
  %129 = load i64, ptr %7, align 8
  %130 = load i64, ptr %10, align 8
  %131 = xor i64 %130, %129
  store i64 %131, ptr %10, align 8
  %132 = load i64, ptr %10, align 8
  %133 = xor i64 %132, -1
  %134 = load i64, ptr %10, align 8
  %135 = shl i64 %134, 21
  %136 = add i64 %133, %135
  store i64 %136, ptr %10, align 8
  %137 = load i64, ptr %10, align 8
  %138 = lshr i64 %137, 24
  %139 = load i64, ptr %10, align 8
  %140 = shl i64 %139, 40
  %141 = or i64 %138, %140
  %142 = load i64, ptr %10, align 8
  %143 = xor i64 %142, %141
  store i64 %143, ptr %10, align 8
  %144 = load i64, ptr %10, align 8
  %145 = mul i64 %144, 265
  store i64 %145, ptr %10, align 8
  %146 = load i64, ptr %10, align 8
  %147 = lshr i64 %146, 14
  %148 = load i64, ptr %10, align 8
  %149 = shl i64 %148, 50
  %150 = or i64 %147, %149
  %151 = load i64, ptr %10, align 8
  %152 = xor i64 %151, %150
  store i64 %152, ptr %10, align 8
  %153 = load i64, ptr %7, align 8
  %154 = load i64, ptr %10, align 8
  %155 = xor i64 %154, %153
  store i64 %155, ptr %10, align 8
  %156 = load i64, ptr %10, align 8
  %157 = mul i64 %156, 21
  store i64 %157, ptr %10, align 8
  %158 = load i64, ptr %10, align 8
  %159 = lshr i64 %158, 28
  %160 = load i64, ptr %10, align 8
  %161 = shl i64 %160, 36
  %162 = or i64 %159, %161
  %163 = load i64, ptr %10, align 8
  %164 = xor i64 %163, %162
  store i64 %164, ptr %10, align 8
  %165 = load i64, ptr %10, align 8
  %166 = shl i64 %165, 31
  %167 = load i64, ptr %10, align 8
  %168 = add i64 %167, %166
  store i64 %168, ptr %10, align 8
  %169 = load i64, ptr %10, align 8
  %170 = xor i64 %169, -1
  %171 = load i64, ptr %10, align 8
  %172 = shl i64 %171, 18
  %173 = add i64 %170, %172
  store i64 %173, ptr %10, align 8
  %174 = load i64, ptr %10, align 8
  store i64 %174, ptr %4, align 8
  br label %180

175:                                              ; preds = %75
  %176 = load ptr, ptr %5, align 8
  %177 = load i64, ptr %6, align 8
  %178 = load i64, ptr %7, align 8
  %179 = call i64 @stbds_siphash_bytes(ptr noundef %176, i64 noundef %177, i64 noundef %178)
  store i64 %179, ptr %4, align 8
  br label %180

180:                                              ; preds = %175, %78, %14
  %181 = load i64, ptr %4, align 8
  ret i64 %181
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define internal i64 @stbds_siphash_bytes(ptr noundef %0, i64 noundef %1, i64 noundef %2) #0 {
  %4 = alloca ptr, align 8
  %5 = alloca i64, align 8
  %6 = alloca i64, align 8
  %7 = alloca ptr, align 8
  %8 = alloca i64, align 8
  %9 = alloca i64, align 8
  %10 = alloca i64, align 8
  %11 = alloca i64, align 8
  %12 = alloca i64, align 8
  %13 = alloca i64, align 8
  %14 = alloca i64, align 8
  store ptr %0, ptr %4, align 8
  store i64 %1, ptr %5, align 8
  store i64 %2, ptr %6, align 8
  %15 = load ptr, ptr %4, align 8
  store ptr %15, ptr %7, align 8
  %16 = load i64, ptr %6, align 8
  %17 = xor i64 8317987319222330741, %16
  store i64 %17, ptr %10, align 8
  %18 = load i64, ptr %6, align 8
  %19 = xor i64 %18, -1
  %20 = xor i64 7237128888997146477, %19
  store i64 %20, ptr %11, align 8
  %21 = load i64, ptr %6, align 8
  %22 = xor i64 7816392313619706465, %21
  store i64 %22, ptr %12, align 8
  %23 = load i64, ptr %6, align 8
  %24 = xor i64 %23, -1
  %25 = xor i64 8387220255154660723, %24
  store i64 %25, ptr %13, align 8
  store i64 0, ptr %8, align 8
  br label %26

26:                                               ; preds = %152, %3
  %27 = load i64, ptr %8, align 8
  %28 = add i64 %27, 8
  %29 = load i64, ptr %5, align 8
  %30 = icmp ule i64 %28, %29
  br i1 %30, label %31, label %157

31:                                               ; preds = %26
  %32 = load ptr, ptr %7, align 8
  %33 = getelementptr inbounds i8, ptr %32, i64 0
  %34 = load i8, ptr %33, align 1
  %35 = zext i8 %34 to i32
  %36 = load ptr, ptr %7, align 8
  %37 = getelementptr inbounds i8, ptr %36, i64 1
  %38 = load i8, ptr %37, align 1
  %39 = zext i8 %38 to i32
  %40 = shl i32 %39, 8
  %41 = or i32 %35, %40
  %42 = load ptr, ptr %7, align 8
  %43 = getelementptr inbounds i8, ptr %42, i64 2
  %44 = load i8, ptr %43, align 1
  %45 = zext i8 %44 to i32
  %46 = shl i32 %45, 16
  %47 = or i32 %41, %46
  %48 = load ptr, ptr %7, align 8
  %49 = getelementptr inbounds i8, ptr %48, i64 3
  %50 = load i8, ptr %49, align 1
  %51 = zext i8 %50 to i32
  %52 = shl i32 %51, 24
  %53 = or i32 %47, %52
  %54 = sext i32 %53 to i64
  store i64 %54, ptr %14, align 8
  %55 = load ptr, ptr %7, align 8
  %56 = getelementptr inbounds i8, ptr %55, i64 4
  %57 = load i8, ptr %56, align 1
  %58 = zext i8 %57 to i32
  %59 = load ptr, ptr %7, align 8
  %60 = getelementptr inbounds i8, ptr %59, i64 5
  %61 = load i8, ptr %60, align 1
  %62 = zext i8 %61 to i32
  %63 = shl i32 %62, 8
  %64 = or i32 %58, %63
  %65 = load ptr, ptr %7, align 8
  %66 = getelementptr inbounds i8, ptr %65, i64 6
  %67 = load i8, ptr %66, align 1
  %68 = zext i8 %67 to i32
  %69 = shl i32 %68, 16
  %70 = or i32 %64, %69
  %71 = load ptr, ptr %7, align 8
  %72 = getelementptr inbounds i8, ptr %71, i64 7
  %73 = load i8, ptr %72, align 1
  %74 = zext i8 %73 to i32
  %75 = shl i32 %74, 24
  %76 = or i32 %70, %75
  %77 = sext i32 %76 to i64
  %78 = shl i64 %77, 16
  %79 = shl i64 %78, 16
  %80 = load i64, ptr %14, align 8
  %81 = or i64 %80, %79
  store i64 %81, ptr %14, align 8
  %82 = load i64, ptr %14, align 8
  %83 = load i64, ptr %13, align 8
  %84 = xor i64 %83, %82
  store i64 %84, ptr %13, align 8
  store i64 0, ptr %9, align 8
  br label %85

85:                                               ; preds = %145, %31
  %86 = load i64, ptr %9, align 8
  %87 = icmp ult i64 %86, 1
  br i1 %87, label %88, label %148

88:                                               ; preds = %85
  br label %89

89:                                               ; preds = %88
  %90 = load i64, ptr %11, align 8
  %91 = load i64, ptr %10, align 8
  %92 = add i64 %91, %90
  store i64 %92, ptr %10, align 8
  %93 = load i64, ptr %11, align 8
  %94 = shl i64 %93, 13
  %95 = load i64, ptr %11, align 8
  %96 = lshr i64 %95, 51
  %97 = or i64 %94, %96
  store i64 %97, ptr %11, align 8
  %98 = load i64, ptr %10, align 8
  %99 = load i64, ptr %11, align 8
  %100 = xor i64 %99, %98
  store i64 %100, ptr %11, align 8
  %101 = load i64, ptr %10, align 8
  %102 = shl i64 %101, 32
  %103 = load i64, ptr %10, align 8
  %104 = lshr i64 %103, 32
  %105 = or i64 %102, %104
  store i64 %105, ptr %10, align 8
  %106 = load i64, ptr %13, align 8
  %107 = load i64, ptr %12, align 8
  %108 = add i64 %107, %106
  store i64 %108, ptr %12, align 8
  %109 = load i64, ptr %13, align 8
  %110 = shl i64 %109, 16
  %111 = load i64, ptr %13, align 8
  %112 = lshr i64 %111, 48
  %113 = or i64 %110, %112
  store i64 %113, ptr %13, align 8
  %114 = load i64, ptr %12, align 8
  %115 = load i64, ptr %13, align 8
  %116 = xor i64 %115, %114
  store i64 %116, ptr %13, align 8
  %117 = load i64, ptr %11, align 8
  %118 = load i64, ptr %12, align 8
  %119 = add i64 %118, %117
  store i64 %119, ptr %12, align 8
  %120 = load i64, ptr %11, align 8
  %121 = shl i64 %120, 17
  %122 = load i64, ptr %11, align 8
  %123 = lshr i64 %122, 47
  %124 = or i64 %121, %123
  store i64 %124, ptr %11, align 8
  %125 = load i64, ptr %12, align 8
  %126 = load i64, ptr %11, align 8
  %127 = xor i64 %126, %125
  store i64 %127, ptr %11, align 8
  %128 = load i64, ptr %12, align 8
  %129 = shl i64 %128, 32
  %130 = load i64, ptr %12, align 8
  %131 = lshr i64 %130, 32
  %132 = or i64 %129, %131
  store i64 %132, ptr %12, align 8
  %133 = load i64, ptr %13, align 8
  %134 = load i64, ptr %10, align 8
  %135 = add i64 %134, %133
  store i64 %135, ptr %10, align 8
  %136 = load i64, ptr %13, align 8
  %137 = shl i64 %136, 21
  %138 = load i64, ptr %13, align 8
  %139 = lshr i64 %138, 43
  %140 = or i64 %137, %139
  store i64 %140, ptr %13, align 8
  %141 = load i64, ptr %10, align 8
  %142 = load i64, ptr %13, align 8
  %143 = xor i64 %142, %141
  store i64 %143, ptr %13, align 8
  br label %144

144:                                              ; preds = %89
  br label %145

145:                                              ; preds = %144
  %146 = load i64, ptr %9, align 8
  %147 = add i64 %146, 1
  store i64 %147, ptr %9, align 8
  br label %85, !llvm.loop !8

148:                                              ; preds = %85
  %149 = load i64, ptr %14, align 8
  %150 = load i64, ptr %10, align 8
  %151 = xor i64 %150, %149
  store i64 %151, ptr %10, align 8
  br label %152

152:                                              ; preds = %148
  %153 = load i64, ptr %8, align 8
  %154 = add i64 %153, 8
  store i64 %154, ptr %8, align 8
  %155 = load ptr, ptr %7, align 8
  %156 = getelementptr inbounds i8, ptr %155, i64 8
  store ptr %156, ptr %7, align 8
  br label %26, !llvm.loop !9

157:                                              ; preds = %26
  %158 = load i64, ptr %5, align 8
  %159 = shl i64 %158, 56
  store i64 %159, ptr %14, align 8
  %160 = load i64, ptr %5, align 8
  %161 = load i64, ptr %8, align 8
  %162 = sub i64 %160, %161
  switch i64 %162, label %225 [
    i64 7, label %163
    i64 6, label %172
    i64 5, label %181
    i64 4, label %190
    i64 3, label %199
    i64 2, label %208
    i64 1, label %217
    i64 0, label %224
  ]

163:                                              ; preds = %157
  %164 = load ptr, ptr %7, align 8
  %165 = getelementptr inbounds i8, ptr %164, i64 6
  %166 = load i8, ptr %165, align 1
  %167 = zext i8 %166 to i64
  %168 = shl i64 %167, 24
  %169 = shl i64 %168, 24
  %170 = load i64, ptr %14, align 8
  %171 = or i64 %170, %169
  store i64 %171, ptr %14, align 8
  br label %172

172:                                              ; preds = %157, %163
  %173 = load ptr, ptr %7, align 8
  %174 = getelementptr inbounds i8, ptr %173, i64 5
  %175 = load i8, ptr %174, align 1
  %176 = zext i8 %175 to i64
  %177 = shl i64 %176, 20
  %178 = shl i64 %177, 20
  %179 = load i64, ptr %14, align 8
  %180 = or i64 %179, %178
  store i64 %180, ptr %14, align 8
  br label %181

181:                                              ; preds = %157, %172
  %182 = load ptr, ptr %7, align 8
  %183 = getelementptr inbounds i8, ptr %182, i64 4
  %184 = load i8, ptr %183, align 1
  %185 = zext i8 %184 to i64
  %186 = shl i64 %185, 16
  %187 = shl i64 %186, 16
  %188 = load i64, ptr %14, align 8
  %189 = or i64 %188, %187
  store i64 %189, ptr %14, align 8
  br label %190

190:                                              ; preds = %157, %181
  %191 = load ptr, ptr %7, align 8
  %192 = getelementptr inbounds i8, ptr %191, i64 3
  %193 = load i8, ptr %192, align 1
  %194 = zext i8 %193 to i32
  %195 = shl i32 %194, 24
  %196 = sext i32 %195 to i64
  %197 = load i64, ptr %14, align 8
  %198 = or i64 %197, %196
  store i64 %198, ptr %14, align 8
  br label %199

199:                                              ; preds = %157, %190
  %200 = load ptr, ptr %7, align 8
  %201 = getelementptr inbounds i8, ptr %200, i64 2
  %202 = load i8, ptr %201, align 1
  %203 = zext i8 %202 to i32
  %204 = shl i32 %203, 16
  %205 = sext i32 %204 to i64
  %206 = load i64, ptr %14, align 8
  %207 = or i64 %206, %205
  store i64 %207, ptr %14, align 8
  br label %208

208:                                              ; preds = %157, %199
  %209 = load ptr, ptr %7, align 8
  %210 = getelementptr inbounds i8, ptr %209, i64 1
  %211 = load i8, ptr %210, align 1
  %212 = zext i8 %211 to i32
  %213 = shl i32 %212, 8
  %214 = sext i32 %213 to i64
  %215 = load i64, ptr %14, align 8
  %216 = or i64 %215, %214
  store i64 %216, ptr %14, align 8
  br label %217

217:                                              ; preds = %157, %208
  %218 = load ptr, ptr %7, align 8
  %219 = getelementptr inbounds i8, ptr %218, i64 0
  %220 = load i8, ptr %219, align 1
  %221 = zext i8 %220 to i64
  %222 = load i64, ptr %14, align 8
  %223 = or i64 %222, %221
  store i64 %223, ptr %14, align 8
  br label %224

224:                                              ; preds = %157, %217
  br label %225

225:                                              ; preds = %157, %224
  %226 = load i64, ptr %14, align 8
  %227 = load i64, ptr %13, align 8
  %228 = xor i64 %227, %226
  store i64 %228, ptr %13, align 8
  store i64 0, ptr %9, align 8
  br label %229

229:                                              ; preds = %289, %225
  %230 = load i64, ptr %9, align 8
  %231 = icmp ult i64 %230, 1
  br i1 %231, label %232, label %292

232:                                              ; preds = %229
  br label %233

233:                                              ; preds = %232
  %234 = load i64, ptr %11, align 8
  %235 = load i64, ptr %10, align 8
  %236 = add i64 %235, %234
  store i64 %236, ptr %10, align 8
  %237 = load i64, ptr %11, align 8
  %238 = shl i64 %237, 13
  %239 = load i64, ptr %11, align 8
  %240 = lshr i64 %239, 51
  %241 = or i64 %238, %240
  store i64 %241, ptr %11, align 8
  %242 = load i64, ptr %10, align 8
  %243 = load i64, ptr %11, align 8
  %244 = xor i64 %243, %242
  store i64 %244, ptr %11, align 8
  %245 = load i64, ptr %10, align 8
  %246 = shl i64 %245, 32
  %247 = load i64, ptr %10, align 8
  %248 = lshr i64 %247, 32
  %249 = or i64 %246, %248
  store i64 %249, ptr %10, align 8
  %250 = load i64, ptr %13, align 8
  %251 = load i64, ptr %12, align 8
  %252 = add i64 %251, %250
  store i64 %252, ptr %12, align 8
  %253 = load i64, ptr %13, align 8
  %254 = shl i64 %253, 16
  %255 = load i64, ptr %13, align 8
  %256 = lshr i64 %255, 48
  %257 = or i64 %254, %256
  store i64 %257, ptr %13, align 8
  %258 = load i64, ptr %12, align 8
  %259 = load i64, ptr %13, align 8
  %260 = xor i64 %259, %258
  store i64 %260, ptr %13, align 8
  %261 = load i64, ptr %11, align 8
  %262 = load i64, ptr %12, align 8
  %263 = add i64 %262, %261
  store i64 %263, ptr %12, align 8
  %264 = load i64, ptr %11, align 8
  %265 = shl i64 %264, 17
  %266 = load i64, ptr %11, align 8
  %267 = lshr i64 %266, 47
  %268 = or i64 %265, %267
  store i64 %268, ptr %11, align 8
  %269 = load i64, ptr %12, align 8
  %270 = load i64, ptr %11, align 8
  %271 = xor i64 %270, %269
  store i64 %271, ptr %11, align 8
  %272 = load i64, ptr %12, align 8
  %273 = shl i64 %272, 32
  %274 = load i64, ptr %12, align 8
  %275 = lshr i64 %274, 32
  %276 = or i64 %273, %275
  store i64 %276, ptr %12, align 8
  %277 = load i64, ptr %13, align 8
  %278 = load i64, ptr %10, align 8
  %279 = add i64 %278, %277
  store i64 %279, ptr %10, align 8
  %280 = load i64, ptr %13, align 8
  %281 = shl i64 %280, 21
  %282 = load i64, ptr %13, align 8
  %283 = lshr i64 %282, 43
  %284 = or i64 %281, %283
  store i64 %284, ptr %13, align 8
  %285 = load i64, ptr %10, align 8
  %286 = load i64, ptr %13, align 8
  %287 = xor i64 %286, %285
  store i64 %287, ptr %13, align 8
  br label %288

288:                                              ; preds = %233
  br label %289

289:                                              ; preds = %288
  %290 = load i64, ptr %9, align 8
  %291 = add i64 %290, 1
  store i64 %291, ptr %9, align 8
  br label %229, !llvm.loop !10

292:                                              ; preds = %229
  %293 = load i64, ptr %14, align 8
  %294 = load i64, ptr %10, align 8
  %295 = xor i64 %294, %293
  store i64 %295, ptr %10, align 8
  %296 = load i64, ptr %12, align 8
  %297 = xor i64 %296, 255
  store i64 %297, ptr %12, align 8
  store i64 0, ptr %9, align 8
  br label %298

298:                                              ; preds = %358, %292
  %299 = load i64, ptr %9, align 8
  %300 = icmp ult i64 %299, 1
  br i1 %300, label %301, label %361

301:                                              ; preds = %298
  br label %302

302:                                              ; preds = %301
  %303 = load i64, ptr %11, align 8
  %304 = load i64, ptr %10, align 8
  %305 = add i64 %304, %303
  store i64 %305, ptr %10, align 8
  %306 = load i64, ptr %11, align 8
  %307 = shl i64 %306, 13
  %308 = load i64, ptr %11, align 8
  %309 = lshr i64 %308, 51
  %310 = or i64 %307, %309
  store i64 %310, ptr %11, align 8
  %311 = load i64, ptr %10, align 8
  %312 = load i64, ptr %11, align 8
  %313 = xor i64 %312, %311
  store i64 %313, ptr %11, align 8
  %314 = load i64, ptr %10, align 8
  %315 = shl i64 %314, 32
  %316 = load i64, ptr %10, align 8
  %317 = lshr i64 %316, 32
  %318 = or i64 %315, %317
  store i64 %318, ptr %10, align 8
  %319 = load i64, ptr %13, align 8
  %320 = load i64, ptr %12, align 8
  %321 = add i64 %320, %319
  store i64 %321, ptr %12, align 8
  %322 = load i64, ptr %13, align 8
  %323 = shl i64 %322, 16
  %324 = load i64, ptr %13, align 8
  %325 = lshr i64 %324, 48
  %326 = or i64 %323, %325
  store i64 %326, ptr %13, align 8
  %327 = load i64, ptr %12, align 8
  %328 = load i64, ptr %13, align 8
  %329 = xor i64 %328, %327
  store i64 %329, ptr %13, align 8
  %330 = load i64, ptr %11, align 8
  %331 = load i64, ptr %12, align 8
  %332 = add i64 %331, %330
  store i64 %332, ptr %12, align 8
  %333 = load i64, ptr %11, align 8
  %334 = shl i64 %333, 17
  %335 = load i64, ptr %11, align 8
  %336 = lshr i64 %335, 47
  %337 = or i64 %334, %336
  store i64 %337, ptr %11, align 8
  %338 = load i64, ptr %12, align 8
  %339 = load i64, ptr %11, align 8
  %340 = xor i64 %339, %338
  store i64 %340, ptr %11, align 8
  %341 = load i64, ptr %12, align 8
  %342 = shl i64 %341, 32
  %343 = load i64, ptr %12, align 8
  %344 = lshr i64 %343, 32
  %345 = or i64 %342, %344
  store i64 %345, ptr %12, align 8
  %346 = load i64, ptr %13, align 8
  %347 = load i64, ptr %10, align 8
  %348 = add i64 %347, %346
  store i64 %348, ptr %10, align 8
  %349 = load i64, ptr %13, align 8
  %350 = shl i64 %349, 21
  %351 = load i64, ptr %13, align 8
  %352 = lshr i64 %351, 43
  %353 = or i64 %350, %352
  store i64 %353, ptr %13, align 8
  %354 = load i64, ptr %10, align 8
  %355 = load i64, ptr %13, align 8
  %356 = xor i64 %355, %354
  store i64 %356, ptr %13, align 8
  br label %357

357:                                              ; preds = %302
  br label %358

358:                                              ; preds = %357
  %359 = load i64, ptr %9, align 8
  %360 = add i64 %359, 1
  store i64 %360, ptr %9, align 8
  br label %298, !llvm.loop !11

361:                                              ; preds = %298
  %362 = load i64, ptr %11, align 8
  %363 = load i64, ptr %12, align 8
  %364 = xor i64 %362, %363
  %365 = load i64, ptr %13, align 8
  %366 = xor i64 %364, %365
  ret i64 %366
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @stbds_hmfree_func(ptr noundef %0, i64 noundef %1) #0 {
  %3 = alloca ptr, align 8
  %4 = alloca i64, align 8
  %5 = alloca i64, align 8
  store ptr %0, ptr %3, align 8
  store i64 %1, ptr %4, align 8
  %6 = load ptr, ptr %3, align 8
  %7 = icmp eq ptr %6, null
  br i1 %7, label %8, label %9

8:                                                ; preds = %2
  br label %57

9:                                                ; preds = %2
  %10 = load ptr, ptr %3, align 8
  %11 = getelementptr inbounds %struct.stbds_array_header, ptr %10, i64 -1
  %12 = getelementptr inbounds %struct.stbds_array_header, ptr %11, i32 0, i32 2
  %13 = load ptr, ptr %12, align 8
  %14 = icmp ne ptr %13, null
  br i1 %14, label %15, label %50

15:                                               ; preds = %9
  %16 = load ptr, ptr %3, align 8
  %17 = getelementptr inbounds %struct.stbds_array_header, ptr %16, i64 -1
  %18 = getelementptr inbounds %struct.stbds_array_header, ptr %17, i32 0, i32 2
  %19 = load ptr, ptr %18, align 8
  %20 = getelementptr inbounds %struct.stbds_hash_index, ptr %19, i32 0, i32 9
  %21 = getelementptr inbounds %struct.stbds_string_arena, ptr %20, i32 0, i32 3
  %22 = load i8, ptr %21, align 1
  %23 = zext i8 %22 to i32
  %24 = icmp eq i32 %23, 2
  br i1 %24, label %25, label %44

25:                                               ; preds = %15
  store i64 1, ptr %5, align 8
  br label %26

26:                                               ; preds = %40, %25
  %27 = load i64, ptr %5, align 8
  %28 = load ptr, ptr %3, align 8
  %29 = getelementptr inbounds %struct.stbds_array_header, ptr %28, i64 -1
  %30 = getelementptr inbounds %struct.stbds_array_header, ptr %29, i32 0, i32 0
  %31 = load i64, ptr %30, align 8
  %32 = icmp ult i64 %27, %31
  br i1 %32, label %33, label %43

33:                                               ; preds = %26
  %34 = load ptr, ptr %3, align 8
  %35 = load i64, ptr %4, align 8
  %36 = load i64, ptr %5, align 8
  %37 = mul i64 %35, %36
  %38 = getelementptr inbounds i8, ptr %34, i64 %37
  %39 = load ptr, ptr %38, align 8
  call void @free(ptr noundef %39)
  br label %40

40:                                               ; preds = %33
  %41 = load i64, ptr %5, align 8
  %42 = add i64 %41, 1
  store i64 %42, ptr %5, align 8
  br label %26, !llvm.loop !12

43:                                               ; preds = %26
  br label %44

44:                                               ; preds = %43, %15
  %45 = load ptr, ptr %3, align 8
  %46 = getelementptr inbounds %struct.stbds_array_header, ptr %45, i64 -1
  %47 = getelementptr inbounds %struct.stbds_array_header, ptr %46, i32 0, i32 2
  %48 = load ptr, ptr %47, align 8
  %49 = getelementptr inbounds %struct.stbds_hash_index, ptr %48, i32 0, i32 9
  call void @stbds_strreset(ptr noundef %49)
  br label %50

50:                                               ; preds = %44, %9
  %51 = load ptr, ptr %3, align 8
  %52 = getelementptr inbounds %struct.stbds_array_header, ptr %51, i64 -1
  %53 = getelementptr inbounds %struct.stbds_array_header, ptr %52, i32 0, i32 2
  %54 = load ptr, ptr %53, align 8
  call void @free(ptr noundef %54)
  %55 = load ptr, ptr %3, align 8
  %56 = getelementptr inbounds %struct.stbds_array_header, ptr %55, i64 -1
  call void @free(ptr noundef %56)
  br label %57

57:                                               ; preds = %50, %8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @stbds_strreset(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %5 = load ptr, ptr %2, align 8
  %6 = getelementptr inbounds %struct.stbds_string_arena, ptr %5, i32 0, i32 0
  %7 = load ptr, ptr %6, align 8
  store ptr %7, ptr %3, align 8
  br label %8

8:                                                ; preds = %11, %1
  %9 = load ptr, ptr %3, align 8
  %10 = icmp ne ptr %9, null
  br i1 %10, label %11, label %17

11:                                               ; preds = %8
  %12 = load ptr, ptr %3, align 8
  %13 = getelementptr inbounds %struct.stbds_string_block, ptr %12, i32 0, i32 0
  %14 = load ptr, ptr %13, align 8
  store ptr %14, ptr %4, align 8
  %15 = load ptr, ptr %3, align 8
  call void @free(ptr noundef %15)
  %16 = load ptr, ptr %4, align 8
  store ptr %16, ptr %3, align 8
  br label %8, !llvm.loop !13

17:                                               ; preds = %8
  %18 = load ptr, ptr %2, align 8
  %19 = load ptr, ptr %2, align 8
  %20 = call i64 @llvm.objectsize.i64.p0(ptr %19, i1 false, i1 true, i1 false)
  %21 = call ptr @__memset_chk(ptr noundef %18, i32 noundef 0, i64 noundef 24, i64 noundef %20) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define ptr @stbds_hmget_key_ts(ptr noundef %0, i64 noundef %1, ptr noundef %2, i64 noundef %3, ptr noundef %4, i32 noundef %5) #0 {
  %7 = alloca ptr, align 8
  %8 = alloca ptr, align 8
  %9 = alloca i64, align 8
  %10 = alloca ptr, align 8
  %11 = alloca i64, align 8
  %12 = alloca ptr, align 8
  %13 = alloca i32, align 4
  %14 = alloca i64, align 8
  %15 = alloca ptr, align 8
  %16 = alloca ptr, align 8
  %17 = alloca i64, align 8
  %18 = alloca ptr, align 8
  store ptr %0, ptr %8, align 8
  store i64 %1, ptr %9, align 8
  store ptr %2, ptr %10, align 8
  store i64 %3, ptr %11, align 8
  store ptr %4, ptr %12, align 8
  store i32 %5, ptr %13, align 4
  store i64 0, ptr %14, align 8
  %19 = load ptr, ptr %8, align 8
  %20 = icmp eq ptr %19, null
  br i1 %20, label %21, label %38

21:                                               ; preds = %6
  %22 = load i64, ptr %9, align 8
  %23 = call ptr @stbds_arrgrowf(ptr noundef null, i64 noundef %22, i64 noundef 0, i64 noundef 1)
  store ptr %23, ptr %8, align 8
  %24 = load ptr, ptr %8, align 8
  %25 = getelementptr inbounds %struct.stbds_array_header, ptr %24, i64 -1
  %26 = getelementptr inbounds %struct.stbds_array_header, ptr %25, i32 0, i32 0
  %27 = load i64, ptr %26, align 8
  %28 = add i64 %27, 1
  store i64 %28, ptr %26, align 8
  %29 = load ptr, ptr %8, align 8
  %30 = load i64, ptr %9, align 8
  %31 = load ptr, ptr %8, align 8
  %32 = call i64 @llvm.objectsize.i64.p0(ptr %31, i1 false, i1 true, i1 false)
  %33 = call ptr @__memset_chk(ptr noundef %29, i32 noundef 0, i64 noundef %30, i64 noundef %32) #8
  %34 = load ptr, ptr %12, align 8
  store i64 -1, ptr %34, align 8
  %35 = load ptr, ptr %8, align 8
  %36 = load i64, ptr %9, align 8
  %37 = getelementptr inbounds i8, ptr %35, i64 %36
  store ptr %37, ptr %7, align 8
  br label %80

38:                                               ; preds = %6
  %39 = load ptr, ptr %8, align 8
  %40 = load i64, ptr %9, align 8
  %41 = sub i64 0, %40
  %42 = getelementptr inbounds i8, ptr %39, i64 %41
  store ptr %42, ptr %16, align 8
  %43 = load ptr, ptr %16, align 8
  %44 = getelementptr inbounds %struct.stbds_array_header, ptr %43, i64 -1
  %45 = getelementptr inbounds %struct.stbds_array_header, ptr %44, i32 0, i32 2
  %46 = load ptr, ptr %45, align 8
  store ptr %46, ptr %15, align 8
  %47 = load ptr, ptr %15, align 8
  %48 = icmp eq ptr %47, null
  br i1 %48, label %49, label %51

49:                                               ; preds = %38
  %50 = load ptr, ptr %12, align 8
  store i64 -1, ptr %50, align 8
  br label %78

51:                                               ; preds = %38
  %52 = load ptr, ptr %8, align 8
  %53 = load i64, ptr %9, align 8
  %54 = load ptr, ptr %10, align 8
  %55 = load i64, ptr %11, align 8
  %56 = load i64, ptr %14, align 8
  %57 = load i32, ptr %13, align 4
  %58 = call i64 @stbds_hm_find_slot(ptr noundef %52, i64 noundef %53, ptr noundef %54, i64 noundef %55, i64 noundef %56, i32 noundef %57)
  store i64 %58, ptr %17, align 8
  %59 = load i64, ptr %17, align 8
  %60 = icmp slt i64 %59, 0
  br i1 %60, label %61, label %63

61:                                               ; preds = %51
  %62 = load ptr, ptr %12, align 8
  store i64 -1, ptr %62, align 8
  br label %77

63:                                               ; preds = %51
  %64 = load ptr, ptr %15, align 8
  %65 = getelementptr inbounds %struct.stbds_hash_index, ptr %64, i32 0, i32 10
  %66 = load ptr, ptr %65, align 8
  %67 = load i64, ptr %17, align 8
  %68 = ashr i64 %67, 3
  %69 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %66, i64 %68
  store ptr %69, ptr %18, align 8
  %70 = load ptr, ptr %18, align 8
  %71 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %70, i32 0, i32 1
  %72 = load i64, ptr %17, align 8
  %73 = and i64 %72, 7
  %74 = getelementptr inbounds [8 x i64], ptr %71, i64 0, i64 %73
  %75 = load i64, ptr %74, align 8
  %76 = load ptr, ptr %12, align 8
  store i64 %75, ptr %76, align 8
  br label %77

77:                                               ; preds = %63, %61
  br label %78

78:                                               ; preds = %77, %49
  %79 = load ptr, ptr %8, align 8
  store ptr %79, ptr %7, align 8
  br label %80

80:                                               ; preds = %78, %21
  %81 = load ptr, ptr %7, align 8
  ret ptr %81
}

; Function Attrs: nounwind
declare ptr @__memset_chk(ptr noundef, i32 noundef, i64 noundef, i64 noundef) #4

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i64 @llvm.objectsize.i64.p0(ptr, i1 immarg, i1 immarg, i1 immarg) #5

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define internal i64 @stbds_hm_find_slot(ptr noundef %0, i64 noundef %1, ptr noundef %2, i64 noundef %3, i64 noundef %4, i32 noundef %5) #0 {
  %7 = alloca i64, align 8
  %8 = alloca ptr, align 8
  %9 = alloca i64, align 8
  %10 = alloca ptr, align 8
  %11 = alloca i64, align 8
  %12 = alloca i64, align 8
  %13 = alloca i32, align 4
  %14 = alloca ptr, align 8
  %15 = alloca ptr, align 8
  %16 = alloca i64, align 8
  %17 = alloca i64, align 8
  %18 = alloca i64, align 8
  %19 = alloca i64, align 8
  %20 = alloca i64, align 8
  %21 = alloca ptr, align 8
  store ptr %0, ptr %8, align 8
  store i64 %1, ptr %9, align 8
  store ptr %2, ptr %10, align 8
  store i64 %3, ptr %11, align 8
  store i64 %4, ptr %12, align 8
  store i32 %5, ptr %13, align 4
  %22 = load ptr, ptr %8, align 8
  %23 = load i64, ptr %9, align 8
  %24 = sub i64 0, %23
  %25 = getelementptr inbounds i8, ptr %22, i64 %24
  store ptr %25, ptr %14, align 8
  %26 = load ptr, ptr %14, align 8
  %27 = getelementptr inbounds %struct.stbds_array_header, ptr %26, i64 -1
  %28 = getelementptr inbounds %struct.stbds_array_header, ptr %27, i32 0, i32 2
  %29 = load ptr, ptr %28, align 8
  store ptr %29, ptr %15, align 8
  %30 = load i32, ptr %13, align 4
  %31 = icmp sge i32 %30, 1
  br i1 %31, label %32, label %38

32:                                               ; preds = %6
  %33 = load ptr, ptr %10, align 8
  %34 = load ptr, ptr %15, align 8
  %35 = getelementptr inbounds %struct.stbds_hash_index, ptr %34, i32 0, i32 7
  %36 = load i64, ptr %35, align 8
  %37 = call i64 @stbds_hash_string(ptr noundef %33, i64 noundef %36)
  br label %45

38:                                               ; preds = %6
  %39 = load ptr, ptr %10, align 8
  %40 = load i64, ptr %11, align 8
  %41 = load ptr, ptr %15, align 8
  %42 = getelementptr inbounds %struct.stbds_hash_index, ptr %41, i32 0, i32 7
  %43 = load i64, ptr %42, align 8
  %44 = call i64 @stbds_hash_bytes(ptr noundef %39, i64 noundef %40, i64 noundef %43)
  br label %45

45:                                               ; preds = %38, %32
  %46 = phi i64 [ %37, %32 ], [ %44, %38 ]
  store i64 %46, ptr %16, align 8
  store i64 8, ptr %17, align 8
  %47 = load i64, ptr %16, align 8
  %48 = icmp ult i64 %47, 2
  br i1 %48, label %49, label %52

49:                                               ; preds = %45
  %50 = load i64, ptr %16, align 8
  %51 = add i64 %50, 2
  store i64 %51, ptr %16, align 8
  br label %52

52:                                               ; preds = %49, %45
  %53 = load i64, ptr %16, align 8
  %54 = load ptr, ptr %15, align 8
  %55 = getelementptr inbounds %struct.stbds_hash_index, ptr %54, i32 0, i32 1
  %56 = load i64, ptr %55, align 8
  %57 = load ptr, ptr %15, align 8
  %58 = getelementptr inbounds %struct.stbds_hash_index, ptr %57, i32 0, i32 8
  %59 = load i64, ptr %58, align 8
  %60 = call i64 @stbds_probe_position(i64 noundef %53, i64 noundef %56, i64 noundef %59)
  store i64 %60, ptr %20, align 8
  br label %61

61:                                               ; preds = %162, %52
  %62 = load ptr, ptr %15, align 8
  %63 = getelementptr inbounds %struct.stbds_hash_index, ptr %62, i32 0, i32 10
  %64 = load ptr, ptr %63, align 8
  %65 = load i64, ptr %20, align 8
  %66 = lshr i64 %65, 3
  %67 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %64, i64 %66
  store ptr %67, ptr %21, align 8
  %68 = load i64, ptr %20, align 8
  %69 = and i64 %68, 7
  store i64 %69, ptr %19, align 8
  br label %70

70:                                               ; preds = %111, %61
  %71 = load i64, ptr %19, align 8
  %72 = icmp ult i64 %71, 8
  br i1 %72, label %73, label %114

73:                                               ; preds = %70
  %74 = load ptr, ptr %21, align 8
  %75 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %74, i32 0, i32 0
  %76 = load i64, ptr %19, align 8
  %77 = getelementptr inbounds [8 x i64], ptr %75, i64 0, i64 %76
  %78 = load i64, ptr %77, align 8
  %79 = load i64, ptr %16, align 8
  %80 = icmp eq i64 %78, %79
  br i1 %80, label %81, label %101

81:                                               ; preds = %73
  %82 = load ptr, ptr %8, align 8
  %83 = load i64, ptr %9, align 8
  %84 = load ptr, ptr %10, align 8
  %85 = load i64, ptr %11, align 8
  %86 = load i64, ptr %12, align 8
  %87 = load i32, ptr %13, align 4
  %88 = load ptr, ptr %21, align 8
  %89 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %88, i32 0, i32 1
  %90 = load i64, ptr %19, align 8
  %91 = getelementptr inbounds [8 x i64], ptr %89, i64 0, i64 %90
  %92 = load i64, ptr %91, align 8
  %93 = call i32 @stbds_is_key_equal(ptr noundef %82, i64 noundef %83, ptr noundef %84, i64 noundef %85, i64 noundef %86, i32 noundef %87, i64 noundef %92)
  %94 = icmp ne i32 %93, 0
  br i1 %94, label %95, label %100

95:                                               ; preds = %81
  %96 = load i64, ptr %20, align 8
  %97 = and i64 %96, -8
  %98 = load i64, ptr %19, align 8
  %99 = add i64 %97, %98
  store i64 %99, ptr %7, align 8
  br label %174

100:                                              ; preds = %81
  br label %110

101:                                              ; preds = %73
  %102 = load ptr, ptr %21, align 8
  %103 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %102, i32 0, i32 0
  %104 = load i64, ptr %19, align 8
  %105 = getelementptr inbounds [8 x i64], ptr %103, i64 0, i64 %104
  %106 = load i64, ptr %105, align 8
  %107 = icmp eq i64 %106, 0
  br i1 %107, label %108, label %109

108:                                              ; preds = %101
  store i64 -1, ptr %7, align 8
  br label %174

109:                                              ; preds = %101
  br label %110

110:                                              ; preds = %109, %100
  br label %111

111:                                              ; preds = %110
  %112 = load i64, ptr %19, align 8
  %113 = add i64 %112, 1
  store i64 %113, ptr %19, align 8
  br label %70, !llvm.loop !14

114:                                              ; preds = %70
  %115 = load i64, ptr %20, align 8
  %116 = and i64 %115, 7
  store i64 %116, ptr %18, align 8
  store i64 0, ptr %19, align 8
  br label %117

117:                                              ; preds = %159, %114
  %118 = load i64, ptr %19, align 8
  %119 = load i64, ptr %18, align 8
  %120 = icmp ult i64 %118, %119
  br i1 %120, label %121, label %162

121:                                              ; preds = %117
  %122 = load ptr, ptr %21, align 8
  %123 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %122, i32 0, i32 0
  %124 = load i64, ptr %19, align 8
  %125 = getelementptr inbounds [8 x i64], ptr %123, i64 0, i64 %124
  %126 = load i64, ptr %125, align 8
  %127 = load i64, ptr %16, align 8
  %128 = icmp eq i64 %126, %127
  br i1 %128, label %129, label %149

129:                                              ; preds = %121
  %130 = load ptr, ptr %8, align 8
  %131 = load i64, ptr %9, align 8
  %132 = load ptr, ptr %10, align 8
  %133 = load i64, ptr %11, align 8
  %134 = load i64, ptr %12, align 8
  %135 = load i32, ptr %13, align 4
  %136 = load ptr, ptr %21, align 8
  %137 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %136, i32 0, i32 1
  %138 = load i64, ptr %19, align 8
  %139 = getelementptr inbounds [8 x i64], ptr %137, i64 0, i64 %138
  %140 = load i64, ptr %139, align 8
  %141 = call i32 @stbds_is_key_equal(ptr noundef %130, i64 noundef %131, ptr noundef %132, i64 noundef %133, i64 noundef %134, i32 noundef %135, i64 noundef %140)
  %142 = icmp ne i32 %141, 0
  br i1 %142, label %143, label %148

143:                                              ; preds = %129
  %144 = load i64, ptr %20, align 8
  %145 = and i64 %144, -8
  %146 = load i64, ptr %19, align 8
  %147 = add i64 %145, %146
  store i64 %147, ptr %7, align 8
  br label %174

148:                                              ; preds = %129
  br label %158

149:                                              ; preds = %121
  %150 = load ptr, ptr %21, align 8
  %151 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %150, i32 0, i32 0
  %152 = load i64, ptr %19, align 8
  %153 = getelementptr inbounds [8 x i64], ptr %151, i64 0, i64 %152
  %154 = load i64, ptr %153, align 8
  %155 = icmp eq i64 %154, 0
  br i1 %155, label %156, label %157

156:                                              ; preds = %149
  store i64 -1, ptr %7, align 8
  br label %174

157:                                              ; preds = %149
  br label %158

158:                                              ; preds = %157, %148
  br label %159

159:                                              ; preds = %158
  %160 = load i64, ptr %19, align 8
  %161 = add i64 %160, 1
  store i64 %161, ptr %19, align 8
  br label %117, !llvm.loop !15

162:                                              ; preds = %117
  %163 = load i64, ptr %17, align 8
  %164 = load i64, ptr %20, align 8
  %165 = add i64 %164, %163
  store i64 %165, ptr %20, align 8
  %166 = load i64, ptr %17, align 8
  %167 = add i64 %166, 8
  store i64 %167, ptr %17, align 8
  %168 = load ptr, ptr %15, align 8
  %169 = getelementptr inbounds %struct.stbds_hash_index, ptr %168, i32 0, i32 1
  %170 = load i64, ptr %169, align 8
  %171 = sub i64 %170, 1
  %172 = load i64, ptr %20, align 8
  %173 = and i64 %172, %171
  store i64 %173, ptr %20, align 8
  br label %61

174:                                              ; preds = %156, %143, %108, %95
  %175 = load i64, ptr %7, align 8
  ret i64 %175
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define ptr @stbds_hmget_key(ptr noundef %0, i64 noundef %1, ptr noundef %2, i64 noundef %3, i32 noundef %4) #0 {
  %6 = alloca ptr, align 8
  %7 = alloca i64, align 8
  %8 = alloca ptr, align 8
  %9 = alloca i64, align 8
  %10 = alloca i32, align 4
  %11 = alloca i64, align 8
  %12 = alloca ptr, align 8
  store ptr %0, ptr %6, align 8
  store i64 %1, ptr %7, align 8
  store ptr %2, ptr %8, align 8
  store i64 %3, ptr %9, align 8
  store i32 %4, ptr %10, align 4
  %13 = load ptr, ptr %6, align 8
  %14 = load i64, ptr %7, align 8
  %15 = load ptr, ptr %8, align 8
  %16 = load i64, ptr %9, align 8
  %17 = load i32, ptr %10, align 4
  %18 = call ptr @stbds_hmget_key_ts(ptr noundef %13, i64 noundef %14, ptr noundef %15, i64 noundef %16, ptr noundef %11, i32 noundef %17)
  store ptr %18, ptr %12, align 8
  %19 = load i64, ptr %11, align 8
  %20 = load ptr, ptr %12, align 8
  %21 = load i64, ptr %7, align 8
  %22 = sub i64 0, %21
  %23 = getelementptr inbounds i8, ptr %20, i64 %22
  %24 = getelementptr inbounds %struct.stbds_array_header, ptr %23, i64 -1
  %25 = getelementptr inbounds %struct.stbds_array_header, ptr %24, i32 0, i32 3
  store i64 %19, ptr %25, align 8
  %26 = load ptr, ptr %12, align 8
  ret ptr %26
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define ptr @stbds_hmput_default(ptr noundef %0, i64 noundef %1) #0 {
  %3 = alloca ptr, align 8
  %4 = alloca i64, align 8
  store ptr %0, ptr %3, align 8
  store i64 %1, ptr %4, align 8
  %5 = load ptr, ptr %3, align 8
  %6 = icmp eq ptr %5, null
  br i1 %6, label %16, label %7

7:                                                ; preds = %2
  %8 = load ptr, ptr %3, align 8
  %9 = load i64, ptr %4, align 8
  %10 = sub i64 0, %9
  %11 = getelementptr inbounds i8, ptr %8, i64 %10
  %12 = getelementptr inbounds %struct.stbds_array_header, ptr %11, i64 -1
  %13 = getelementptr inbounds %struct.stbds_array_header, ptr %12, i32 0, i32 0
  %14 = load i64, ptr %13, align 8
  %15 = icmp eq i64 %14, 0
  br i1 %15, label %16, label %42

16:                                               ; preds = %7, %2
  %17 = load ptr, ptr %3, align 8
  %18 = icmp ne ptr %17, null
  br i1 %18, label %19, label %24

19:                                               ; preds = %16
  %20 = load ptr, ptr %3, align 8
  %21 = load i64, ptr %4, align 8
  %22 = sub i64 0, %21
  %23 = getelementptr inbounds i8, ptr %20, i64 %22
  br label %25

24:                                               ; preds = %16
  br label %25

25:                                               ; preds = %24, %19
  %26 = phi ptr [ %23, %19 ], [ null, %24 ]
  %27 = load i64, ptr %4, align 8
  %28 = call ptr @stbds_arrgrowf(ptr noundef %26, i64 noundef %27, i64 noundef 0, i64 noundef 1)
  store ptr %28, ptr %3, align 8
  %29 = load ptr, ptr %3, align 8
  %30 = getelementptr inbounds %struct.stbds_array_header, ptr %29, i64 -1
  %31 = getelementptr inbounds %struct.stbds_array_header, ptr %30, i32 0, i32 0
  %32 = load i64, ptr %31, align 8
  %33 = add i64 %32, 1
  store i64 %33, ptr %31, align 8
  %34 = load ptr, ptr %3, align 8
  %35 = load i64, ptr %4, align 8
  %36 = load ptr, ptr %3, align 8
  %37 = call i64 @llvm.objectsize.i64.p0(ptr %36, i1 false, i1 true, i1 false)
  %38 = call ptr @__memset_chk(ptr noundef %34, i32 noundef 0, i64 noundef %35, i64 noundef %37) #8
  %39 = load ptr, ptr %3, align 8
  %40 = load i64, ptr %4, align 8
  %41 = getelementptr inbounds i8, ptr %39, i64 %40
  store ptr %41, ptr %3, align 8
  br label %42

42:                                               ; preds = %25, %7
  %43 = load ptr, ptr %3, align 8
  ret ptr %43
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define ptr @stbds_hmput_key(ptr noundef %0, i64 noundef %1, ptr noundef %2, i64 noundef %3, i32 noundef %4) #0 {
  %6 = alloca ptr, align 8
  %7 = alloca ptr, align 8
  %8 = alloca i64, align 8
  %9 = alloca ptr, align 8
  %10 = alloca i64, align 8
  %11 = alloca i32, align 4
  %12 = alloca i64, align 8
  %13 = alloca ptr, align 8
  %14 = alloca ptr, align 8
  %15 = alloca ptr, align 8
  %16 = alloca i64, align 8
  %17 = alloca i64, align 8
  %18 = alloca i64, align 8
  %19 = alloca i64, align 8
  %20 = alloca i64, align 8
  %21 = alloca ptr, align 8
  %22 = alloca i64, align 8
  %23 = alloca i64, align 8
  %24 = alloca i64, align 8
  store ptr %0, ptr %7, align 8
  store i64 %1, ptr %8, align 8
  store ptr %2, ptr %9, align 8
  store i64 %3, ptr %10, align 8
  store i32 %4, ptr %11, align 4
  store i64 0, ptr %12, align 8
  %25 = load ptr, ptr %7, align 8
  %26 = icmp eq ptr %25, null
  br i1 %26, label %27, label %43

27:                                               ; preds = %5
  %28 = load i64, ptr %8, align 8
  %29 = call ptr @stbds_arrgrowf(ptr noundef null, i64 noundef %28, i64 noundef 0, i64 noundef 1)
  store ptr %29, ptr %7, align 8
  %30 = load ptr, ptr %7, align 8
  %31 = load i64, ptr %8, align 8
  %32 = load ptr, ptr %7, align 8
  %33 = call i64 @llvm.objectsize.i64.p0(ptr %32, i1 false, i1 true, i1 false)
  %34 = call ptr @__memset_chk(ptr noundef %30, i32 noundef 0, i64 noundef %31, i64 noundef %33) #8
  %35 = load ptr, ptr %7, align 8
  %36 = getelementptr inbounds %struct.stbds_array_header, ptr %35, i64 -1
  %37 = getelementptr inbounds %struct.stbds_array_header, ptr %36, i32 0, i32 0
  %38 = load i64, ptr %37, align 8
  %39 = add i64 %38, 1
  store i64 %39, ptr %37, align 8
  %40 = load ptr, ptr %7, align 8
  %41 = load i64, ptr %8, align 8
  %42 = getelementptr inbounds i8, ptr %40, i64 %41
  store ptr %42, ptr %7, align 8
  br label %43

43:                                               ; preds = %27, %5
  %44 = load ptr, ptr %7, align 8
  store ptr %44, ptr %13, align 8
  %45 = load ptr, ptr %7, align 8
  %46 = load i64, ptr %8, align 8
  %47 = sub i64 0, %46
  %48 = getelementptr inbounds i8, ptr %45, i64 %47
  store ptr %48, ptr %7, align 8
  %49 = load ptr, ptr %7, align 8
  %50 = getelementptr inbounds %struct.stbds_array_header, ptr %49, i64 -1
  %51 = getelementptr inbounds %struct.stbds_array_header, ptr %50, i32 0, i32 2
  %52 = load ptr, ptr %51, align 8
  store ptr %52, ptr %14, align 8
  %53 = load ptr, ptr %14, align 8
  %54 = icmp eq ptr %53, null
  br i1 %54, label %63, label %55

55:                                               ; preds = %43
  %56 = load ptr, ptr %14, align 8
  %57 = getelementptr inbounds %struct.stbds_hash_index, ptr %56, i32 0, i32 2
  %58 = load i64, ptr %57, align 8
  %59 = load ptr, ptr %14, align 8
  %60 = getelementptr inbounds %struct.stbds_hash_index, ptr %59, i32 0, i32 3
  %61 = load i64, ptr %60, align 8
  %62 = icmp uge i64 %58, %61
  br i1 %62, label %63, label %95

63:                                               ; preds = %55, %43
  %64 = load ptr, ptr %14, align 8
  %65 = icmp eq ptr %64, null
  br i1 %65, label %66, label %67

66:                                               ; preds = %63
  br label %72

67:                                               ; preds = %63
  %68 = load ptr, ptr %14, align 8
  %69 = getelementptr inbounds %struct.stbds_hash_index, ptr %68, i32 0, i32 1
  %70 = load i64, ptr %69, align 8
  %71 = mul i64 %70, 2
  br label %72

72:                                               ; preds = %67, %66
  %73 = phi i64 [ 8, %66 ], [ %71, %67 ]
  store i64 %73, ptr %16, align 8
  %74 = load i64, ptr %16, align 8
  %75 = load ptr, ptr %14, align 8
  %76 = call ptr @stbds_make_hash_index(i64 noundef %74, ptr noundef %75)
  store ptr %76, ptr %15, align 8
  %77 = load ptr, ptr %14, align 8
  %78 = icmp ne ptr %77, null
  br i1 %78, label %79, label %81

79:                                               ; preds = %72
  %80 = load ptr, ptr %14, align 8
  call void @free(ptr noundef %80)
  br label %90

81:                                               ; preds = %72
  %82 = load i32, ptr %11, align 4
  %83 = icmp sge i32 %82, 1
  %84 = zext i1 %83 to i64
  %85 = select i1 %83, i32 1, i32 0
  %86 = trunc i32 %85 to i8
  %87 = load ptr, ptr %15, align 8
  %88 = getelementptr inbounds %struct.stbds_hash_index, ptr %87, i32 0, i32 9
  %89 = getelementptr inbounds %struct.stbds_string_arena, ptr %88, i32 0, i32 3
  store i8 %86, ptr %89, align 1
  br label %90

90:                                               ; preds = %81, %79
  %91 = load ptr, ptr %15, align 8
  store ptr %91, ptr %14, align 8
  %92 = load ptr, ptr %7, align 8
  %93 = getelementptr inbounds %struct.stbds_array_header, ptr %92, i64 -1
  %94 = getelementptr inbounds %struct.stbds_array_header, ptr %93, i32 0, i32 2
  store ptr %91, ptr %94, align 8
  br label %95

95:                                               ; preds = %90, %55
  %96 = load i32, ptr %11, align 4
  %97 = icmp sge i32 %96, 1
  br i1 %97, label %98, label %104

98:                                               ; preds = %95
  %99 = load ptr, ptr %9, align 8
  %100 = load ptr, ptr %14, align 8
  %101 = getelementptr inbounds %struct.stbds_hash_index, ptr %100, i32 0, i32 7
  %102 = load i64, ptr %101, align 8
  %103 = call i64 @stbds_hash_string(ptr noundef %99, i64 noundef %102)
  br label %111

104:                                              ; preds = %95
  %105 = load ptr, ptr %9, align 8
  %106 = load i64, ptr %10, align 8
  %107 = load ptr, ptr %14, align 8
  %108 = getelementptr inbounds %struct.stbds_hash_index, ptr %107, i32 0, i32 7
  %109 = load i64, ptr %108, align 8
  %110 = call i64 @stbds_hash_bytes(ptr noundef %105, i64 noundef %106, i64 noundef %109)
  br label %111

111:                                              ; preds = %104, %98
  %112 = phi i64 [ %103, %98 ], [ %110, %104 ]
  store i64 %112, ptr %17, align 8
  store i64 8, ptr %18, align 8
  store i64 -1, ptr %20, align 8
  %113 = load i64, ptr %17, align 8
  %114 = icmp ult i64 %113, 2
  br i1 %114, label %115, label %118

115:                                              ; preds = %111
  %116 = load i64, ptr %17, align 8
  %117 = add i64 %116, 2
  store i64 %117, ptr %17, align 8
  br label %118

118:                                              ; preds = %115, %111
  %119 = load i64, ptr %17, align 8
  %120 = load ptr, ptr %14, align 8
  %121 = getelementptr inbounds %struct.stbds_hash_index, ptr %120, i32 0, i32 1
  %122 = load i64, ptr %121, align 8
  %123 = load ptr, ptr %14, align 8
  %124 = getelementptr inbounds %struct.stbds_hash_index, ptr %123, i32 0, i32 8
  %125 = load i64, ptr %124, align 8
  %126 = call i64 @stbds_probe_position(i64 noundef %119, i64 noundef %122, i64 noundef %125)
  store i64 %126, ptr %19, align 8
  br label %127

127:                                              ; preds = %304, %118
  %128 = load ptr, ptr %14, align 8
  %129 = getelementptr inbounds %struct.stbds_hash_index, ptr %128, i32 0, i32 10
  %130 = load ptr, ptr %129, align 8
  %131 = load i64, ptr %19, align 8
  %132 = lshr i64 %131, 3
  %133 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %130, i64 %132
  store ptr %133, ptr %21, align 8
  %134 = load i64, ptr %19, align 8
  %135 = and i64 %134, 7
  store i64 %135, ptr %23, align 8
  br label %136

136:                                              ; preds = %225, %127
  %137 = load i64, ptr %23, align 8
  %138 = icmp ult i64 %137, 8
  br i1 %138, label %139, label %228

139:                                              ; preds = %136
  %140 = load ptr, ptr %21, align 8
  %141 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %140, i32 0, i32 0
  %142 = load i64, ptr %23, align 8
  %143 = getelementptr inbounds [8 x i64], ptr %141, i64 0, i64 %142
  %144 = load i64, ptr %143, align 8
  %145 = load i64, ptr %17, align 8
  %146 = icmp eq i64 %144, %145
  br i1 %146, label %147, label %194

147:                                              ; preds = %139
  %148 = load ptr, ptr %13, align 8
  %149 = load i64, ptr %8, align 8
  %150 = load ptr, ptr %9, align 8
  %151 = load i64, ptr %10, align 8
  %152 = load i64, ptr %12, align 8
  %153 = load i32, ptr %11, align 4
  %154 = load ptr, ptr %21, align 8
  %155 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %154, i32 0, i32 1
  %156 = load i64, ptr %23, align 8
  %157 = getelementptr inbounds [8 x i64], ptr %155, i64 0, i64 %156
  %158 = load i64, ptr %157, align 8
  %159 = call i32 @stbds_is_key_equal(ptr noundef %148, i64 noundef %149, ptr noundef %150, i64 noundef %151, i64 noundef %152, i32 noundef %153, i64 noundef %158)
  %160 = icmp ne i32 %159, 0
  br i1 %160, label %161, label %193

161:                                              ; preds = %147
  %162 = load ptr, ptr %21, align 8
  %163 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %162, i32 0, i32 1
  %164 = load i64, ptr %23, align 8
  %165 = getelementptr inbounds [8 x i64], ptr %163, i64 0, i64 %164
  %166 = load i64, ptr %165, align 8
  %167 = load ptr, ptr %7, align 8
  %168 = getelementptr inbounds %struct.stbds_array_header, ptr %167, i64 -1
  %169 = getelementptr inbounds %struct.stbds_array_header, ptr %168, i32 0, i32 3
  store i64 %166, ptr %169, align 8
  %170 = load i32, ptr %11, align 4
  %171 = icmp sge i32 %170, 1
  br i1 %171, label %172, label %189

172:                                              ; preds = %161
  %173 = load ptr, ptr %13, align 8
  %174 = load i64, ptr %8, align 8
  %175 = load ptr, ptr %21, align 8
  %176 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %175, i32 0, i32 1
  %177 = load i64, ptr %23, align 8
  %178 = getelementptr inbounds [8 x i64], ptr %176, i64 0, i64 %177
  %179 = load i64, ptr %178, align 8
  %180 = mul i64 %174, %179
  %181 = getelementptr inbounds i8, ptr %173, i64 %180
  %182 = load i64, ptr %12, align 8
  %183 = getelementptr inbounds i8, ptr %181, i64 %182
  %184 = load ptr, ptr %183, align 8
  %185 = load ptr, ptr %7, align 8
  %186 = getelementptr inbounds %struct.stbds_array_header, ptr %185, i64 -1
  %187 = getelementptr inbounds %struct.stbds_array_header, ptr %186, i32 0, i32 2
  %188 = load ptr, ptr %187, align 8
  store ptr %184, ptr %188, align 8
  br label %189

189:                                              ; preds = %172, %161
  %190 = load ptr, ptr %7, align 8
  %191 = load i64, ptr %8, align 8
  %192 = getelementptr inbounds i8, ptr %190, i64 %191
  store ptr %192, ptr %6, align 8
  br label %451

193:                                              ; preds = %147
  br label %224

194:                                              ; preds = %139
  %195 = load ptr, ptr %21, align 8
  %196 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %195, i32 0, i32 0
  %197 = load i64, ptr %23, align 8
  %198 = getelementptr inbounds [8 x i64], ptr %196, i64 0, i64 %197
  %199 = load i64, ptr %198, align 8
  %200 = icmp eq i64 %199, 0
  br i1 %200, label %201, label %206

201:                                              ; preds = %194
  %202 = load i64, ptr %19, align 8
  %203 = and i64 %202, -8
  %204 = load i64, ptr %23, align 8
  %205 = add i64 %203, %204
  store i64 %205, ptr %19, align 8
  br label %316

206:                                              ; preds = %194
  %207 = load i64, ptr %20, align 8
  %208 = icmp slt i64 %207, 0
  br i1 %208, label %209, label %222

209:                                              ; preds = %206
  %210 = load ptr, ptr %21, align 8
  %211 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %210, i32 0, i32 1
  %212 = load i64, ptr %23, align 8
  %213 = getelementptr inbounds [8 x i64], ptr %211, i64 0, i64 %212
  %214 = load i64, ptr %213, align 8
  %215 = icmp eq i64 %214, -2
  br i1 %215, label %216, label %221

216:                                              ; preds = %209
  %217 = load i64, ptr %19, align 8
  %218 = and i64 %217, -8
  %219 = load i64, ptr %23, align 8
  %220 = add i64 %218, %219
  store i64 %220, ptr %20, align 8
  br label %221

221:                                              ; preds = %216, %209
  br label %222

222:                                              ; preds = %221, %206
  br label %223

223:                                              ; preds = %222
  br label %224

224:                                              ; preds = %223, %193
  br label %225

225:                                              ; preds = %224
  %226 = load i64, ptr %23, align 8
  %227 = add i64 %226, 1
  store i64 %227, ptr %23, align 8
  br label %136, !llvm.loop !16

228:                                              ; preds = %136
  %229 = load i64, ptr %19, align 8
  %230 = and i64 %229, 7
  store i64 %230, ptr %22, align 8
  store i64 0, ptr %23, align 8
  br label %231

231:                                              ; preds = %301, %228
  %232 = load i64, ptr %23, align 8
  %233 = load i64, ptr %22, align 8
  %234 = icmp ult i64 %232, %233
  br i1 %234, label %235, label %304

235:                                              ; preds = %231
  %236 = load ptr, ptr %21, align 8
  %237 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %236, i32 0, i32 0
  %238 = load i64, ptr %23, align 8
  %239 = getelementptr inbounds [8 x i64], ptr %237, i64 0, i64 %238
  %240 = load i64, ptr %239, align 8
  %241 = load i64, ptr %17, align 8
  %242 = icmp eq i64 %240, %241
  br i1 %242, label %243, label %270

243:                                              ; preds = %235
  %244 = load ptr, ptr %13, align 8
  %245 = load i64, ptr %8, align 8
  %246 = load ptr, ptr %9, align 8
  %247 = load i64, ptr %10, align 8
  %248 = load i64, ptr %12, align 8
  %249 = load i32, ptr %11, align 4
  %250 = load ptr, ptr %21, align 8
  %251 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %250, i32 0, i32 1
  %252 = load i64, ptr %23, align 8
  %253 = getelementptr inbounds [8 x i64], ptr %251, i64 0, i64 %252
  %254 = load i64, ptr %253, align 8
  %255 = call i32 @stbds_is_key_equal(ptr noundef %244, i64 noundef %245, ptr noundef %246, i64 noundef %247, i64 noundef %248, i32 noundef %249, i64 noundef %254)
  %256 = icmp ne i32 %255, 0
  br i1 %256, label %257, label %269

257:                                              ; preds = %243
  %258 = load ptr, ptr %21, align 8
  %259 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %258, i32 0, i32 1
  %260 = load i64, ptr %23, align 8
  %261 = getelementptr inbounds [8 x i64], ptr %259, i64 0, i64 %260
  %262 = load i64, ptr %261, align 8
  %263 = load ptr, ptr %7, align 8
  %264 = getelementptr inbounds %struct.stbds_array_header, ptr %263, i64 -1
  %265 = getelementptr inbounds %struct.stbds_array_header, ptr %264, i32 0, i32 3
  store i64 %262, ptr %265, align 8
  %266 = load ptr, ptr %7, align 8
  %267 = load i64, ptr %8, align 8
  %268 = getelementptr inbounds i8, ptr %266, i64 %267
  store ptr %268, ptr %6, align 8
  br label %451

269:                                              ; preds = %243
  br label %300

270:                                              ; preds = %235
  %271 = load ptr, ptr %21, align 8
  %272 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %271, i32 0, i32 0
  %273 = load i64, ptr %23, align 8
  %274 = getelementptr inbounds [8 x i64], ptr %272, i64 0, i64 %273
  %275 = load i64, ptr %274, align 8
  %276 = icmp eq i64 %275, 0
  br i1 %276, label %277, label %282

277:                                              ; preds = %270
  %278 = load i64, ptr %19, align 8
  %279 = and i64 %278, -8
  %280 = load i64, ptr %23, align 8
  %281 = add i64 %279, %280
  store i64 %281, ptr %19, align 8
  br label %316

282:                                              ; preds = %270
  %283 = load i64, ptr %20, align 8
  %284 = icmp slt i64 %283, 0
  br i1 %284, label %285, label %298

285:                                              ; preds = %282
  %286 = load ptr, ptr %21, align 8
  %287 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %286, i32 0, i32 1
  %288 = load i64, ptr %23, align 8
  %289 = getelementptr inbounds [8 x i64], ptr %287, i64 0, i64 %288
  %290 = load i64, ptr %289, align 8
  %291 = icmp eq i64 %290, -2
  br i1 %291, label %292, label %297

292:                                              ; preds = %285
  %293 = load i64, ptr %19, align 8
  %294 = and i64 %293, -8
  %295 = load i64, ptr %23, align 8
  %296 = add i64 %294, %295
  store i64 %296, ptr %20, align 8
  br label %297

297:                                              ; preds = %292, %285
  br label %298

298:                                              ; preds = %297, %282
  br label %299

299:                                              ; preds = %298
  br label %300

300:                                              ; preds = %299, %269
  br label %301

301:                                              ; preds = %300
  %302 = load i64, ptr %23, align 8
  %303 = add i64 %302, 1
  store i64 %303, ptr %23, align 8
  br label %231, !llvm.loop !17

304:                                              ; preds = %231
  %305 = load i64, ptr %18, align 8
  %306 = load i64, ptr %19, align 8
  %307 = add i64 %306, %305
  store i64 %307, ptr %19, align 8
  %308 = load i64, ptr %18, align 8
  %309 = add i64 %308, 8
  store i64 %309, ptr %18, align 8
  %310 = load ptr, ptr %14, align 8
  %311 = getelementptr inbounds %struct.stbds_hash_index, ptr %310, i32 0, i32 1
  %312 = load i64, ptr %311, align 8
  %313 = sub i64 %312, 1
  %314 = load i64, ptr %19, align 8
  %315 = and i64 %314, %313
  store i64 %315, ptr %19, align 8
  br label %127

316:                                              ; preds = %277, %201
  %317 = load i64, ptr %20, align 8
  %318 = icmp sge i64 %317, 0
  br i1 %318, label %319, label %325

319:                                              ; preds = %316
  %320 = load i64, ptr %20, align 8
  store i64 %320, ptr %19, align 8
  %321 = load ptr, ptr %14, align 8
  %322 = getelementptr inbounds %struct.stbds_hash_index, ptr %321, i32 0, i32 5
  %323 = load i64, ptr %322, align 8
  %324 = add i64 %323, -1
  store i64 %324, ptr %322, align 8
  br label %325

325:                                              ; preds = %319, %316
  %326 = load ptr, ptr %14, align 8
  %327 = getelementptr inbounds %struct.stbds_hash_index, ptr %326, i32 0, i32 2
  %328 = load i64, ptr %327, align 8
  %329 = add i64 %328, 1
  store i64 %329, ptr %327, align 8
  %330 = load ptr, ptr %7, align 8
  %331 = icmp ne ptr %330, null
  br i1 %331, label %332, label %337

332:                                              ; preds = %325
  %333 = load ptr, ptr %7, align 8
  %334 = getelementptr inbounds %struct.stbds_array_header, ptr %333, i64 -1
  %335 = getelementptr inbounds %struct.stbds_array_header, ptr %334, i32 0, i32 0
  %336 = load i64, ptr %335, align 8
  br label %338

337:                                              ; preds = %325
  br label %338

338:                                              ; preds = %337, %332
  %339 = phi i64 [ %336, %332 ], [ 0, %337 ]
  store i64 %339, ptr %24, align 8
  %340 = load i64, ptr %24, align 8
  %341 = add i64 %340, 1
  %342 = load ptr, ptr %7, align 8
  %343 = icmp ne ptr %342, null
  br i1 %343, label %344, label %349

344:                                              ; preds = %338
  %345 = load ptr, ptr %7, align 8
  %346 = getelementptr inbounds %struct.stbds_array_header, ptr %345, i64 -1
  %347 = getelementptr inbounds %struct.stbds_array_header, ptr %346, i32 0, i32 1
  %348 = load i64, ptr %347, align 8
  br label %350

349:                                              ; preds = %338
  br label %350

350:                                              ; preds = %349, %344
  %351 = phi i64 [ %348, %344 ], [ 0, %349 ]
  %352 = icmp ugt i64 %341, %351
  br i1 %352, label %353, label %357

353:                                              ; preds = %350
  %354 = load ptr, ptr %7, align 8
  %355 = load i64, ptr %8, align 8
  %356 = call ptr @stbds_arrgrowf(ptr noundef %354, i64 noundef %355, i64 noundef 1, i64 noundef 0)
  store ptr %356, ptr %7, align 8
  br label %357

357:                                              ; preds = %353, %350
  %358 = load ptr, ptr %7, align 8
  %359 = load i64, ptr %8, align 8
  %360 = getelementptr inbounds i8, ptr %358, i64 %359
  store ptr %360, ptr %13, align 8
  %361 = load i64, ptr %24, align 8
  %362 = add nsw i64 %361, 1
  %363 = load ptr, ptr %7, align 8
  %364 = getelementptr inbounds %struct.stbds_array_header, ptr %363, i64 -1
  %365 = getelementptr inbounds %struct.stbds_array_header, ptr %364, i32 0, i32 0
  store i64 %362, ptr %365, align 8
  %366 = load ptr, ptr %14, align 8
  %367 = getelementptr inbounds %struct.stbds_hash_index, ptr %366, i32 0, i32 10
  %368 = load ptr, ptr %367, align 8
  %369 = load i64, ptr %19, align 8
  %370 = lshr i64 %369, 3
  %371 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %368, i64 %370
  store ptr %371, ptr %21, align 8
  %372 = load i64, ptr %17, align 8
  %373 = load ptr, ptr %21, align 8
  %374 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %373, i32 0, i32 0
  %375 = load i64, ptr %19, align 8
  %376 = and i64 %375, 7
  %377 = getelementptr inbounds [8 x i64], ptr %374, i64 0, i64 %376
  store i64 %372, ptr %377, align 8
  %378 = load i64, ptr %24, align 8
  %379 = sub nsw i64 %378, 1
  %380 = load ptr, ptr %21, align 8
  %381 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %380, i32 0, i32 1
  %382 = load i64, ptr %19, align 8
  %383 = and i64 %382, 7
  %384 = getelementptr inbounds [8 x i64], ptr %381, i64 0, i64 %383
  store i64 %379, ptr %384, align 8
  %385 = load i64, ptr %24, align 8
  %386 = sub nsw i64 %385, 1
  %387 = load ptr, ptr %7, align 8
  %388 = getelementptr inbounds %struct.stbds_array_header, ptr %387, i64 -1
  %389 = getelementptr inbounds %struct.stbds_array_header, ptr %388, i32 0, i32 3
  store i64 %386, ptr %389, align 8
  %390 = load ptr, ptr %14, align 8
  %391 = getelementptr inbounds %struct.stbds_hash_index, ptr %390, i32 0, i32 9
  %392 = getelementptr inbounds %struct.stbds_string_arena, ptr %391, i32 0, i32 3
  %393 = load i8, ptr %392, align 1
  %394 = zext i8 %393 to i32
  switch i32 %394, label %432 [
    i32 2, label %395
    i32 3, label %407
    i32 1, label %421
  ]

395:                                              ; preds = %357
  %396 = load ptr, ptr %9, align 8
  %397 = call ptr @stbds_strdup(ptr noundef %396)
  %398 = load ptr, ptr %7, align 8
  %399 = load i64, ptr %8, align 8
  %400 = load i64, ptr %24, align 8
  %401 = mul i64 %399, %400
  %402 = getelementptr inbounds i8, ptr %398, i64 %401
  store ptr %397, ptr %402, align 8
  %403 = load ptr, ptr %7, align 8
  %404 = getelementptr inbounds %struct.stbds_array_header, ptr %403, i64 -1
  %405 = getelementptr inbounds %struct.stbds_array_header, ptr %404, i32 0, i32 2
  %406 = load ptr, ptr %405, align 8
  store ptr %397, ptr %406, align 8
  br label %447

407:                                              ; preds = %357
  %408 = load ptr, ptr %14, align 8
  %409 = getelementptr inbounds %struct.stbds_hash_index, ptr %408, i32 0, i32 9
  %410 = load ptr, ptr %9, align 8
  %411 = call ptr @stbds_stralloc(ptr noundef %409, ptr noundef %410)
  %412 = load ptr, ptr %7, align 8
  %413 = load i64, ptr %8, align 8
  %414 = load i64, ptr %24, align 8
  %415 = mul i64 %413, %414
  %416 = getelementptr inbounds i8, ptr %412, i64 %415
  store ptr %411, ptr %416, align 8
  %417 = load ptr, ptr %7, align 8
  %418 = getelementptr inbounds %struct.stbds_array_header, ptr %417, i64 -1
  %419 = getelementptr inbounds %struct.stbds_array_header, ptr %418, i32 0, i32 2
  %420 = load ptr, ptr %419, align 8
  store ptr %411, ptr %420, align 8
  br label %447

421:                                              ; preds = %357
  %422 = load ptr, ptr %9, align 8
  %423 = load ptr, ptr %7, align 8
  %424 = load i64, ptr %8, align 8
  %425 = load i64, ptr %24, align 8
  %426 = mul i64 %424, %425
  %427 = getelementptr inbounds i8, ptr %423, i64 %426
  store ptr %422, ptr %427, align 8
  %428 = load ptr, ptr %7, align 8
  %429 = getelementptr inbounds %struct.stbds_array_header, ptr %428, i64 -1
  %430 = getelementptr inbounds %struct.stbds_array_header, ptr %429, i32 0, i32 2
  %431 = load ptr, ptr %430, align 8
  store ptr %422, ptr %431, align 8
  br label %447

432:                                              ; preds = %357
  %433 = load ptr, ptr %7, align 8
  %434 = load i64, ptr %8, align 8
  %435 = load i64, ptr %24, align 8
  %436 = mul i64 %434, %435
  %437 = getelementptr inbounds i8, ptr %433, i64 %436
  %438 = load ptr, ptr %9, align 8
  %439 = load i64, ptr %10, align 8
  %440 = load ptr, ptr %7, align 8
  %441 = load i64, ptr %8, align 8
  %442 = load i64, ptr %24, align 8
  %443 = mul i64 %441, %442
  %444 = getelementptr inbounds i8, ptr %440, i64 %443
  %445 = call i64 @llvm.objectsize.i64.p0(ptr %444, i1 false, i1 true, i1 false)
  %446 = call ptr @__memcpy_chk(ptr noundef %437, ptr noundef %438, i64 noundef %439, i64 noundef %445) #8
  br label %447

447:                                              ; preds = %432, %421, %407, %395
  %448 = load ptr, ptr %7, align 8
  %449 = load i64, ptr %8, align 8
  %450 = getelementptr inbounds i8, ptr %448, i64 %449
  store ptr %450, ptr %6, align 8
  br label %451

451:                                              ; preds = %447, %257, %189
  %452 = load ptr, ptr %6, align 8
  ret ptr %452
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define internal ptr @stbds_make_hash_index(i64 noundef %0, ptr noundef %1) #0 {
  %3 = alloca i64, align 8
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i64, align 8
  %7 = alloca i64, align 8
  %8 = alloca i64, align 8
  %9 = alloca i64, align 8
  %10 = alloca i64, align 8
  %11 = alloca ptr, align 8
  %12 = alloca i64, align 8
  %13 = alloca i64, align 8
  %14 = alloca ptr, align 8
  %15 = alloca i64, align 8
  %16 = alloca i64, align 8
  %17 = alloca i64, align 8
  %18 = alloca i64, align 8
  %19 = alloca i64, align 8
  %20 = alloca ptr, align 8
  store i64 %0, ptr %3, align 8
  store ptr %1, ptr %4, align 8
  %21 = load i64, ptr %3, align 8
  %22 = lshr i64 %21, 3
  %23 = mul i64 %22, 128
  %24 = add i64 %23, 104
  %25 = add i64 %24, 64
  %26 = sub i64 %25, 1
  %27 = call ptr @realloc(ptr noundef null, i64 noundef %26) #7
  store ptr %27, ptr %5, align 8
  %28 = load ptr, ptr %5, align 8
  %29 = getelementptr inbounds %struct.stbds_hash_index, ptr %28, i64 1
  %30 = ptrtoint ptr %29 to i64
  %31 = add i64 %30, 64
  %32 = sub i64 %31, 1
  %33 = and i64 %32, -64
  %34 = inttoptr i64 %33 to ptr
  %35 = load ptr, ptr %5, align 8
  %36 = getelementptr inbounds %struct.stbds_hash_index, ptr %35, i32 0, i32 10
  store ptr %34, ptr %36, align 8
  %37 = load i64, ptr %3, align 8
  %38 = load ptr, ptr %5, align 8
  %39 = getelementptr inbounds %struct.stbds_hash_index, ptr %38, i32 0, i32 1
  store i64 %37, ptr %39, align 8
  %40 = load i64, ptr %3, align 8
  %41 = call i64 @stbds_log2(i64 noundef %40)
  %42 = load ptr, ptr %5, align 8
  %43 = getelementptr inbounds %struct.stbds_hash_index, ptr %42, i32 0, i32 8
  store i64 %41, ptr %43, align 8
  %44 = load ptr, ptr %5, align 8
  %45 = getelementptr inbounds %struct.stbds_hash_index, ptr %44, i32 0, i32 5
  store i64 0, ptr %45, align 8
  %46 = load ptr, ptr %5, align 8
  %47 = getelementptr inbounds %struct.stbds_hash_index, ptr %46, i32 0, i32 2
  store i64 0, ptr %47, align 8
  %48 = load i64, ptr %3, align 8
  %49 = load i64, ptr %3, align 8
  %50 = lshr i64 %49, 2
  %51 = sub i64 %48, %50
  %52 = load ptr, ptr %5, align 8
  %53 = getelementptr inbounds %struct.stbds_hash_index, ptr %52, i32 0, i32 3
  store i64 %51, ptr %53, align 8
  %54 = load i64, ptr %3, align 8
  %55 = lshr i64 %54, 3
  %56 = load i64, ptr %3, align 8
  %57 = lshr i64 %56, 4
  %58 = add i64 %55, %57
  %59 = load ptr, ptr %5, align 8
  %60 = getelementptr inbounds %struct.stbds_hash_index, ptr %59, i32 0, i32 6
  store i64 %58, ptr %60, align 8
  %61 = load i64, ptr %3, align 8
  %62 = lshr i64 %61, 2
  %63 = load ptr, ptr %5, align 8
  %64 = getelementptr inbounds %struct.stbds_hash_index, ptr %63, i32 0, i32 4
  store i64 %62, ptr %64, align 8
  %65 = load i64, ptr %3, align 8
  %66 = icmp ule i64 %65, 8
  br i1 %66, label %67, label %70

67:                                               ; preds = %2
  %68 = load ptr, ptr %5, align 8
  %69 = getelementptr inbounds %struct.stbds_hash_index, ptr %68, i32 0, i32 4
  store i64 0, ptr %69, align 8
  br label %70

70:                                               ; preds = %67, %2
  %71 = load ptr, ptr %4, align 8
  %72 = icmp ne ptr %71, null
  br i1 %72, label %73, label %83

73:                                               ; preds = %70
  %74 = load ptr, ptr %5, align 8
  %75 = getelementptr inbounds %struct.stbds_hash_index, ptr %74, i32 0, i32 9
  %76 = load ptr, ptr %4, align 8
  %77 = getelementptr inbounds %struct.stbds_hash_index, ptr %76, i32 0, i32 9
  call void @llvm.memcpy.p0.p0.i64(ptr align 8 %75, ptr align 8 %77, i64 24, i1 false)
  %78 = load ptr, ptr %4, align 8
  %79 = getelementptr inbounds %struct.stbds_hash_index, ptr %78, i32 0, i32 7
  %80 = load i64, ptr %79, align 8
  %81 = load ptr, ptr %5, align 8
  %82 = getelementptr inbounds %struct.stbds_hash_index, ptr %81, i32 0, i32 7
  store i64 %80, ptr %82, align 8
  br label %130

83:                                               ; preds = %70
  %84 = load ptr, ptr %5, align 8
  %85 = getelementptr inbounds %struct.stbds_hash_index, ptr %84, i32 0, i32 9
  %86 = load ptr, ptr %5, align 8
  %87 = getelementptr inbounds %struct.stbds_hash_index, ptr %86, i32 0, i32 9
  %88 = call i64 @llvm.objectsize.i64.p0(ptr %87, i1 false, i1 true, i1 false)
  %89 = call ptr @__memset_chk(ptr noundef %85, i32 noundef 0, i64 noundef 24, i64 noundef %88) #8
  %90 = load i64, ptr @stbds_hash_seed, align 8
  %91 = load ptr, ptr %5, align 8
  %92 = getelementptr inbounds %struct.stbds_hash_index, ptr %91, i32 0, i32 7
  store i64 %90, ptr %92, align 8
  store i64 4165473040, ptr %8, align 8
  %93 = load i64, ptr %8, align 8
  %94 = shl i64 %93, 16
  store i64 %94, ptr %8, align 8
  %95 = load i64, ptr %8, align 8
  %96 = shl i64 %95, 16
  store i64 %96, ptr %8, align 8
  %97 = load i64, ptr %8, align 8
  %98 = lshr i64 %97, 16
  store i64 %98, ptr %8, align 8
  %99 = load i64, ptr %8, align 8
  %100 = lshr i64 %99, 16
  store i64 %100, ptr %8, align 8
  store i64 666578662, ptr %6, align 8
  %101 = load i64, ptr %6, align 8
  %102 = shl i64 %101, 16
  store i64 %102, ptr %6, align 8
  %103 = load i64, ptr %6, align 8
  %104 = shl i64 %103, 16
  store i64 %104, ptr %6, align 8
  %105 = load i64, ptr %8, align 8
  %106 = xor i64 %105, 2147001325
  %107 = load i64, ptr %6, align 8
  %108 = xor i64 %107, %106
  store i64 %108, ptr %6, align 8
  store i64 2678386204, ptr %8, align 8
  %109 = load i64, ptr %8, align 8
  %110 = shl i64 %109, 16
  store i64 %110, ptr %8, align 8
  %111 = load i64, ptr %8, align 8
  %112 = shl i64 %111, 16
  store i64 %112, ptr %8, align 8
  %113 = load i64, ptr %8, align 8
  %114 = lshr i64 %113, 16
  store i64 %114, ptr %8, align 8
  %115 = load i64, ptr %8, align 8
  %116 = lshr i64 %115, 16
  store i64 %116, ptr %8, align 8
  store i64 0, ptr %7, align 8
  %117 = load i64, ptr %7, align 8
  %118 = shl i64 %117, 16
  store i64 %118, ptr %7, align 8
  %119 = load i64, ptr %7, align 8
  %120 = shl i64 %119, 16
  store i64 %120, ptr %7, align 8
  %121 = load i64, ptr %8, align 8
  %122 = xor i64 %121, 715136305
  %123 = load i64, ptr %7, align 8
  %124 = xor i64 %123, %122
  store i64 %124, ptr %7, align 8
  %125 = load i64, ptr @stbds_hash_seed, align 8
  %126 = load i64, ptr %6, align 8
  %127 = mul i64 %125, %126
  %128 = load i64, ptr %7, align 8
  %129 = add i64 %127, %128
  store i64 %129, ptr @stbds_hash_seed, align 8
  br label %130

130:                                              ; preds = %83, %73
  store i64 0, ptr %9, align 8
  br label %131

131:                                              ; preds = %166, %130
  %132 = load i64, ptr %9, align 8
  %133 = load i64, ptr %3, align 8
  %134 = lshr i64 %133, 3
  %135 = icmp ult i64 %132, %134
  br i1 %135, label %136, label %169

136:                                              ; preds = %131
  %137 = load ptr, ptr %5, align 8
  %138 = getelementptr inbounds %struct.stbds_hash_index, ptr %137, i32 0, i32 10
  %139 = load ptr, ptr %138, align 8
  %140 = load i64, ptr %9, align 8
  %141 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %139, i64 %140
  store ptr %141, ptr %11, align 8
  store i64 0, ptr %10, align 8
  br label %142

142:                                              ; preds = %150, %136
  %143 = load i64, ptr %10, align 8
  %144 = icmp ult i64 %143, 8
  br i1 %144, label %145, label %153

145:                                              ; preds = %142
  %146 = load ptr, ptr %11, align 8
  %147 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %146, i32 0, i32 0
  %148 = load i64, ptr %10, align 8
  %149 = getelementptr inbounds [8 x i64], ptr %147, i64 0, i64 %148
  store i64 0, ptr %149, align 8
  br label %150

150:                                              ; preds = %145
  %151 = load i64, ptr %10, align 8
  %152 = add i64 %151, 1
  store i64 %152, ptr %10, align 8
  br label %142, !llvm.loop !18

153:                                              ; preds = %142
  store i64 0, ptr %10, align 8
  br label %154

154:                                              ; preds = %162, %153
  %155 = load i64, ptr %10, align 8
  %156 = icmp ult i64 %155, 8
  br i1 %156, label %157, label %165

157:                                              ; preds = %154
  %158 = load ptr, ptr %11, align 8
  %159 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %158, i32 0, i32 1
  %160 = load i64, ptr %10, align 8
  %161 = getelementptr inbounds [8 x i64], ptr %159, i64 0, i64 %160
  store i64 -1, ptr %161, align 8
  br label %162

162:                                              ; preds = %157
  %163 = load i64, ptr %10, align 8
  %164 = add i64 %163, 1
  store i64 %164, ptr %10, align 8
  br label %154, !llvm.loop !19

165:                                              ; preds = %154
  br label %166

166:                                              ; preds = %165
  %167 = load i64, ptr %9, align 8
  %168 = add i64 %167, 1
  store i64 %168, ptr %9, align 8
  br label %131, !llvm.loop !20

169:                                              ; preds = %131
  %170 = load ptr, ptr %4, align 8
  %171 = icmp ne ptr %170, null
  br i1 %171, label %172, label %308

172:                                              ; preds = %169
  %173 = load ptr, ptr %4, align 8
  %174 = getelementptr inbounds %struct.stbds_hash_index, ptr %173, i32 0, i32 2
  %175 = load i64, ptr %174, align 8
  %176 = load ptr, ptr %5, align 8
  %177 = getelementptr inbounds %struct.stbds_hash_index, ptr %176, i32 0, i32 2
  store i64 %175, ptr %177, align 8
  store i64 0, ptr %12, align 8
  br label %178

178:                                              ; preds = %304, %172
  %179 = load i64, ptr %12, align 8
  %180 = load ptr, ptr %4, align 8
  %181 = getelementptr inbounds %struct.stbds_hash_index, ptr %180, i32 0, i32 1
  %182 = load i64, ptr %181, align 8
  %183 = lshr i64 %182, 3
  %184 = icmp ult i64 %179, %183
  br i1 %184, label %185, label %307

185:                                              ; preds = %178
  %186 = load ptr, ptr %4, align 8
  %187 = getelementptr inbounds %struct.stbds_hash_index, ptr %186, i32 0, i32 10
  %188 = load ptr, ptr %187, align 8
  %189 = load i64, ptr %12, align 8
  %190 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %188, i64 %189
  store ptr %190, ptr %14, align 8
  store i64 0, ptr %13, align 8
  br label %191

191:                                              ; preds = %300, %185
  %192 = load i64, ptr %13, align 8
  %193 = icmp ult i64 %192, 8
  br i1 %193, label %194, label %303

194:                                              ; preds = %191
  %195 = load ptr, ptr %14, align 8
  %196 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %195, i32 0, i32 1
  %197 = load i64, ptr %13, align 8
  %198 = getelementptr inbounds [8 x i64], ptr %196, i64 0, i64 %197
  %199 = load i64, ptr %198, align 8
  %200 = icmp sge i64 %199, 0
  br i1 %200, label %201, label %298

201:                                              ; preds = %194
  %202 = load ptr, ptr %14, align 8
  %203 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %202, i32 0, i32 0
  %204 = load i64, ptr %13, align 8
  %205 = getelementptr inbounds [8 x i64], ptr %203, i64 0, i64 %204
  %206 = load i64, ptr %205, align 8
  store i64 %206, ptr %15, align 8
  %207 = load i64, ptr %15, align 8
  %208 = load ptr, ptr %5, align 8
  %209 = getelementptr inbounds %struct.stbds_hash_index, ptr %208, i32 0, i32 1
  %210 = load i64, ptr %209, align 8
  %211 = load ptr, ptr %5, align 8
  %212 = getelementptr inbounds %struct.stbds_hash_index, ptr %211, i32 0, i32 8
  %213 = load i64, ptr %212, align 8
  %214 = call i64 @stbds_probe_position(i64 noundef %207, i64 noundef %210, i64 noundef %213)
  store i64 %214, ptr %16, align 8
  store i64 8, ptr %17, align 8
  br label %215

215:                                              ; preds = %286, %201
  %216 = load ptr, ptr %5, align 8
  %217 = getelementptr inbounds %struct.stbds_hash_index, ptr %216, i32 0, i32 10
  %218 = load ptr, ptr %217, align 8
  %219 = load i64, ptr %16, align 8
  %220 = lshr i64 %219, 3
  %221 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %218, i64 %220
  store ptr %221, ptr %20, align 8
  %222 = load i64, ptr %16, align 8
  %223 = and i64 %222, 7
  store i64 %223, ptr %19, align 8
  br label %224

224:                                              ; preds = %250, %215
  %225 = load i64, ptr %19, align 8
  %226 = icmp ult i64 %225, 8
  br i1 %226, label %227, label %253

227:                                              ; preds = %224
  %228 = load ptr, ptr %20, align 8
  %229 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %228, i32 0, i32 0
  %230 = load i64, ptr %19, align 8
  %231 = getelementptr inbounds [8 x i64], ptr %229, i64 0, i64 %230
  %232 = load i64, ptr %231, align 8
  %233 = icmp eq i64 %232, 0
  br i1 %233, label %234, label %249

234:                                              ; preds = %227
  %235 = load i64, ptr %15, align 8
  %236 = load ptr, ptr %20, align 8
  %237 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %236, i32 0, i32 0
  %238 = load i64, ptr %19, align 8
  %239 = getelementptr inbounds [8 x i64], ptr %237, i64 0, i64 %238
  store i64 %235, ptr %239, align 8
  %240 = load ptr, ptr %14, align 8
  %241 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %240, i32 0, i32 1
  %242 = load i64, ptr %13, align 8
  %243 = getelementptr inbounds [8 x i64], ptr %241, i64 0, i64 %242
  %244 = load i64, ptr %243, align 8
  %245 = load ptr, ptr %20, align 8
  %246 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %245, i32 0, i32 1
  %247 = load i64, ptr %19, align 8
  %248 = getelementptr inbounds [8 x i64], ptr %246, i64 0, i64 %247
  store i64 %244, ptr %248, align 8
  br label %299

249:                                              ; preds = %227
  br label %250

250:                                              ; preds = %249
  %251 = load i64, ptr %19, align 8
  %252 = add i64 %251, 1
  store i64 %252, ptr %19, align 8
  br label %224, !llvm.loop !21

253:                                              ; preds = %224
  %254 = load i64, ptr %16, align 8
  %255 = and i64 %254, 7
  store i64 %255, ptr %18, align 8
  store i64 0, ptr %19, align 8
  br label %256

256:                                              ; preds = %283, %253
  %257 = load i64, ptr %19, align 8
  %258 = load i64, ptr %18, align 8
  %259 = icmp ult i64 %257, %258
  br i1 %259, label %260, label %286

260:                                              ; preds = %256
  %261 = load ptr, ptr %20, align 8
  %262 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %261, i32 0, i32 0
  %263 = load i64, ptr %19, align 8
  %264 = getelementptr inbounds [8 x i64], ptr %262, i64 0, i64 %263
  %265 = load i64, ptr %264, align 8
  %266 = icmp eq i64 %265, 0
  br i1 %266, label %267, label %282

267:                                              ; preds = %260
  %268 = load i64, ptr %15, align 8
  %269 = load ptr, ptr %20, align 8
  %270 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %269, i32 0, i32 0
  %271 = load i64, ptr %19, align 8
  %272 = getelementptr inbounds [8 x i64], ptr %270, i64 0, i64 %271
  store i64 %268, ptr %272, align 8
  %273 = load ptr, ptr %14, align 8
  %274 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %273, i32 0, i32 1
  %275 = load i64, ptr %13, align 8
  %276 = getelementptr inbounds [8 x i64], ptr %274, i64 0, i64 %275
  %277 = load i64, ptr %276, align 8
  %278 = load ptr, ptr %20, align 8
  %279 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %278, i32 0, i32 1
  %280 = load i64, ptr %19, align 8
  %281 = getelementptr inbounds [8 x i64], ptr %279, i64 0, i64 %280
  store i64 %277, ptr %281, align 8
  br label %299

282:                                              ; preds = %260
  br label %283

283:                                              ; preds = %282
  %284 = load i64, ptr %19, align 8
  %285 = add i64 %284, 1
  store i64 %285, ptr %19, align 8
  br label %256, !llvm.loop !22

286:                                              ; preds = %256
  %287 = load i64, ptr %17, align 8
  %288 = load i64, ptr %16, align 8
  %289 = add i64 %288, %287
  store i64 %289, ptr %16, align 8
  %290 = load i64, ptr %17, align 8
  %291 = add i64 %290, 8
  store i64 %291, ptr %17, align 8
  %292 = load ptr, ptr %5, align 8
  %293 = getelementptr inbounds %struct.stbds_hash_index, ptr %292, i32 0, i32 1
  %294 = load i64, ptr %293, align 8
  %295 = sub i64 %294, 1
  %296 = load i64, ptr %16, align 8
  %297 = and i64 %296, %295
  store i64 %297, ptr %16, align 8
  br label %215

298:                                              ; preds = %194
  br label %299

299:                                              ; preds = %298, %267, %234
  br label %300

300:                                              ; preds = %299
  %301 = load i64, ptr %13, align 8
  %302 = add i64 %301, 1
  store i64 %302, ptr %13, align 8
  br label %191, !llvm.loop !23

303:                                              ; preds = %191
  br label %304

304:                                              ; preds = %303
  %305 = load i64, ptr %12, align 8
  %306 = add i64 %305, 1
  store i64 %306, ptr %12, align 8
  br label %178, !llvm.loop !24

307:                                              ; preds = %178
  br label %308

308:                                              ; preds = %307, %169
  %309 = load ptr, ptr %5, align 8
  ret ptr %309
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define internal i64 @stbds_probe_position(i64 noundef %0, i64 noundef %1, i64 noundef %2) #0 {
  %4 = alloca i64, align 8
  %5 = alloca i64, align 8
  %6 = alloca i64, align 8
  %7 = alloca i64, align 8
  store i64 %0, ptr %4, align 8
  store i64 %1, ptr %5, align 8
  store i64 %2, ptr %6, align 8
  %8 = load i64, ptr %4, align 8
  %9 = load i64, ptr %5, align 8
  %10 = sub i64 %9, 1
  %11 = and i64 %8, %10
  store i64 %11, ptr %7, align 8
  %12 = load i64, ptr %7, align 8
  ret i64 %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define internal i32 @stbds_is_key_equal(ptr noundef %0, i64 noundef %1, ptr noundef %2, i64 noundef %3, i64 noundef %4, i32 noundef %5, i64 noundef %6) #0 {
  %8 = alloca i32, align 4
  %9 = alloca ptr, align 8
  %10 = alloca i64, align 8
  %11 = alloca ptr, align 8
  %12 = alloca i64, align 8
  %13 = alloca i64, align 8
  %14 = alloca i32, align 4
  %15 = alloca i64, align 8
  store ptr %0, ptr %9, align 8
  store i64 %1, ptr %10, align 8
  store ptr %2, ptr %11, align 8
  store i64 %3, ptr %12, align 8
  store i64 %4, ptr %13, align 8
  store i32 %5, ptr %14, align 4
  store i64 %6, ptr %15, align 8
  %16 = load i32, ptr %14, align 4
  %17 = icmp sge i32 %16, 1
  br i1 %17, label %18, label %31

18:                                               ; preds = %7
  %19 = load ptr, ptr %11, align 8
  %20 = load ptr, ptr %9, align 8
  %21 = load i64, ptr %10, align 8
  %22 = load i64, ptr %15, align 8
  %23 = mul i64 %21, %22
  %24 = getelementptr inbounds i8, ptr %20, i64 %23
  %25 = load i64, ptr %13, align 8
  %26 = getelementptr inbounds i8, ptr %24, i64 %25
  %27 = load ptr, ptr %26, align 8
  %28 = call i32 @strcmp(ptr noundef %19, ptr noundef %27) #8
  %29 = icmp eq i32 0, %28
  %30 = zext i1 %29 to i32
  store i32 %30, ptr %8, align 4
  br label %44

31:                                               ; preds = %7
  %32 = load ptr, ptr %11, align 8
  %33 = load ptr, ptr %9, align 8
  %34 = load i64, ptr %10, align 8
  %35 = load i64, ptr %15, align 8
  %36 = mul i64 %34, %35
  %37 = getelementptr inbounds i8, ptr %33, i64 %36
  %38 = load i64, ptr %13, align 8
  %39 = getelementptr inbounds i8, ptr %37, i64 %38
  %40 = load i64, ptr %12, align 8
  %41 = call i32 @memcmp(ptr noundef %32, ptr noundef %39, i64 noundef %40)
  %42 = icmp eq i32 0, %41
  %43 = zext i1 %42 to i32
  store i32 %43, ptr %8, align 4
  br label %44

44:                                               ; preds = %31, %18
  %45 = load i32, ptr %8, align 4
  ret i32 %45
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define internal ptr @stbds_strdup(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i64, align 8
  %4 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %5 = load ptr, ptr %2, align 8
  %6 = call i64 @strlen(ptr noundef %5) #8
  %7 = add i64 %6, 1
  store i64 %7, ptr %3, align 8
  %8 = load i64, ptr %3, align 8
  %9 = call ptr @realloc(ptr noundef null, i64 noundef %8) #7
  store ptr %9, ptr %4, align 8
  %10 = load ptr, ptr %4, align 8
  %11 = load ptr, ptr %2, align 8
  %12 = load i64, ptr %3, align 8
  %13 = load ptr, ptr %4, align 8
  %14 = call i64 @llvm.objectsize.i64.p0(ptr %13, i1 false, i1 true, i1 false)
  %15 = call ptr @__memmove_chk(ptr noundef %10, ptr noundef %11, i64 noundef %12, i64 noundef %14) #8
  %16 = load ptr, ptr %4, align 8
  ret ptr %16
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define ptr @stbds_stralloc(ptr noundef %0, ptr noundef %1) #0 {
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca i64, align 8
  %8 = alloca i64, align 8
  %9 = alloca ptr, align 8
  %10 = alloca ptr, align 8
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  %11 = load ptr, ptr %5, align 8
  %12 = call i64 @strlen(ptr noundef %11) #8
  %13 = add i64 %12, 1
  store i64 %13, ptr %7, align 8
  %14 = load i64, ptr %7, align 8
  %15 = load ptr, ptr %4, align 8
  %16 = getelementptr inbounds %struct.stbds_string_arena, ptr %15, i32 0, i32 1
  %17 = load i64, ptr %16, align 8
  %18 = icmp ugt i64 %14, %17
  br i1 %18, label %19, label %97

19:                                               ; preds = %2
  %20 = load ptr, ptr %4, align 8
  %21 = getelementptr inbounds %struct.stbds_string_arena, ptr %20, i32 0, i32 2
  %22 = load i8, ptr %21, align 8
  %23 = zext i8 %22 to i64
  store i64 %23, ptr %8, align 8
  %24 = load i64, ptr %8, align 8
  %25 = lshr i64 %24, 1
  %26 = shl i64 512, %25
  store i64 %26, ptr %8, align 8
  %27 = load i64, ptr %8, align 8
  %28 = icmp ult i64 %27, 1048576
  br i1 %28, label %29, label %34

29:                                               ; preds = %19
  %30 = load ptr, ptr %4, align 8
  %31 = getelementptr inbounds %struct.stbds_string_arena, ptr %30, i32 0, i32 2
  %32 = load i8, ptr %31, align 8
  %33 = add i8 %32, 1
  store i8 %33, ptr %31, align 8
  br label %34

34:                                               ; preds = %29, %19
  %35 = load i64, ptr %7, align 8
  %36 = load i64, ptr %8, align 8
  %37 = icmp ugt i64 %35, %36
  br i1 %37, label %38, label %81

38:                                               ; preds = %34
  %39 = load i64, ptr %7, align 8
  %40 = add i64 8, %39
  %41 = call ptr @realloc(ptr noundef null, i64 noundef %40) #7
  store ptr %41, ptr %9, align 8
  %42 = load ptr, ptr %9, align 8
  %43 = getelementptr inbounds %struct.stbds_string_block, ptr %42, i32 0, i32 1
  %44 = getelementptr inbounds [8 x i8], ptr %43, i64 0, i64 0
  %45 = load ptr, ptr %5, align 8
  %46 = load i64, ptr %7, align 8
  %47 = load ptr, ptr %9, align 8
  %48 = getelementptr inbounds %struct.stbds_string_block, ptr %47, i32 0, i32 1
  %49 = getelementptr inbounds [8 x i8], ptr %48, i64 0, i64 0
  %50 = call i64 @llvm.objectsize.i64.p0(ptr %49, i1 false, i1 true, i1 false)
  %51 = call ptr @__memmove_chk(ptr noundef %44, ptr noundef %45, i64 noundef %46, i64 noundef %50) #8
  %52 = load ptr, ptr %4, align 8
  %53 = getelementptr inbounds %struct.stbds_string_arena, ptr %52, i32 0, i32 0
  %54 = load ptr, ptr %53, align 8
  %55 = icmp ne ptr %54, null
  br i1 %55, label %56, label %69

56:                                               ; preds = %38
  %57 = load ptr, ptr %4, align 8
  %58 = getelementptr inbounds %struct.stbds_string_arena, ptr %57, i32 0, i32 0
  %59 = load ptr, ptr %58, align 8
  %60 = getelementptr inbounds %struct.stbds_string_block, ptr %59, i32 0, i32 0
  %61 = load ptr, ptr %60, align 8
  %62 = load ptr, ptr %9, align 8
  %63 = getelementptr inbounds %struct.stbds_string_block, ptr %62, i32 0, i32 0
  store ptr %61, ptr %63, align 8
  %64 = load ptr, ptr %9, align 8
  %65 = load ptr, ptr %4, align 8
  %66 = getelementptr inbounds %struct.stbds_string_arena, ptr %65, i32 0, i32 0
  %67 = load ptr, ptr %66, align 8
  %68 = getelementptr inbounds %struct.stbds_string_block, ptr %67, i32 0, i32 0
  store ptr %64, ptr %68, align 8
  br label %77

69:                                               ; preds = %38
  %70 = load ptr, ptr %9, align 8
  %71 = getelementptr inbounds %struct.stbds_string_block, ptr %70, i32 0, i32 0
  store ptr null, ptr %71, align 8
  %72 = load ptr, ptr %9, align 8
  %73 = load ptr, ptr %4, align 8
  %74 = getelementptr inbounds %struct.stbds_string_arena, ptr %73, i32 0, i32 0
  store ptr %72, ptr %74, align 8
  %75 = load ptr, ptr %4, align 8
  %76 = getelementptr inbounds %struct.stbds_string_arena, ptr %75, i32 0, i32 1
  store i64 0, ptr %76, align 8
  br label %77

77:                                               ; preds = %69, %56
  %78 = load ptr, ptr %9, align 8
  %79 = getelementptr inbounds %struct.stbds_string_block, ptr %78, i32 0, i32 1
  %80 = getelementptr inbounds [8 x i8], ptr %79, i64 0, i64 0
  store ptr %80, ptr %3, align 8
  br label %122

81:                                               ; preds = %34
  %82 = load i64, ptr %8, align 8
  %83 = add i64 8, %82
  %84 = call ptr @realloc(ptr noundef null, i64 noundef %83) #7
  store ptr %84, ptr %10, align 8
  %85 = load ptr, ptr %4, align 8
  %86 = getelementptr inbounds %struct.stbds_string_arena, ptr %85, i32 0, i32 0
  %87 = load ptr, ptr %86, align 8
  %88 = load ptr, ptr %10, align 8
  %89 = getelementptr inbounds %struct.stbds_string_block, ptr %88, i32 0, i32 0
  store ptr %87, ptr %89, align 8
  %90 = load ptr, ptr %10, align 8
  %91 = load ptr, ptr %4, align 8
  %92 = getelementptr inbounds %struct.stbds_string_arena, ptr %91, i32 0, i32 0
  store ptr %90, ptr %92, align 8
  %93 = load i64, ptr %8, align 8
  %94 = load ptr, ptr %4, align 8
  %95 = getelementptr inbounds %struct.stbds_string_arena, ptr %94, i32 0, i32 1
  store i64 %93, ptr %95, align 8
  br label %96

96:                                               ; preds = %81
  br label %97

97:                                               ; preds = %96, %2
  %98 = load ptr, ptr %4, align 8
  %99 = getelementptr inbounds %struct.stbds_string_arena, ptr %98, i32 0, i32 0
  %100 = load ptr, ptr %99, align 8
  %101 = getelementptr inbounds %struct.stbds_string_block, ptr %100, i32 0, i32 1
  %102 = getelementptr inbounds [8 x i8], ptr %101, i64 0, i64 0
  %103 = load ptr, ptr %4, align 8
  %104 = getelementptr inbounds %struct.stbds_string_arena, ptr %103, i32 0, i32 1
  %105 = load i64, ptr %104, align 8
  %106 = getelementptr inbounds i8, ptr %102, i64 %105
  %107 = load i64, ptr %7, align 8
  %108 = sub i64 0, %107
  %109 = getelementptr inbounds i8, ptr %106, i64 %108
  store ptr %109, ptr %6, align 8
  %110 = load i64, ptr %7, align 8
  %111 = load ptr, ptr %4, align 8
  %112 = getelementptr inbounds %struct.stbds_string_arena, ptr %111, i32 0, i32 1
  %113 = load i64, ptr %112, align 8
  %114 = sub i64 %113, %110
  store i64 %114, ptr %112, align 8
  %115 = load ptr, ptr %6, align 8
  %116 = load ptr, ptr %5, align 8
  %117 = load i64, ptr %7, align 8
  %118 = load ptr, ptr %6, align 8
  %119 = call i64 @llvm.objectsize.i64.p0(ptr %118, i1 false, i1 true, i1 false)
  %120 = call ptr @__memmove_chk(ptr noundef %115, ptr noundef %116, i64 noundef %117, i64 noundef %119) #8
  %121 = load ptr, ptr %6, align 8
  store ptr %121, ptr %3, align 8
  br label %122

122:                                              ; preds = %97, %77
  %123 = load ptr, ptr %3, align 8
  ret ptr %123
}

; Function Attrs: nounwind
declare ptr @__memcpy_chk(ptr noundef, ptr noundef, i64 noundef, i64 noundef) #4

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define ptr @stbds_shmode_func(i64 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i64, align 8
  %4 = alloca i32, align 4
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  store i64 %0, ptr %3, align 8
  store i32 %1, ptr %4, align 4
  %7 = load i64, ptr %3, align 8
  %8 = call ptr @stbds_arrgrowf(ptr noundef null, i64 noundef %7, i64 noundef 0, i64 noundef 1)
  store ptr %8, ptr %5, align 8
  %9 = load ptr, ptr %5, align 8
  %10 = load i64, ptr %3, align 8
  %11 = load ptr, ptr %5, align 8
  %12 = call i64 @llvm.objectsize.i64.p0(ptr %11, i1 false, i1 true, i1 false)
  %13 = call ptr @__memset_chk(ptr noundef %9, i32 noundef 0, i64 noundef %10, i64 noundef %12) #8
  %14 = load ptr, ptr %5, align 8
  %15 = getelementptr inbounds %struct.stbds_array_header, ptr %14, i64 -1
  %16 = getelementptr inbounds %struct.stbds_array_header, ptr %15, i32 0, i32 0
  store i64 1, ptr %16, align 8
  %17 = call ptr @stbds_make_hash_index(i64 noundef 8, ptr noundef null)
  store ptr %17, ptr %6, align 8
  %18 = load ptr, ptr %5, align 8
  %19 = getelementptr inbounds %struct.stbds_array_header, ptr %18, i64 -1
  %20 = getelementptr inbounds %struct.stbds_array_header, ptr %19, i32 0, i32 2
  store ptr %17, ptr %20, align 8
  %21 = load i32, ptr %4, align 4
  %22 = trunc i32 %21 to i8
  %23 = load ptr, ptr %6, align 8
  %24 = getelementptr inbounds %struct.stbds_hash_index, ptr %23, i32 0, i32 9
  %25 = getelementptr inbounds %struct.stbds_string_arena, ptr %24, i32 0, i32 3
  store i8 %22, ptr %25, align 1
  %26 = load ptr, ptr %5, align 8
  %27 = load i64, ptr %3, align 8
  %28 = getelementptr inbounds i8, ptr %26, i64 %27
  ret ptr %28
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define ptr @stbds_hmdel_key(ptr noundef %0, i64 noundef %1, ptr noundef %2, i64 noundef %3, i64 noundef %4, i32 noundef %5) #0 {
  %7 = alloca ptr, align 8
  %8 = alloca ptr, align 8
  %9 = alloca i64, align 8
  %10 = alloca ptr, align 8
  %11 = alloca i64, align 8
  %12 = alloca i64, align 8
  %13 = alloca i32, align 4
  %14 = alloca ptr, align 8
  %15 = alloca ptr, align 8
  %16 = alloca i64, align 8
  %17 = alloca ptr, align 8
  %18 = alloca i32, align 4
  %19 = alloca i64, align 8
  %20 = alloca i64, align 8
  store ptr %0, ptr %8, align 8
  store i64 %1, ptr %9, align 8
  store ptr %2, ptr %10, align 8
  store i64 %3, ptr %11, align 8
  store i64 %4, ptr %12, align 8
  store i32 %5, ptr %13, align 4
  %21 = load ptr, ptr %8, align 8
  %22 = icmp eq ptr %21, null
  br i1 %22, label %23, label %24

23:                                               ; preds = %6
  store ptr null, ptr %7, align 8
  br label %237

24:                                               ; preds = %6
  %25 = load ptr, ptr %8, align 8
  %26 = load i64, ptr %9, align 8
  %27 = sub i64 0, %26
  %28 = getelementptr inbounds i8, ptr %25, i64 %27
  store ptr %28, ptr %15, align 8
  %29 = load ptr, ptr %15, align 8
  %30 = getelementptr inbounds %struct.stbds_array_header, ptr %29, i64 -1
  %31 = getelementptr inbounds %struct.stbds_array_header, ptr %30, i32 0, i32 2
  %32 = load ptr, ptr %31, align 8
  store ptr %32, ptr %14, align 8
  %33 = load ptr, ptr %15, align 8
  %34 = getelementptr inbounds %struct.stbds_array_header, ptr %33, i64 -1
  %35 = getelementptr inbounds %struct.stbds_array_header, ptr %34, i32 0, i32 3
  store i64 0, ptr %35, align 8
  %36 = load ptr, ptr %14, align 8
  %37 = icmp eq ptr %36, null
  br i1 %37, label %38, label %40

38:                                               ; preds = %24
  %39 = load ptr, ptr %8, align 8
  store ptr %39, ptr %7, align 8
  br label %237

40:                                               ; preds = %24
  %41 = load ptr, ptr %8, align 8
  %42 = load i64, ptr %9, align 8
  %43 = load ptr, ptr %10, align 8
  %44 = load i64, ptr %11, align 8
  %45 = load i64, ptr %12, align 8
  %46 = load i32, ptr %13, align 4
  %47 = call i64 @stbds_hm_find_slot(ptr noundef %41, i64 noundef %42, ptr noundef %43, i64 noundef %44, i64 noundef %45, i32 noundef %46)
  store i64 %47, ptr %16, align 8
  %48 = load i64, ptr %16, align 8
  %49 = icmp slt i64 %48, 0
  br i1 %49, label %50, label %52

50:                                               ; preds = %40
  %51 = load ptr, ptr %8, align 8
  store ptr %51, ptr %7, align 8
  br label %237

52:                                               ; preds = %40
  %53 = load ptr, ptr %14, align 8
  %54 = getelementptr inbounds %struct.stbds_hash_index, ptr %53, i32 0, i32 10
  %55 = load ptr, ptr %54, align 8
  %56 = load i64, ptr %16, align 8
  %57 = ashr i64 %56, 3
  %58 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %55, i64 %57
  store ptr %58, ptr %17, align 8
  %59 = load i64, ptr %16, align 8
  %60 = and i64 %59, 7
  %61 = trunc i64 %60 to i32
  store i32 %61, ptr %18, align 4
  %62 = load ptr, ptr %17, align 8
  %63 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %62, i32 0, i32 1
  %64 = load i32, ptr %18, align 4
  %65 = sext i32 %64 to i64
  %66 = getelementptr inbounds [8 x i64], ptr %63, i64 0, i64 %65
  %67 = load i64, ptr %66, align 8
  store i64 %67, ptr %19, align 8
  %68 = load ptr, ptr %15, align 8
  %69 = icmp ne ptr %68, null
  br i1 %69, label %70, label %75

70:                                               ; preds = %52
  %71 = load ptr, ptr %15, align 8
  %72 = getelementptr inbounds %struct.stbds_array_header, ptr %71, i64 -1
  %73 = getelementptr inbounds %struct.stbds_array_header, ptr %72, i32 0, i32 0
  %74 = load i64, ptr %73, align 8
  br label %76

75:                                               ; preds = %52
  br label %76

76:                                               ; preds = %75, %70
  %77 = phi i64 [ %74, %70 ], [ 0, %75 ]
  %78 = sub nsw i64 %77, 1
  %79 = sub nsw i64 %78, 1
  store i64 %79, ptr %20, align 8
  %80 = load ptr, ptr %14, align 8
  %81 = getelementptr inbounds %struct.stbds_hash_index, ptr %80, i32 0, i32 2
  %82 = load i64, ptr %81, align 8
  %83 = add i64 %82, -1
  store i64 %83, ptr %81, align 8
  %84 = load ptr, ptr %14, align 8
  %85 = getelementptr inbounds %struct.stbds_hash_index, ptr %84, i32 0, i32 5
  %86 = load i64, ptr %85, align 8
  %87 = add i64 %86, 1
  store i64 %87, ptr %85, align 8
  %88 = load ptr, ptr %15, align 8
  %89 = getelementptr inbounds %struct.stbds_array_header, ptr %88, i64 -1
  %90 = getelementptr inbounds %struct.stbds_array_header, ptr %89, i32 0, i32 3
  store i64 1, ptr %90, align 8
  %91 = load ptr, ptr %17, align 8
  %92 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %91, i32 0, i32 0
  %93 = load i32, ptr %18, align 4
  %94 = sext i32 %93 to i64
  %95 = getelementptr inbounds [8 x i64], ptr %92, i64 0, i64 %94
  store i64 1, ptr %95, align 8
  %96 = load ptr, ptr %17, align 8
  %97 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %96, i32 0, i32 1
  %98 = load i32, ptr %18, align 4
  %99 = sext i32 %98 to i64
  %100 = getelementptr inbounds [8 x i64], ptr %97, i64 0, i64 %99
  store i64 -2, ptr %100, align 8
  %101 = load i32, ptr %13, align 4
  %102 = icmp eq i32 %101, 1
  br i1 %102, label %103, label %117

103:                                              ; preds = %76
  %104 = load ptr, ptr %14, align 8
  %105 = getelementptr inbounds %struct.stbds_hash_index, ptr %104, i32 0, i32 9
  %106 = getelementptr inbounds %struct.stbds_string_arena, ptr %105, i32 0, i32 3
  %107 = load i8, ptr %106, align 1
  %108 = zext i8 %107 to i32
  %109 = icmp eq i32 %108, 2
  br i1 %109, label %110, label %117

110:                                              ; preds = %103
  %111 = load ptr, ptr %8, align 8
  %112 = load i64, ptr %9, align 8
  %113 = load i64, ptr %19, align 8
  %114 = mul i64 %112, %113
  %115 = getelementptr inbounds i8, ptr %111, i64 %114
  %116 = load ptr, ptr %115, align 8
  call void @free(ptr noundef %116)
  br label %117

117:                                              ; preds = %110, %103, %76
  %118 = load i64, ptr %19, align 8
  %119 = load i64, ptr %20, align 8
  %120 = icmp ne i64 %118, %119
  br i1 %120, label %121, label %187

121:                                              ; preds = %117
  %122 = load ptr, ptr %8, align 8
  %123 = load i64, ptr %9, align 8
  %124 = load i64, ptr %19, align 8
  %125 = mul i64 %123, %124
  %126 = getelementptr inbounds i8, ptr %122, i64 %125
  %127 = load ptr, ptr %8, align 8
  %128 = load i64, ptr %9, align 8
  %129 = load i64, ptr %20, align 8
  %130 = mul i64 %128, %129
  %131 = getelementptr inbounds i8, ptr %127, i64 %130
  %132 = load i64, ptr %9, align 8
  %133 = load ptr, ptr %8, align 8
  %134 = load i64, ptr %9, align 8
  %135 = load i64, ptr %19, align 8
  %136 = mul i64 %134, %135
  %137 = getelementptr inbounds i8, ptr %133, i64 %136
  %138 = call i64 @llvm.objectsize.i64.p0(ptr %137, i1 false, i1 true, i1 false)
  %139 = call ptr @__memmove_chk(ptr noundef %126, ptr noundef %131, i64 noundef %132, i64 noundef %138) #8
  %140 = load i32, ptr %13, align 4
  %141 = icmp eq i32 %140, 1
  br i1 %141, label %142, label %157

142:                                              ; preds = %121
  %143 = load ptr, ptr %8, align 8
  %144 = load i64, ptr %9, align 8
  %145 = load ptr, ptr %8, align 8
  %146 = load i64, ptr %9, align 8
  %147 = load i64, ptr %19, align 8
  %148 = mul i64 %146, %147
  %149 = getelementptr inbounds i8, ptr %145, i64 %148
  %150 = load i64, ptr %12, align 8
  %151 = getelementptr inbounds i8, ptr %149, i64 %150
  %152 = load ptr, ptr %151, align 8
  %153 = load i64, ptr %11, align 8
  %154 = load i64, ptr %12, align 8
  %155 = load i32, ptr %13, align 4
  %156 = call i64 @stbds_hm_find_slot(ptr noundef %143, i64 noundef %144, ptr noundef %152, i64 noundef %153, i64 noundef %154, i32 noundef %155)
  store i64 %156, ptr %16, align 8
  br label %171

157:                                              ; preds = %121
  %158 = load ptr, ptr %8, align 8
  %159 = load i64, ptr %9, align 8
  %160 = load ptr, ptr %8, align 8
  %161 = load i64, ptr %9, align 8
  %162 = load i64, ptr %19, align 8
  %163 = mul i64 %161, %162
  %164 = getelementptr inbounds i8, ptr %160, i64 %163
  %165 = load i64, ptr %12, align 8
  %166 = getelementptr inbounds i8, ptr %164, i64 %165
  %167 = load i64, ptr %11, align 8
  %168 = load i64, ptr %12, align 8
  %169 = load i32, ptr %13, align 4
  %170 = call i64 @stbds_hm_find_slot(ptr noundef %158, i64 noundef %159, ptr noundef %166, i64 noundef %167, i64 noundef %168, i32 noundef %169)
  store i64 %170, ptr %16, align 8
  br label %171

171:                                              ; preds = %157, %142
  %172 = load ptr, ptr %14, align 8
  %173 = getelementptr inbounds %struct.stbds_hash_index, ptr %172, i32 0, i32 10
  %174 = load ptr, ptr %173, align 8
  %175 = load i64, ptr %16, align 8
  %176 = ashr i64 %175, 3
  %177 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %174, i64 %176
  store ptr %177, ptr %17, align 8
  %178 = load i64, ptr %16, align 8
  %179 = and i64 %178, 7
  %180 = trunc i64 %179 to i32
  store i32 %180, ptr %18, align 4
  %181 = load i64, ptr %19, align 8
  %182 = load ptr, ptr %17, align 8
  %183 = getelementptr inbounds %struct.stbds_hash_bucket, ptr %182, i32 0, i32 1
  %184 = load i32, ptr %18, align 4
  %185 = sext i32 %184 to i64
  %186 = getelementptr inbounds [8 x i64], ptr %183, i64 0, i64 %185
  store i64 %181, ptr %186, align 8
  br label %187

187:                                              ; preds = %171, %117
  %188 = load ptr, ptr %15, align 8
  %189 = getelementptr inbounds %struct.stbds_array_header, ptr %188, i64 -1
  %190 = getelementptr inbounds %struct.stbds_array_header, ptr %189, i32 0, i32 0
  %191 = load i64, ptr %190, align 8
  %192 = sub i64 %191, 1
  store i64 %192, ptr %190, align 8
  %193 = load ptr, ptr %14, align 8
  %194 = getelementptr inbounds %struct.stbds_hash_index, ptr %193, i32 0, i32 2
  %195 = load i64, ptr %194, align 8
  %196 = load ptr, ptr %14, align 8
  %197 = getelementptr inbounds %struct.stbds_hash_index, ptr %196, i32 0, i32 4
  %198 = load i64, ptr %197, align 8
  %199 = icmp ult i64 %195, %198
  br i1 %199, label %200, label %216

200:                                              ; preds = %187
  %201 = load ptr, ptr %14, align 8
  %202 = getelementptr inbounds %struct.stbds_hash_index, ptr %201, i32 0, i32 1
  %203 = load i64, ptr %202, align 8
  %204 = icmp ugt i64 %203, 8
  br i1 %204, label %205, label %216

205:                                              ; preds = %200
  %206 = load ptr, ptr %14, align 8
  %207 = getelementptr inbounds %struct.stbds_hash_index, ptr %206, i32 0, i32 1
  %208 = load i64, ptr %207, align 8
  %209 = lshr i64 %208, 1
  %210 = load ptr, ptr %14, align 8
  %211 = call ptr @stbds_make_hash_index(i64 noundef %209, ptr noundef %210)
  %212 = load ptr, ptr %15, align 8
  %213 = getelementptr inbounds %struct.stbds_array_header, ptr %212, i64 -1
  %214 = getelementptr inbounds %struct.stbds_array_header, ptr %213, i32 0, i32 2
  store ptr %211, ptr %214, align 8
  %215 = load ptr, ptr %14, align 8
  call void @free(ptr noundef %215)
  br label %235

216:                                              ; preds = %200, %187
  %217 = load ptr, ptr %14, align 8
  %218 = getelementptr inbounds %struct.stbds_hash_index, ptr %217, i32 0, i32 5
  %219 = load i64, ptr %218, align 8
  %220 = load ptr, ptr %14, align 8
  %221 = getelementptr inbounds %struct.stbds_hash_index, ptr %220, i32 0, i32 6
  %222 = load i64, ptr %221, align 8
  %223 = icmp ugt i64 %219, %222
  br i1 %223, label %224, label %234

224:                                              ; preds = %216
  %225 = load ptr, ptr %14, align 8
  %226 = getelementptr inbounds %struct.stbds_hash_index, ptr %225, i32 0, i32 1
  %227 = load i64, ptr %226, align 8
  %228 = load ptr, ptr %14, align 8
  %229 = call ptr @stbds_make_hash_index(i64 noundef %227, ptr noundef %228)
  %230 = load ptr, ptr %15, align 8
  %231 = getelementptr inbounds %struct.stbds_array_header, ptr %230, i64 -1
  %232 = getelementptr inbounds %struct.stbds_array_header, ptr %231, i32 0, i32 2
  store ptr %229, ptr %232, align 8
  %233 = load ptr, ptr %14, align 8
  call void @free(ptr noundef %233)
  br label %234

234:                                              ; preds = %224, %216
  br label %235

235:                                              ; preds = %234, %205
  %236 = load ptr, ptr %8, align 8
  store ptr %236, ptr %7, align 8
  br label %237

237:                                              ; preds = %235, %50, %38, %23
  %238 = load ptr, ptr %7, align 8
  ret ptr %238
}

; Function Attrs: nounwind
declare ptr @__memmove_chk(ptr noundef, ptr noundef, i64 noundef, i64 noundef) #4

; Function Attrs: nounwind
declare i64 @strlen(ptr noundef) #4

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @Map_insert_Map_Any_Any(ptr noundef %0, ptr noundef %1, ptr noundef %2) #0 {
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca [1 x ptr], align 8
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  store ptr %2, ptr %6, align 8
  %8 = load ptr, ptr %4, align 8
  %9 = load ptr, ptr %8, align 8
  %10 = load ptr, ptr %5, align 8
  store ptr %10, ptr %7, align 8
  %11 = getelementptr inbounds [1 x ptr], ptr %7, i64 0, i64 0
  %12 = call ptr @stbds_hmput_key(ptr noundef %9, i64 noundef 16, ptr noundef %11, i64 noundef 8, i32 noundef 0)
  %13 = load ptr, ptr %4, align 8
  store ptr %12, ptr %13, align 8
  %14 = load ptr, ptr %5, align 8
  %15 = load ptr, ptr %4, align 8
  %16 = load ptr, ptr %15, align 8
  %17 = load ptr, ptr %4, align 8
  %18 = load ptr, ptr %17, align 8
  %19 = getelementptr inbounds %struct.Map, ptr %18, i64 -1
  %20 = getelementptr inbounds %struct.stbds_array_header, ptr %19, i64 -1
  %21 = getelementptr inbounds %struct.stbds_array_header, ptr %20, i32 0, i32 3
  %22 = load i64, ptr %21, align 8
  %23 = getelementptr inbounds %struct.Map, ptr %16, i64 %22
  %24 = getelementptr inbounds %struct.Map, ptr %23, i32 0, i32 0
  store ptr %14, ptr %24, align 8
  %25 = load ptr, ptr %6, align 8
  %26 = load ptr, ptr %4, align 8
  %27 = load ptr, ptr %26, align 8
  %28 = load ptr, ptr %4, align 8
  %29 = load ptr, ptr %28, align 8
  %30 = getelementptr inbounds %struct.Map, ptr %29, i64 -1
  %31 = getelementptr inbounds %struct.stbds_array_header, ptr %30, i64 -1
  %32 = getelementptr inbounds %struct.stbds_array_header, ptr %31, i32 0, i32 3
  %33 = load i64, ptr %32, align 8
  %34 = getelementptr inbounds %struct.Map, ptr %27, i64 %33
  %35 = getelementptr inbounds %struct.Map, ptr %34, i32 0, i32 1
  store ptr %25, ptr %35, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define ptr @Map_get_Map_Any(ptr noundef %0, ptr noundef %1) #0 {
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca [1 x ptr], align 8
  store ptr %0, ptr %3, align 8
  store ptr %1, ptr %4, align 8
  %6 = load ptr, ptr %3, align 8
  %7 = load ptr, ptr %6, align 8
  %8 = load ptr, ptr %4, align 8
  store ptr %8, ptr %5, align 8
  %9 = getelementptr inbounds [1 x ptr], ptr %5, i64 0, i64 0
  %10 = call ptr @stbds_hmget_key(ptr noundef %7, i64 noundef 16, ptr noundef %9, i64 noundef 8, i32 noundef 0)
  %11 = load ptr, ptr %3, align 8
  store ptr %10, ptr %11, align 8
  %12 = load ptr, ptr %3, align 8
  %13 = load ptr, ptr %12, align 8
  %14 = getelementptr inbounds %struct.Map, ptr %13, i64 -1
  %15 = getelementptr inbounds %struct.stbds_array_header, ptr %14, i64 -1
  %16 = getelementptr inbounds %struct.stbds_array_header, ptr %15, i32 0, i32 3
  %17 = load i64, ptr %16, align 8
  %18 = load ptr, ptr %3, align 8
  %19 = load ptr, ptr %18, align 8
  %20 = load ptr, ptr %3, align 8
  %21 = load ptr, ptr %20, align 8
  %22 = getelementptr inbounds %struct.Map, ptr %21, i64 -1
  %23 = getelementptr inbounds %struct.stbds_array_header, ptr %22, i64 -1
  %24 = getelementptr inbounds %struct.stbds_array_header, ptr %23, i32 0, i32 3
  %25 = load i64, ptr %24, align 8
  %26 = getelementptr inbounds %struct.Map, ptr %19, i64 %25
  %27 = getelementptr inbounds %struct.Map, ptr %26, i32 0, i32 1
  %28 = load ptr, ptr %27, align 8
  ret ptr %28
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @Map_del_Map_Any(ptr noundef %0, ptr noundef %1) #0 {
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca [1 x ptr], align 8
  store ptr %0, ptr %3, align 8
  store ptr %1, ptr %4, align 8
  %6 = load ptr, ptr %3, align 8
  %7 = load ptr, ptr %6, align 8
  %8 = load ptr, ptr %4, align 8
  store ptr %8, ptr %5, align 8
  %9 = getelementptr inbounds [1 x ptr], ptr %5, i64 0, i64 0
  %10 = load ptr, ptr %3, align 8
  %11 = load ptr, ptr %10, align 8
  %12 = getelementptr inbounds %struct.Map, ptr %11, i32 0, i32 0
  %13 = load ptr, ptr %3, align 8
  %14 = load ptr, ptr %13, align 8
  %15 = ptrtoint ptr %12 to i64
  %16 = ptrtoint ptr %14 to i64
  %17 = sub i64 %15, %16
  %18 = call ptr @stbds_hmdel_key(ptr noundef %7, i64 noundef 16, ptr noundef %9, i64 noundef 8, i64 noundef %17, i32 noundef 0)
  %19 = load ptr, ptr %3, align 8
  store ptr %18, ptr %19, align 8
  %20 = load ptr, ptr %3, align 8
  %21 = load ptr, ptr %20, align 8
  %22 = icmp ne ptr %21, null
  br i1 %22, label %23, label %30

23:                                               ; preds = %2
  %24 = load ptr, ptr %3, align 8
  %25 = load ptr, ptr %24, align 8
  %26 = getelementptr inbounds %struct.Map, ptr %25, i64 -1
  %27 = getelementptr inbounds %struct.stbds_array_header, ptr %26, i64 -1
  %28 = getelementptr inbounds %struct.stbds_array_header, ptr %27, i32 0, i32 3
  %29 = load i64, ptr %28, align 8
  br label %31

30:                                               ; preds = %2
  br label %31

31:                                               ; preds = %30, %23
  %32 = phi i64 [ %29, %23 ], [ 0, %30 ]
  %33 = trunc i64 %32 to i32
  ret i32 %33
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @Map_len_Map(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = load ptr, ptr %3, align 8
  %5 = icmp ne ptr %4, null
  br i1 %5, label %6, label %14

6:                                                ; preds = %1
  %7 = load ptr, ptr %2, align 8
  %8 = load ptr, ptr %7, align 8
  %9 = getelementptr inbounds %struct.Map, ptr %8, i64 -1
  %10 = getelementptr inbounds %struct.stbds_array_header, ptr %9, i64 -1
  %11 = getelementptr inbounds %struct.stbds_array_header, ptr %10, i32 0, i32 0
  %12 = load i64, ptr %11, align 8
  %13 = sub nsw i64 %12, 1
  br label %15

14:                                               ; preds = %1
  br label %15

15:                                               ; preds = %14, %6
  %16 = phi i64 [ %13, %6 ], [ 0, %14 ]
  %17 = trunc i64 %16 to i32
  ret i32 %17
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @Map_free_Map(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = icmp ne ptr %3, null
  br i1 %4, label %5, label %8

5:                                                ; preds = %1
  %6 = load ptr, ptr %2, align 8
  %7 = getelementptr inbounds ptr, ptr %6, i64 -1
  call void @stbds_hmfree_func(ptr noundef %7, i64 noundef 8)
  br label %9

8:                                                ; preds = %1
  br label %9

9:                                                ; preds = %8, %5
  %10 = phi i32 [ 0, %5 ], [ 0, %8 ]
  store ptr null, ptr %2, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define internal i64 @stbds_log2(i64 noundef %0) #0 {
  %2 = alloca i64, align 8
  %3 = alloca i64, align 8
  store i64 %0, ptr %2, align 8
  store i64 0, ptr %3, align 8
  br label %4

4:                                                ; preds = %7, %1
  %5 = load i64, ptr %2, align 8
  %6 = icmp ugt i64 %5, 1
  br i1 %6, label %7, label %12

7:                                                ; preds = %4
  %8 = load i64, ptr %2, align 8
  %9 = lshr i64 %8, 1
  store i64 %9, ptr %2, align 8
  %10 = load i64, ptr %3, align 8
  %11 = add i64 %10, 1
  store i64 %11, ptr %3, align 8
  br label %4, !llvm.loop !25

12:                                               ; preds = %4
  %13 = load i64, ptr %3, align 8
  ret i64 %13
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #6

; Function Attrs: nounwind
declare i32 @strcmp(ptr noundef, ptr noundef) #4

declare i32 @memcmp(ptr noundef, ptr noundef, i64 noundef) #3

attributes #0 = { noinline nounwind optnone ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #1 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #2 = { allocsize(1) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #3 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #4 = { nounwind "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #5 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #6 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #7 = { allocsize(1) }
attributes #8 = { nounwind }

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
!12 = distinct !{!12, !7}
!13 = distinct !{!13, !7}
!14 = distinct !{!14, !7}
!15 = distinct !{!15, !7}
!16 = distinct !{!16, !7}
!17 = distinct !{!17, !7}
!18 = distinct !{!18, !7}
!19 = distinct !{!19, !7}
!20 = distinct !{!20, !7}
!21 = distinct !{!21, !7}
!22 = distinct !{!22, !7}
!23 = distinct !{!23, !7}
!24 = distinct !{!24, !7}
!25 = distinct !{!25, !7}
