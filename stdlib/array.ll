declare noalias noundef ptr @malloc(i64 noundef) local_unnamed_addr #1
declare void @free(ptr allocptr nocapture noundef) local_unnamed_addr #2
declare noalias noundef ptr @realloc(ptr allocptr nocapture noundef, i64 noundef) local_unnamed_addr #4
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #7

define noalias noundef ptr @Array_new_Int_Long(i32 noundef %0, i64 noundef %1) local_unnamed_addr #0 {
  %3 = tail call dereferenceable_or_null(24) ptr @malloc(i64 noundef 24) #8
  %4 = icmp eq ptr %3, null
  br i1 %4, label %14, label %5

5:
  %6 = getelementptr inbounds i8, ptr %3, i64 8
  store i32 %0, ptr %6, align 8, !tbaa !6
  %7 = getelementptr inbounds i8, ptr %3, i64 12
  store i32 0, ptr %7, align 4, !tbaa !13
  store i64 %1, ptr %3, align 8, !tbaa !14
  %8 = zext i32 %0 to i64
  %9 = mul i64 %8, %1
  %10 = tail call ptr @malloc(i64 noundef %9) #8
  %11 = getelementptr inbounds i8, ptr %3, i64 16
  store ptr %10, ptr %11, align 8, !tbaa !15
  %12 = icmp eq ptr %10, null
  br i1 %12, label %13, label %14

13:
  tail call void @free(ptr noundef nonnull %3)
  br label %14

14:
  %15 = phi ptr [ null, %13 ], [ null, %2 ], [ %3, %5 ]
  ret ptr %15
}



define void @resize(ptr nocapture noundef %0) local_unnamed_addr #3 {
  %2 = getelementptr inbounds i8, ptr %0, i64 8
  %3 = load i32, ptr %2, align 8, !tbaa !6
  %4 = shl i32 %3, 1
  store i32 %4, ptr %2, align 8, !tbaa !6
  %5 = getelementptr inbounds i8, ptr %0, i64 16
  %6 = load ptr, ptr %5, align 8, !tbaa !15
  %7 = zext i32 %4 to i64
  %8 = load i64, ptr %0, align 8, !tbaa !14
  %9 = mul i64 %8, %7
  %10 = tail call ptr @realloc(ptr noundef %6, i64 noundef %9) #9
  %11 = icmp eq ptr %10, null
  br i1 %11, label %13, label %12

12:
  store ptr %10, ptr %5, align 8, !tbaa !15
  br label %13

13:
  ret void
}




define void @Array_add_Array_Any(ptr nocapture noundef %0, ptr nocapture noundef readonly %1) local_unnamed_addr #5 {
  %3 = getelementptr inbounds i8, ptr %0, i64 12
  %4 = load i32, ptr %3, align 4, !tbaa !13
  %5 = getelementptr inbounds i8, ptr %0, i64 8
  %6 = load i32, ptr %5, align 8, !tbaa !6
  %7 = icmp eq i32 %4, %6
  br i1 %7, label %8, label %18

8:
  %9 = shl i32 %4, 1
  store i32 %9, ptr %5, align 8, !tbaa !6
  %10 = getelementptr inbounds i8, ptr %0, i64 16
  %11 = load ptr, ptr %10, align 8, !tbaa !15
  %12 = zext i32 %9 to i64
  %13 = load i64, ptr %0, align 8, !tbaa !14
  %14 = mul i64 %13, %12
  %15 = tail call ptr @realloc(ptr noundef %11, i64 noundef %14) #9
  %16 = icmp eq ptr %15, null
  br i1 %16, label %18, label %17

17:
  store ptr %15, ptr %10, align 8, !tbaa !15
  br label %18

18:
  %19 = getelementptr inbounds i8, ptr %0, i64 16
  %20 = load ptr, ptr %19, align 8, !tbaa !15
  %21 = load i32, ptr %3, align 4, !tbaa !13
  %22 = zext i32 %21 to i64
  %23 = load i64, ptr %0, align 8, !tbaa !14
  %24 = mul i64 %23, %22
  %25 = getelementptr inbounds i8, ptr %20, i64 %24
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef align 1 %25, ptr noundef align 1 %1, i64 noundef %23, i1 noundef false) #10
  %26 = load i32, ptr %3, align 4, !tbaa !13
  %27 = add i32 %26, 1
  store i32 %27, ptr %3, align 4, !tbaa !13
  ret void
}


define ptr @Array_get_Array_Int(ptr nocapture noundef readonly %0, i32 noundef %1) local_unnamed_addr #6 {
  %3 = getelementptr inbounds i8, ptr %0, i64 12
  %4 = load i32, ptr %3, align 4, !tbaa !13
  %5 = icmp ugt i32 %4, %1
  br i1 %5, label %6, label %13

6:
  %7 = getelementptr inbounds i8, ptr %0, i64 16
  %8 = load ptr, ptr %7, align 8, !tbaa !15
  %9 = zext i32 %1 to i64
  %10 = load i64, ptr %0, align 8, !tbaa !14
  %11 = mul i64 %10, %9
  %12 = getelementptr inbounds i8, ptr %8, i64 %11
  br label %13

13:
  %14 = phi ptr [ %12, %6 ], [ null, %2 ]
  ret ptr %14
}


define void @Array_free_Array(ptr noundef %0) local_unnamed_addr #3 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %6, label %3

3:
  %4 = getelementptr inbounds i8, ptr %0, i64 16
  %5 = load ptr, ptr %4, align 8, !tbaa !15
  tail call void @free(ptr noundef %5)
  tail call void @free(ptr noundef nonnull %0)
  br label %6

6:
  ret void
}

attributes #0 = { mustprogress nounwind ssp willreturn memory(readwrite, argmem: none) uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #1 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #2 = { mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #3 = { mustprogress nounwind ssp willreturn uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #4 = { mustprogress nounwind willreturn allockind("realloc") allocsize(1) memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #5 = { nounwind ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #6 = { mustprogress nofree norecurse nosync nounwind ssp willreturn memory(argmem: read) uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #7 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #8 = { allocsize(0) }
attributes #9 = { allocsize(1) }
attributes #10 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 2]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Homebrew clang version 19.1.7"}
!6 = !{!7, !11, i64 8}
!7 = !{!"", !8, i64 0, !11, i64 8, !11, i64 12, !12, i64 16}
!8 = !{!"long", !9, i64 0}
!9 = !{!"omnipotent char", !10, i64 0}
!10 = !{!"Simple C/C++ TBAA"}
!11 = !{!"int", !9, i64 0}
!12 = !{!"any pointer", !9, i64 0}
!13 = !{!7, !11, i64 12}
!14 = !{!7, !8, i64 0}
!15 = !{!7, !12, i64 16}
