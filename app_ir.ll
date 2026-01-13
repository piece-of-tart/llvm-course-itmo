; ModuleID = '/home/michael/itmo/llvm-2025/src/app.cpp'
source_filename = "/home/michael/itmo/llvm-2025/src/app.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.GameOfLife = type { [9600 x i8] }

@_ZZL14GameOfLifeInitP10GameOfLifeE4rand = internal unnamed_addr global i32 -1831433054, align 4

; Function Attrs: mustprogress noreturn uwtable
define dso_local noundef i32 @_Z3appv() local_unnamed_addr #0 {
  %1 = alloca [9600 x i8], align 16
  %2 = alloca %struct.GameOfLife, align 1
  call void @llvm.lifetime.start.p0(i64 9600, ptr nonnull %2) #7
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 1 dereferenceable(9600) %2, i8 0, i64 9600, i1 false)
  %3 = load i32, ptr @_ZZL14GameOfLifeInitP10GameOfLifeE4rand, align 4, !tbaa !5
  br label %4

4:                                                ; preds = %8, %0
  %5 = phi i64 [ 0, %0 ], [ %9, %8 ]
  %6 = phi i32 [ %3, %0 ], [ %36, %8 ]
  %7 = mul nuw nsw i64 %5, 120
  br label %11

8:                                                ; preds = %11
  %9 = add nuw nsw i64 %5, 1
  %10 = icmp eq i64 %9, 80
  br i1 %10, label %39, label %4, !llvm.loop !9

11:                                               ; preds = %11, %4
  %12 = phi i64 [ 0, %4 ], [ %37, %11 ]
  %13 = phi i32 [ %6, %4 ], [ %36, %11 ]
  %14 = add nuw nsw i64 %12, %7
  %15 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %14
  %16 = trunc i32 %13 to i8
  %17 = and i8 %16, 1
  %18 = xor i8 %17, 1
  store i8 %18, ptr %15, align 1, !tbaa !11
  %19 = shl i32 %13, 13
  %20 = xor i32 %19, %13
  %21 = ashr i32 %20, 17
  %22 = xor i32 %21, %20
  %23 = shl i32 %22, 5
  %24 = xor i32 %23, %22
  %25 = or disjoint i64 %12, 1
  %26 = add nuw nsw i64 %25, %7
  %27 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %26
  %28 = trunc i32 %22 to i8
  %29 = and i8 %28, 1
  %30 = xor i8 %29, 1
  store i8 %30, ptr %27, align 1, !tbaa !11
  %31 = shl i32 %24, 13
  %32 = xor i32 %31, %24
  %33 = ashr i32 %32, 17
  %34 = xor i32 %33, %32
  %35 = shl i32 %34, 5
  %36 = xor i32 %35, %34
  %37 = add nuw nsw i64 %12, 2
  %38 = icmp eq i64 %37, 120
  br i1 %38, label %8, label %11, !llvm.loop !13

39:                                               ; preds = %8
  store i32 %36, ptr @_ZZL14GameOfLifeInitP10GameOfLifeE4rand, align 4, !tbaa !5
  call fastcc void @_ZL19GameOfLifeNextFieldP10GameOfLife(ptr noundef %2)
  br label %40

40:                                               ; preds = %132, %39
  call void @llvm.lifetime.start.p0(i64 9600, ptr nonnull %1) #7
  br label %41

41:                                               ; preds = %54, %40
  %42 = phi i64 [ 0, %40 ], [ %55, %54 ]
  %43 = trunc i64 %42 to i32
  %44 = add i32 %43, 79
  %45 = urem i32 %44, 80
  %46 = mul nuw nsw i32 %45, 120
  %47 = add i32 %43, 80
  %48 = urem i32 %47, 80
  %49 = mul nuw nsw i32 %48, 120
  %50 = add i32 %43, 81
  %51 = urem i32 %50, 80
  %52 = mul nuw nsw i32 %51, 120
  %53 = mul nuw nsw i64 %42, 120
  br label %57

54:                                               ; preds = %125
  %55 = add nuw nsw i64 %42, 1
  %56 = icmp eq i64 %55, 80
  br i1 %56, label %128, label %41, !llvm.loop !14

57:                                               ; preds = %125, %41
  %58 = phi i64 [ 0, %41 ], [ %126, %125 ]
  %59 = trunc i64 %58 to i8
  %60 = add nuw i8 %59, 79
  %61 = urem i8 %60, 80
  %62 = zext nneg i8 %61 to i32
  %63 = add nuw nsw i32 %46, %62
  %64 = zext nneg i32 %63 to i64
  %65 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %64
  %66 = load i8, ptr %65, align 1, !tbaa !11, !range !15, !noundef !16
  %67 = add nuw nsw i32 %49, %62
  %68 = zext nneg i32 %67 to i64
  %69 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %68
  %70 = load i8, ptr %69, align 1, !tbaa !11, !range !15, !noundef !16
  %71 = add nuw nsw i32 %52, %62
  %72 = zext nneg i32 %71 to i64
  %73 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %72
  %74 = load i8, ptr %73, align 1, !tbaa !11, !range !15, !noundef !16
  %75 = add nuw i8 %59, 80
  %76 = urem i8 %75, 80
  %77 = zext nneg i8 %76 to i32
  %78 = add nuw nsw i32 %46, %77
  %79 = zext nneg i32 %78 to i64
  %80 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %79
  %81 = load i8, ptr %80, align 1, !tbaa !11, !range !15, !noundef !16
  %82 = add nuw nsw i32 %52, %77
  %83 = zext nneg i32 %82 to i64
  %84 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %83
  %85 = load i8, ptr %84, align 1, !tbaa !11, !range !15, !noundef !16
  %86 = add nuw i8 %59, 81
  %87 = urem i8 %86, 80
  %88 = zext nneg i8 %87 to i32
  %89 = add nuw nsw i32 %46, %88
  %90 = zext nneg i32 %89 to i64
  %91 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %90
  %92 = load i8, ptr %91, align 1, !tbaa !11, !range !15, !noundef !16
  %93 = add nuw nsw i32 %49, %88
  %94 = zext nneg i32 %93 to i64
  %95 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %94
  %96 = load i8, ptr %95, align 1, !tbaa !11, !range !15, !noundef !16
  %97 = add nuw nsw i8 %70, %66
  %98 = add nuw nsw i8 %97, %74
  %99 = add nuw nsw i8 %98, %81
  %100 = add nuw nsw i8 %99, %85
  %101 = add nuw nsw i8 %100, %92
  %102 = add nuw nsw i8 %101, %96
  %103 = zext nneg i8 %102 to i32
  %104 = add nuw nsw i32 %52, %88
  %105 = zext nneg i32 %104 to i64
  %106 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %105
  %107 = load i8, ptr %106, align 1, !tbaa !11, !range !15, !noundef !16
  %108 = zext nneg i8 %107 to i32
  %109 = add nuw nsw i32 %103, %108
  %110 = add nuw nsw i64 %58, %53
  %111 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %110
  %112 = load i8, ptr %111, align 1, !tbaa !11, !range !15, !noundef !16
  %113 = trunc nuw i8 %112 to i1
  %114 = icmp ne i32 %109, 3
  %115 = or i1 %114, %113
  br i1 %115, label %118, label %116

116:                                              ; preds = %57
  %117 = getelementptr inbounds nuw [9600 x i8], ptr %1, i64 0, i64 %110
  store i8 1, ptr %117, align 1, !tbaa !11
  br label %125

118:                                              ; preds = %57
  %119 = add nsw i32 %109, -4
  %120 = icmp ult i32 %119, -2
  %121 = and i1 %120, %113
  %122 = getelementptr inbounds nuw [9600 x i8], ptr %1, i64 0, i64 %110
  br i1 %121, label %123, label %124

123:                                              ; preds = %118
  store i8 0, ptr %122, align 1, !tbaa !11
  br label %125

124:                                              ; preds = %118
  store i8 %112, ptr %122, align 1, !tbaa !11
  br label %125

125:                                              ; preds = %124, %123, %116
  %126 = add nuw nsw i64 %58, 1
  %127 = icmp eq i64 %126, 120
  br i1 %127, label %54, label %57, !llvm.loop !17

128:                                              ; preds = %54
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(9600) %2, ptr noundef nonnull align 16 dereferenceable(9600) %1, i64 9600, i1 false), !tbaa !11
  call void @llvm.lifetime.end.p0(i64 9600, ptr nonnull %1) #7
  br label %129

129:                                              ; preds = %128, %133
  %130 = phi i64 [ 0, %128 ], [ %134, %133 ]
  %131 = trunc nuw nsw i64 %130 to i32
  br label %136

132:                                              ; preds = %133
  tail call void @_Z14Graphics_flushv()
  br label %40, !llvm.loop !18

133:                                              ; preds = %136
  %134 = add nuw nsw i64 %130, 1
  %135 = icmp eq i64 %134, 120
  br i1 %135, label %132, label %129, !llvm.loop !19

136:                                              ; preds = %129, %136
  %137 = phi i64 [ 0, %129 ], [ %145, %136 ]
  %138 = mul nuw nsw i64 %137, 120
  %139 = add nuw nsw i64 %138, %130
  %140 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %139
  %141 = load i8, ptr %140, align 1, !tbaa !11, !range !15, !noundef !16
  %142 = zext nneg i8 %141 to i32
  %143 = sub nsw i32 0, %142
  %144 = trunc nuw nsw i64 %137 to i32
  tail call void @_Z18Graphics_put_pixeliiij(i32 noundef %131, i32 noundef %144, i32 noundef 10, i32 noundef %143)
  %145 = add nuw nsw i64 %137, 1
  %146 = icmp eq i64 %145, 80
  br i1 %146, label %133, label %136, !llvm.loop !20
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr captures(none)) #1

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr writeonly captures(none), i8, i64, i1 immarg) #2

; Function Attrs: mustprogress nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable
define internal fastcc void @_ZL19GameOfLifeNextFieldP10GameOfLife(ptr noundef nonnull captures(none) %0) unnamed_addr #3 {
  %2 = alloca [9600 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 9600, ptr nonnull %2) #7
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
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(9600) %0, ptr noundef nonnull align 16 dereferenceable(9600) %2, i64 9600, i1 false), !tbaa !11
  call void @llvm.lifetime.end.p0(i64 9600, ptr nonnull %2) #7
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
  %31 = load i8, ptr %30, align 1, !tbaa !11, !range !15, !noundef !16
  %32 = add nuw nsw i32 %12, %27
  %33 = zext nneg i32 %32 to i64
  %34 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %33
  %35 = load i8, ptr %34, align 1, !tbaa !11, !range !15, !noundef !16
  %36 = add nuw nsw i32 %16, %27
  %37 = zext nneg i32 %36 to i64
  %38 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %37
  %39 = load i8, ptr %38, align 1, !tbaa !11, !range !15, !noundef !16
  %40 = add nuw i8 %24, 80
  %41 = urem i8 %40, 80
  %42 = zext nneg i8 %41 to i32
  %43 = add nuw nsw i32 %8, %42
  %44 = zext nneg i32 %43 to i64
  %45 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %44
  %46 = load i8, ptr %45, align 1, !tbaa !11, !range !15, !noundef !16
  %47 = add nuw nsw i32 %16, %42
  %48 = zext nneg i32 %47 to i64
  %49 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %48
  %50 = load i8, ptr %49, align 1, !tbaa !11, !range !15, !noundef !16
  %51 = add nuw i8 %24, 81
  %52 = urem i8 %51, 80
  %53 = zext nneg i8 %52 to i32
  %54 = add nuw nsw i32 %8, %53
  %55 = zext nneg i32 %54 to i64
  %56 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %55
  %57 = load i8, ptr %56, align 1, !tbaa !11, !range !15, !noundef !16
  %58 = add nuw nsw i32 %12, %53
  %59 = zext nneg i32 %58 to i64
  %60 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %59
  %61 = load i8, ptr %60, align 1, !tbaa !11, !range !15, !noundef !16
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
  %72 = load i8, ptr %71, align 1, !tbaa !11, !range !15, !noundef !16
  %73 = zext nneg i8 %72 to i32
  %74 = add nuw nsw i32 %68, %73
  %75 = add nuw nsw i64 %23, %17
  %76 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %75
  %77 = load i8, ptr %76, align 1, !tbaa !11, !range !15, !noundef !16
  %78 = trunc nuw i8 %77 to i1
  %79 = icmp ne i32 %74, 3
  %80 = or i1 %79, %78
  br i1 %80, label %83, label %81

81:                                               ; preds = %22
  %82 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %75
  store i8 1, ptr %82, align 1, !tbaa !11
  br label %90

83:                                               ; preds = %22
  %84 = add nsw i32 %74, -4
  %85 = icmp ult i32 %84, -2
  %86 = and i1 %85, %78
  %87 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %75
  br i1 %86, label %88, label %89

88:                                               ; preds = %83
  store i8 0, ptr %87, align 1, !tbaa !11
  br label %90

89:                                               ; preds = %83
  store i8 %77, ptr %87, align 1, !tbaa !11
  br label %90

90:                                               ; preds = %88, %89, %81
  %91 = add nuw nsw i64 %23, 1
  %92 = icmp eq i64 %91, 120
  br i1 %92, label %18, label %22, !llvm.loop !17
}

declare void @_Z18Graphics_put_pixeliiij(i32 noundef, i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #4

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr captures(none)) #1

declare void @_Z14Graphics_flushv() local_unnamed_addr #4

; Function Attrs: mustprogress norecurse noreturn uwtable
define dso_local noundef i32 @main() local_unnamed_addr #5 {
  %1 = tail call noundef i32 @_Z3appv()
  unreachable
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias writeonly captures(none), ptr noalias readonly captures(none), i64, i1 immarg) #6

attributes #0 = { mustprogress noreturn uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #3 = { mustprogress nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { mustprogress norecurse noreturn uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #7 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"Ubuntu clang version 21.1.8 (++20251221032922+2078da43e25a-1~exp1~20251221153059.70)"}
!5 = !{!6, !6, i64 0}
!6 = !{!"int", !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C++ TBAA"}
!9 = distinct !{!9, !10}
!10 = !{!"llvm.loop.mustprogress"}
!11 = !{!12, !12, i64 0}
!12 = !{!"bool", !7, i64 0}
!13 = distinct !{!13, !10}
!14 = distinct !{!14, !10}
!15 = !{i8 0, i8 2}
!16 = !{}
!17 = distinct !{!17, !10}
!18 = distinct !{!18, !10}
!19 = distinct !{!19, !10}
!20 = distinct !{!20, !10}
