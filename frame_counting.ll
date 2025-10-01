; ModuleID = '/home/michael/itmo/llvm-2025/src/FrameCounting.cpp'
source_filename = "/home/michael/itmo/llvm-2025/src/FrameCounting.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress uwtable
define dso_local void @_Z15GameOfLife_initP10GameOfLife(ptr nocapture noundef writeonly %0) local_unnamed_addr #0 {
  br label %2

2:                                                ; preds = %1, %6
  %3 = phi i64 [ 0, %1 ], [ %7, %6 ]
  %4 = mul nuw nsw i64 %3, 120
  br label %9

5:                                                ; preds = %6
  ret void

6:                                                ; preds = %9
  %7 = add nuw nsw i64 %3, 1
  %8 = icmp eq i64 %7, 80
  br i1 %8, label %5, label %2, !llvm.loop !5

9:                                                ; preds = %2, %9
  %10 = phi i64 [ 0, %2 ], [ %17, %9 ]
  %11 = tail call noundef i32 @_Z24RandomGenerator_next_intv()
  %12 = add nuw nsw i64 %10, %4
  %13 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %12
  %14 = trunc i32 %11 to i8
  %15 = and i8 %14, 1
  %16 = xor i8 %15, 1
  store i8 %16, ptr %13, align 1, !tbaa !7
  %17 = add nuw nsw i64 %10, 1
  %18 = icmp eq i64 %17, 120
  br i1 %18, label %6, label %9, !llvm.loop !11
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

declare noundef i32 @_Z24RandomGenerator_next_intv() local_unnamed_addr #2

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define dso_local noundef range(i32 0, 9) i32 @_Z26GameOfLife_get_alive_cellsP10GameOfLifeii(ptr nocapture noundef readonly %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #3 {
  %4 = add i32 %2, 80
  %5 = add i32 %1, 80
  %6 = add i32 %1, 79
  %7 = srem i32 %6, 80
  %8 = add i32 %2, 79
  %9 = srem i32 %8, 80
  %10 = mul nsw i32 %9, 120
  %11 = add nsw i32 %10, %7
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds [9600 x i8], ptr %0, i64 0, i64 %12
  %14 = load i8, ptr %13, align 1, !tbaa !7, !range !12, !noundef !13
  %15 = srem i32 %4, 80
  %16 = mul nsw i32 %15, 120
  %17 = add nsw i32 %16, %7
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds [9600 x i8], ptr %0, i64 0, i64 %18
  %20 = load i8, ptr %19, align 1, !tbaa !7, !range !12, !noundef !13
  %21 = add i32 %2, 81
  %22 = srem i32 %21, 80
  %23 = mul nsw i32 %22, 120
  %24 = add nsw i32 %23, %7
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds [9600 x i8], ptr %0, i64 0, i64 %25
  %27 = load i8, ptr %26, align 1, !tbaa !7, !range !12, !noundef !13
  %28 = srem i32 %5, 80
  %29 = add i32 %2, 79
  %30 = srem i32 %29, 80
  %31 = mul nsw i32 %30, 120
  %32 = add nsw i32 %31, %28
  %33 = sext i32 %32 to i64
  %34 = getelementptr inbounds [9600 x i8], ptr %0, i64 0, i64 %33
  %35 = load i8, ptr %34, align 1, !tbaa !7, !range !12, !noundef !13
  %36 = add i32 %2, 81
  %37 = srem i32 %36, 80
  %38 = mul nsw i32 %37, 120
  %39 = add nsw i32 %38, %28
  %40 = sext i32 %39 to i64
  %41 = getelementptr inbounds [9600 x i8], ptr %0, i64 0, i64 %40
  %42 = load i8, ptr %41, align 1, !tbaa !7, !range !12, !noundef !13
  %43 = add i32 %1, 81
  %44 = srem i32 %43, 80
  %45 = add i32 %2, 79
  %46 = srem i32 %45, 80
  %47 = mul nsw i32 %46, 120
  %48 = add nsw i32 %47, %44
  %49 = sext i32 %48 to i64
  %50 = getelementptr inbounds [9600 x i8], ptr %0, i64 0, i64 %49
  %51 = load i8, ptr %50, align 1, !tbaa !7, !range !12, !noundef !13
  %52 = srem i32 %4, 80
  %53 = mul nsw i32 %52, 120
  %54 = add nsw i32 %53, %44
  %55 = sext i32 %54 to i64
  %56 = getelementptr inbounds [9600 x i8], ptr %0, i64 0, i64 %55
  %57 = load i8, ptr %56, align 1, !tbaa !7, !range !12, !noundef !13
  %58 = add nuw nsw i8 %14, %20
  %59 = add nuw nsw i8 %58, %27
  %60 = add nuw nsw i8 %59, %35
  %61 = add nuw nsw i8 %60, %42
  %62 = add nuw nsw i8 %61, %51
  %63 = add nuw nsw i8 %62, %57
  %64 = zext nneg i8 %63 to i32
  %65 = add i32 %2, 81
  %66 = srem i32 %65, 80
  %67 = mul nsw i32 %66, 120
  %68 = add nsw i32 %67, %44
  %69 = sext i32 %68 to i64
  %70 = getelementptr inbounds [9600 x i8], ptr %0, i64 0, i64 %69
  %71 = load i8, ptr %70, align 1, !tbaa !7, !range !12, !noundef !13
  %72 = zext nneg i8 %71 to i32
  %73 = add nuw nsw i32 %64, %72
  ret i32 %73
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable
define dso_local void @_Z21GameOfLife_next_fieldP10GameOfLife(ptr nocapture noundef %0) local_unnamed_addr #4 {
  %2 = alloca [9600 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 9600, ptr nonnull %2) #6
  br label %3

3:                                                ; preds = %1, %18
  %4 = phi i64 [ 0, %1 ], [ %19, %18 ]
  %5 = trunc i64 %4 to i32
  %6 = add i32 %5, 79
  %7 = urem i32 %6, 80
  %8 = mul nuw nsw i32 %7, 120
  %9 = trunc i64 %4 to i32
  %10 = add i32 %9, 80
  %11 = urem i32 %10, 80
  %12 = mul nuw nsw i32 %11, 120
  %13 = trunc i64 %4 to i32
  %14 = add i32 %13, 81
  %15 = urem i32 %14, 80
  %16 = mul nuw nsw i32 %15, 120
  %17 = mul nuw nsw i64 %4, 120
  br label %22

18:                                               ; preds = %90
  %19 = add nuw nsw i64 %4, 1
  %20 = icmp eq i64 %19, 80
  br i1 %20, label %21, label %3, !llvm.loop !14

21:                                               ; preds = %18
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(9600) %0, ptr noundef nonnull align 16 dereferenceable(9600) %2, i64 9600, i1 false), !tbaa !7
  call void @llvm.lifetime.end.p0(i64 9600, ptr nonnull %2) #6
  ret void

22:                                               ; preds = %3, %90
  %23 = phi i64 [ 0, %3 ], [ %91, %90 ]
  %24 = trunc i64 %23 to i8
  %25 = add nuw i8 %24, 79
  %26 = urem i8 %25, 80
  %27 = zext nneg i8 %26 to i32
  %28 = add nuw nsw i32 %8, %27
  %29 = zext nneg i32 %28 to i64
  %30 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %29
  %31 = load i8, ptr %30, align 1, !tbaa !7, !range !12, !noundef !13
  %32 = add nuw nsw i32 %12, %27
  %33 = zext nneg i32 %32 to i64
  %34 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %33
  %35 = load i8, ptr %34, align 1, !tbaa !7, !range !12, !noundef !13
  %36 = add nuw nsw i32 %16, %27
  %37 = zext nneg i32 %36 to i64
  %38 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %37
  %39 = load i8, ptr %38, align 1, !tbaa !7, !range !12, !noundef !13
  %40 = add nuw i8 %24, 80
  %41 = urem i8 %40, 80
  %42 = zext nneg i8 %41 to i32
  %43 = add nuw nsw i32 %8, %42
  %44 = zext nneg i32 %43 to i64
  %45 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %44
  %46 = load i8, ptr %45, align 1, !tbaa !7, !range !12, !noundef !13
  %47 = add nuw nsw i32 %16, %42
  %48 = zext nneg i32 %47 to i64
  %49 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %48
  %50 = load i8, ptr %49, align 1, !tbaa !7, !range !12, !noundef !13
  %51 = add nuw i8 %24, 81
  %52 = urem i8 %51, 80
  %53 = zext nneg i8 %52 to i32
  %54 = add nuw nsw i32 %8, %53
  %55 = zext nneg i32 %54 to i64
  %56 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %55
  %57 = load i8, ptr %56, align 1, !tbaa !7, !range !12, !noundef !13
  %58 = add nuw nsw i32 %12, %53
  %59 = zext nneg i32 %58 to i64
  %60 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %59
  %61 = load i8, ptr %60, align 1, !tbaa !7, !range !12, !noundef !13
  %62 = add nuw nsw i8 %35, %31
  %63 = add nuw nsw i8 %62, %39
  %64 = add nuw nsw i8 %63, %46
  %65 = add nuw nsw i8 %64, %50
  %66 = add nuw nsw i8 %65, %57
  %67 = add nuw nsw i8 %66, %61
  %68 = zext nneg i8 %67 to i32
  %69 = add nuw nsw i32 %16, %53
  %70 = zext nneg i32 %69 to i64
  %71 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %70
  %72 = load i8, ptr %71, align 1, !tbaa !7, !range !12, !noundef !13
  %73 = zext nneg i8 %72 to i32
  %74 = add nuw nsw i32 %68, %73
  %75 = add nuw nsw i64 %23, %17
  %76 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %75
  %77 = load i8, ptr %76, align 1, !tbaa !7, !range !12, !noundef !13
  %78 = trunc nuw i8 %77 to i1
  %79 = icmp ne i32 %74, 3
  %80 = or i1 %79, %78
  br i1 %80, label %83, label %81

81:                                               ; preds = %22
  %82 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %75
  store i8 1, ptr %82, align 1, !tbaa !7
  br label %90

83:                                               ; preds = %22
  %84 = add nsw i32 %74, -4
  %85 = icmp ult i32 %84, -2
  %86 = and i1 %85, %78
  %87 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %75
  br i1 %86, label %88, label %89

88:                                               ; preds = %83
  store i8 0, ptr %87, align 1, !tbaa !7
  br label %90

89:                                               ; preds = %83
  store i8 %77, ptr %87, align 1, !tbaa !7
  br label %90

90:                                               ; preds = %88, %89, %81
  %91 = add nuw nsw i64 %23, 1
  %92 = icmp eq i64 %91, 120
  br i1 %92, label %18, label %22, !llvm.loop !15
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define dso_local noundef zeroext i1 @_Z20GameOfLife_get_coordP10GameOfLifeii(ptr nocapture noundef readonly %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #3 {
  %4 = mul nsw i32 %2, 120
  %5 = add nsw i32 %4, %1
  %6 = sext i32 %5 to i64
  %7 = getelementptr inbounds [9600 x i8], ptr %0, i64 0, i64 %6
  %8 = load i8, ptr %7, align 1, !tbaa !7, !range !12, !noundef !13
  %9 = trunc nuw i8 %8 to i1
  ret i1 %9
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #5

attributes #0 = { mustprogress uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { mustprogress nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #6 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"Ubuntu clang version 20.1.2 (0ubuntu1~24.04.2)"}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.mustprogress"}
!7 = !{!8, !8, i64 0}
!8 = !{!"bool", !9, i64 0}
!9 = !{!"omnipotent char", !10, i64 0}
!10 = !{!"Simple C++ TBAA"}
!11 = distinct !{!11, !6}
!12 = !{i8 0, i8 2}
!13 = !{}
!14 = distinct !{!14, !6}
!15 = distinct !{!15, !6}
