; Function Attrs: nofree norecurse nosync nounwind ssp memory(read, inaccessiblemem: none) uwtable(sync)
define range(i32 0, 1024) i32 @hash(ptr nocapture noundef readonly %0) local_unnamed_addr #0 {
  %2 = load i8, ptr %0, align 1, !tbaa !6
  %3 = icmp eq i8 %2, 0
  br i1 %3, label %16, label %4

4:                                                ; preds = %1, %4
  %5 = phi i8 [ %12, %4 ], [ %2, %1 ]
  %6 = phi i32 [ %11, %4 ], [ -2128831035, %1 ]
  %7 = phi ptr [ %8, %4 ], [ %0, %1 ]
  %8 = getelementptr inbounds i8, ptr %7, i64 1
  %9 = zext i8 %5 to i32
  %10 = xor i32 %6, %9
  %11 = mul i32 %10, 16777619
  %12 = load i8, ptr %8, align 1, !tbaa !6
  %13 = icmp eq i8 %12, 0
  br i1 %13, label %14, label %4, !llvm.loop !9

14:                                               ; preds = %4
  %15 = and i32 %11, 1023
  br label %16

16:                                               ; preds = %14, %1
  %17 = phi i32 [ 453, %1 ], [ %15, %14 ]
  ret i32 %17
}

; Function Attrs: nofree nounwind ssp uwtable(sync)
define noalias noundef ptr @new_entry(ptr nocapture noundef readonly %0, ptr nocapture noundef readonly %1, ptr nocapture noundef readonly %2) local_unnamed_addr #1 {
  %4 = tail call dereferenceable_or_null(24) ptr @malloc(i64 noundef 24) #11
  %5 = tail call ptr @strdup(ptr noundef %1) #12
  store ptr %5, ptr %4, align 8, !tbaa !11
  %6 = getelementptr inbounds i8, ptr %0, i64 8
  %7 = load i32, ptr %6, align 8, !tbaa !14
  %8 = zext i32 %7 to i64
  %9 = tail call ptr @malloc(i64 noundef %8) #11
  %10 = getelementptr inbounds i8, ptr %4, i64 8
  store ptr %9, ptr %10, align 8, !tbaa !17
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef align 1 %9, ptr noundef align 1 %2, i64 noundef %8, i1 noundef false) #12
  %11 = getelementptr inbounds i8, ptr %4, i64 16
  store ptr null, ptr %11, align 8, !tbaa !18
  ret ptr %4
}

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @malloc(i64 noundef) local_unnamed_addr #2

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: readwrite, inaccessiblemem: readwrite)
declare noalias ptr @strdup(ptr nocapture noundef readonly) local_unnamed_addr #3

; Function Attrs: mustprogress nofree nounwind ssp willreturn memory(write, argmem: none, inaccessiblemem: readwrite) uwtable(sync)
define noalias noundef ptr @Map_new_Int(i32 noundef %0) local_unnamed_addr #4 {
  %2 = tail call dereferenceable_or_null(16) ptr @malloc(i64 noundef 16) #11
  %3 = getelementptr inbounds i8, ptr %2, i64 8
  store i32 %0, ptr %3, align 8, !tbaa !14
  %4 = tail call dereferenceable_or_null(8192) ptr @calloc(i64 noundef 1024, i64 noundef 8) #13
  store ptr %4, ptr %2, align 8, !tbaa !19
  ret ptr %2
}

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,zeroed") allocsize(0,1) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @calloc(i64 noundef, i64 noundef) local_unnamed_addr #5

; Function Attrs: nofree nounwind ssp uwtable(sync)
define void @Map_add_Map_Str_Any(ptr nocapture noundef readonly %0, ptr nocapture noundef readonly %1, ptr nocapture noundef readonly %2) local_unnamed_addr #1 {
  %4 = load i8, ptr %1, align 1, !tbaa !6
  %5 = icmp eq i8 %4, 0
  br i1 %5, label %19, label %6

6:                                                ; preds = %3, %6
  %7 = phi i8 [ %14, %6 ], [ %4, %3 ]
  %8 = phi i32 [ %13, %6 ], [ -2128831035, %3 ]
  %9 = phi ptr [ %10, %6 ], [ %1, %3 ]
  %10 = getelementptr inbounds i8, ptr %9, i64 1
  %11 = zext i8 %7 to i32
  %12 = xor i32 %8, %11
  %13 = mul i32 %12, 16777619
  %14 = load i8, ptr %10, align 1, !tbaa !6
  %15 = icmp eq i8 %14, 0
  br i1 %15, label %16, label %6, !llvm.loop !9

16:                                               ; preds = %6
  %17 = and i32 %13, 1023
  %18 = zext nneg i32 %17 to i64
  br label %19

19:                                               ; preds = %3, %16
  %20 = phi i64 [ 453, %3 ], [ %18, %16 ]
  %21 = load ptr, ptr %0, align 8, !tbaa !19
  %22 = getelementptr inbounds ptr, ptr %21, i64 %20
  %23 = load ptr, ptr %22, align 8, !tbaa !20
  %24 = icmp eq ptr %23, null
  br i1 %24, label %40, label %25

25:                                               ; preds = %19, %36
  %26 = phi ptr [ %38, %36 ], [ %23, %19 ]
  %27 = load ptr, ptr %26, align 8, !tbaa !11
  %28 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %27, ptr noundef nonnull dereferenceable(1) %1) #12
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %30, label %36

30:                                               ; preds = %25
  %31 = getelementptr inbounds i8, ptr %26, i64 8
  %32 = load ptr, ptr %31, align 8, !tbaa !17
  %33 = getelementptr inbounds i8, ptr %0, i64 8
  %34 = load i32, ptr %33, align 8, !tbaa !14
  %35 = zext i32 %34 to i64
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef align 1 %32, ptr noundef align 1 %2, i64 noundef %35, i1 noundef false) #12
  br label %49

36:                                               ; preds = %25
  %37 = getelementptr inbounds i8, ptr %26, i64 16
  %38 = load ptr, ptr %37, align 8, !tbaa !20
  %39 = icmp eq ptr %38, null
  br i1 %39, label %40, label %25, !llvm.loop !21

40:                                               ; preds = %36, %19
  %41 = tail call dereferenceable_or_null(24) ptr @malloc(i64 noundef 24) #11
  %42 = tail call ptr @strdup(ptr noundef nonnull readonly %1) #12
  store ptr %42, ptr %41, align 8, !tbaa !11
  %43 = getelementptr inbounds i8, ptr %0, i64 8
  %44 = load i32, ptr %43, align 8, !tbaa !14
  %45 = zext i32 %44 to i64
  %46 = tail call ptr @malloc(i64 noundef %45) #11
  %47 = getelementptr inbounds i8, ptr %41, i64 8
  store ptr %46, ptr %47, align 8, !tbaa !17
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef align 1 %46, ptr noundef readonly align 1 %2, i64 noundef %45, i1 noundef false) #12
  %48 = getelementptr inbounds i8, ptr %41, i64 16
  store ptr %23, ptr %48, align 8, !tbaa !18
  store ptr %41, ptr %22, align 8, !tbaa !20
  br label %49

49:                                               ; preds = %40, %30
  ret void
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: read)
declare i32 @strcmp(ptr nocapture noundef, ptr nocapture noundef) local_unnamed_addr #6

; Function Attrs: nofree nounwind ssp memory(read, inaccessiblemem: none) uwtable(sync)
define ptr @Map_get_Map_Str(ptr nocapture noundef readonly %0, ptr nocapture noundef readonly %1) local_unnamed_addr #7 {
  %3 = load ptr, ptr %0, align 8, !tbaa !19
  %4 = load i8, ptr %1, align 1, !tbaa !6
  %5 = icmp eq i8 %4, 0
  br i1 %5, label %19, label %6

6:                                                ; preds = %2, %6
  %7 = phi i8 [ %14, %6 ], [ %4, %2 ]
  %8 = phi i32 [ %13, %6 ], [ -2128831035, %2 ]
  %9 = phi ptr [ %10, %6 ], [ %1, %2 ]
  %10 = getelementptr inbounds i8, ptr %9, i64 1
  %11 = zext i8 %7 to i32
  %12 = xor i32 %8, %11
  %13 = mul i32 %12, 16777619
  %14 = load i8, ptr %10, align 1, !tbaa !6
  %15 = icmp eq i8 %14, 0
  br i1 %15, label %16, label %6, !llvm.loop !9

16:                                               ; preds = %6
  %17 = and i32 %13, 1023
  %18 = zext nneg i32 %17 to i64
  br label %19

19:                                               ; preds = %2, %16
  %20 = phi i64 [ 453, %2 ], [ %18, %16 ]
  %21 = getelementptr inbounds ptr, ptr %3, i64 %20
  %22 = load ptr, ptr %21, align 8, !tbaa !20
  %23 = icmp eq ptr %22, null
  br i1 %23, label %36, label %24

24:                                               ; preds = %19, %32
  %25 = phi ptr [ %34, %32 ], [ %22, %19 ]
  %26 = load ptr, ptr %25, align 8, !tbaa !11
  %27 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %26, ptr noundef nonnull dereferenceable(1) %1) #12
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %29, label %32

29:                                               ; preds = %24
  %30 = getelementptr inbounds i8, ptr %25, i64 8
  %31 = load ptr, ptr %30, align 8, !tbaa !17
  br label %36

32:                                               ; preds = %24
  %33 = getelementptr inbounds i8, ptr %25, i64 16
  %34 = load ptr, ptr %33, align 8, !tbaa !20
  %35 = icmp eq ptr %34, null
  br i1 %35, label %36, label %24, !llvm.loop !22

36:                                               ; preds = %32, %19, %29
  %37 = phi ptr [ %31, %29 ], [ null, %19 ], [ null, %32 ]
  ret ptr %37
}

; Function Attrs: nounwind ssp uwtable(sync)
define void @Map_free_Map(ptr nocapture noundef %0) local_unnamed_addr #8 {
  br label %4

2:                                                ; preds = %18
  %3 = load ptr, ptr %0, align 8, !tbaa !19
  tail call void @free(ptr noundef %3)
  tail call void @free(ptr noundef %0)
  ret void

4:                                                ; preds = %1, %18
  %5 = phi i64 [ 0, %1 ], [ %19, %18 ]
  %6 = load ptr, ptr %0, align 8, !tbaa !19
  %7 = getelementptr inbounds ptr, ptr %6, i64 %5
  %8 = load ptr, ptr %7, align 8, !tbaa !20
  %9 = icmp eq ptr %8, null
  br i1 %9, label %18, label %10

10:                                               ; preds = %4, %10
  %11 = phi ptr [ %13, %10 ], [ %8, %4 ]
  %12 = getelementptr inbounds i8, ptr %11, i64 16
  %13 = load ptr, ptr %12, align 8, !tbaa !18
  %14 = load ptr, ptr %11, align 8, !tbaa !11
  tail call void @free(ptr noundef %14)
  %15 = getelementptr inbounds i8, ptr %11, i64 8
  %16 = load ptr, ptr %15, align 8, !tbaa !17
  tail call void @free(ptr noundef %16)
  tail call void @free(ptr noundef nonnull %11)
  %17 = icmp eq ptr %13, null
  br i1 %17, label %18, label %10, !llvm.loop !23

18:                                               ; preds = %10, %4
  %19 = add nuw nsw i64 %5, 1
  %20 = icmp eq i64 %19, 1024
  br i1 %20, label %2, label %4, !llvm.loop !24
}

; Function Attrs: mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite)
declare void @free(ptr allocptr nocapture noundef) local_unnamed_addr #9

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #10

attributes #0 = { nofree norecurse nosync nounwind ssp memory(read, inaccessiblemem: none) uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #1 = { nofree nounwind ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #2 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #3 = { mustprogress nofree nounwind willreturn memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #4 = { mustprogress nofree nounwind ssp willreturn memory(write, argmem: none, inaccessiblemem: readwrite) uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #5 = { mustprogress nofree nounwind willreturn allockind("alloc,zeroed") allocsize(0,1) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #6 = { mustprogress nofree nounwind willreturn memory(argmem: read) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #7 = { nofree nounwind ssp memory(read, inaccessiblemem: none) uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #8 = { nounwind ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #9 = { mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #10 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #11 = { allocsize(0) }
attributes #12 = { nounwind }
attributes #13 = { allocsize(0,1) }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 2]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Homebrew clang version 19.1.7"}
!6 = !{!7, !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C/C++ TBAA"}
!9 = distinct !{!9, !10}
!10 = !{!"llvm.loop.mustprogress"}
!11 = !{!12, !13, i64 0}
!12 = !{!"Entry", !13, i64 0, !13, i64 8, !13, i64 16}
!13 = !{!"any pointer", !7, i64 0}
!14 = !{!15, !16, i64 8}
!15 = !{!"", !13, i64 0, !16, i64 8}
!16 = !{!"int", !7, i64 0}
!17 = !{!12, !13, i64 8}
!18 = !{!12, !13, i64 16}
!19 = !{!15, !13, i64 0}
!20 = !{!13, !13, i64 0}
!21 = distinct !{!21, !10}
!22 = distinct !{!22, !10}
!23 = distinct !{!23, !10}
!24 = distinct !{!24, !10}
