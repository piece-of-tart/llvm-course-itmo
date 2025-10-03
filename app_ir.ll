; ModuleID = '/home/michael/itmo/llvm-2025/src/app.cpp'
source_filename = "/home/michael/itmo/llvm-2025/src/app.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.GameOfLife = type { [9600 x i8] }

@_ZZ24RandomGenerator_set_seedvE4flag = internal unnamed_addr global i1 false, align 1

; Function Attrs: mustprogress nounwind uwtable
define dso_local void @_Z24RandomGenerator_set_seedv() local_unnamed_addr #0 {
  %1 = load i1, ptr @_ZZ24RandomGenerator_set_seedvE4flag, align 1
  br i1 %1, label %5, label %2

2:                                                ; preds = %0
  %3 = tail call i64 @time(ptr noundef null) #10
  %4 = trunc i64 %3 to i32
  tail call void @srand(i32 noundef %4) #10
  br label %5

5:                                                ; preds = %2, %0
  store i1 true, ptr @_ZZ24RandomGenerator_set_seedvE4flag, align 1
  ret void
}

; Function Attrs: nounwind
declare void @srand(i32 noundef) local_unnamed_addr #1

; Function Attrs: nounwind
declare i64 @time(ptr noundef) local_unnamed_addr #1

; Function Attrs: mustprogress nounwind uwtable
define dso_local noundef i32 @_Z24RandomGenerator_next_intv() local_unnamed_addr #0 {
  %1 = load i1, ptr @_ZZ24RandomGenerator_set_seedvE4flag, align 1
  br i1 %1, label %5, label %2

2:                                                ; preds = %0
  %3 = tail call i64 @time(ptr noundef null) #10
  %4 = trunc i64 %3 to i32
  tail call void @srand(i32 noundef %4) #10
  br label %5

5:                                                ; preds = %0, %2
  store i1 true, ptr @_ZZ24RandomGenerator_set_seedvE4flag, align 1
  %6 = tail call i32 @rand() #10
  ret i32 %6
}

; Function Attrs: nounwind
declare i32 @rand() local_unnamed_addr #1

; Function Attrs: mustprogress nounwind uwtable
define dso_local void @_Z14GameOfLifeInitP10GameOfLife(ptr nocapture noundef writeonly %0) local_unnamed_addr #0 {
  br label %2

2:                                                ; preds = %1, %6
  %3 = phi i64 [ 0, %1 ], [ %7, %6 ]
  %4 = mul nuw nsw i64 %3, 120
  br label %9

5:                                                ; preds = %6
  ret void

6:                                                ; preds = %15
  %7 = add nuw nsw i64 %3, 1
  %8 = icmp eq i64 %7, 80
  br i1 %8, label %5, label %2, !llvm.loop !5

9:                                                ; preds = %2, %15
  %10 = phi i64 [ 0, %2 ], [ %22, %15 ]
  %11 = load i1, ptr @_ZZ24RandomGenerator_set_seedvE4flag, align 1
  br i1 %11, label %15, label %12

12:                                               ; preds = %9
  %13 = tail call i64 @time(ptr noundef null) #10
  %14 = trunc i64 %13 to i32
  tail call void @srand(i32 noundef %14) #10
  br label %15

15:                                               ; preds = %9, %12
  store i1 true, ptr @_ZZ24RandomGenerator_set_seedvE4flag, align 1
  %16 = tail call noundef i32 @rand() #10
  %17 = add nuw nsw i64 %10, %4
  %18 = getelementptr inbounds nuw [9600 x i8], ptr %0, i64 0, i64 %17
  %19 = trunc i32 %16 to i8
  %20 = and i8 %19, 1
  %21 = xor i8 %20, 1
  store i8 %21, ptr %18, align 1, !tbaa !7
  %22 = add nuw nsw i64 %10, 1
  %23 = icmp eq i64 %22, 120
  br i1 %23, label %6, label %9, !llvm.loop !11
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #2

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #2

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define dso_local noundef range(i32 0, 9) i32 @_Z23GameOfLifeGetAliveCellsP10GameOfLifeii(ptr nocapture noundef readonly %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #3 {
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
define dso_local void @_Z19GameOfLifeNextFieldP10GameOfLife(ptr nocapture noundef %0) local_unnamed_addr #4 {
  %2 = alloca [9600 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 9600, ptr nonnull %2) #10
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
  call void @llvm.lifetime.end.p0(i64 9600, ptr nonnull %2) #10
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
define dso_local noundef zeroext i1 @_Z18GameOfLifeGetCoordP10GameOfLifeii(ptr nocapture noundef readonly %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #3 {
  %4 = mul nsw i32 %2, 120
  %5 = add nsw i32 %4, %1
  %6 = sext i32 %5 to i64
  %7 = getelementptr inbounds [9600 x i8], ptr %0, i64 0, i64 %6
  %8 = load i8, ptr %7, align 1, !tbaa !7, !range !12, !noundef !13
  %9 = trunc nuw i8 %8 to i1
  ret i1 %9
}

; Function Attrs: mustprogress noreturn uwtable
define dso_local noundef i32 @_Z3appv() local_unnamed_addr #5 {
  %1 = alloca [9600 x i8], align 16
  %2 = alloca %struct.GameOfLife, align 1
  call void @llvm.lifetime.start.p0(i64 9600, ptr nonnull %2) #10
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 1 dereferenceable(9600) %2, i8 0, i64 9600, i1 false)
  br label %3

3:                                                ; preds = %6, %0
  %4 = phi i64 [ 0, %0 ], [ %7, %6 ]
  %5 = mul nuw nsw i64 %4, 120
  br label %9

6:                                                ; preds = %15
  %7 = add nuw nsw i64 %4, 1
  %8 = icmp eq i64 %7, 80
  br i1 %8, label %24, label %3, !llvm.loop !5

9:                                                ; preds = %15, %3
  %10 = phi i64 [ 0, %3 ], [ %22, %15 ]
  %11 = load i1, ptr @_ZZ24RandomGenerator_set_seedvE4flag, align 1
  br i1 %11, label %15, label %12

12:                                               ; preds = %9
  %13 = tail call i64 @time(ptr noundef null) #10
  %14 = trunc i64 %13 to i32
  tail call void @srand(i32 noundef %14) #10
  br label %15

15:                                               ; preds = %12, %9
  store i1 true, ptr @_ZZ24RandomGenerator_set_seedvE4flag, align 1
  %16 = tail call noundef i32 @rand() #10
  %17 = add nuw nsw i64 %10, %5
  %18 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %17
  %19 = trunc i32 %16 to i8
  %20 = and i8 %19, 1
  %21 = xor i8 %20, 1
  store i8 %21, ptr %18, align 1, !tbaa !7
  %22 = add nuw nsw i64 %10, 1
  %23 = icmp eq i64 %22, 120
  br i1 %23, label %6, label %9, !llvm.loop !11

24:                                               ; preds = %6
  call void @_Z19GameOfLifeNextFieldP10GameOfLife(ptr noundef nonnull %2)
  br label %25

25:                                               ; preds = %117, %24
  call void @llvm.lifetime.start.p0(i64 9600, ptr nonnull %1) #10
  br label %26

26:                                               ; preds = %39, %25
  %27 = phi i64 [ 0, %25 ], [ %40, %39 ]
  %28 = trunc i64 %27 to i32
  %29 = add i32 %28, 79
  %30 = urem i32 %29, 80
  %31 = mul nuw nsw i32 %30, 120
  %32 = add i32 %28, 80
  %33 = urem i32 %32, 80
  %34 = mul nuw nsw i32 %33, 120
  %35 = add i32 %28, 81
  %36 = urem i32 %35, 80
  %37 = mul nuw nsw i32 %36, 120
  %38 = mul nuw nsw i64 %27, 120
  br label %42

39:                                               ; preds = %110
  %40 = add nuw nsw i64 %27, 1
  %41 = icmp eq i64 %40, 80
  br i1 %41, label %113, label %26, !llvm.loop !14

42:                                               ; preds = %110, %26
  %43 = phi i64 [ 0, %26 ], [ %111, %110 ]
  %44 = trunc i64 %43 to i8
  %45 = add nuw i8 %44, 79
  %46 = urem i8 %45, 80
  %47 = zext nneg i8 %46 to i32
  %48 = add nuw nsw i32 %31, %47
  %49 = zext nneg i32 %48 to i64
  %50 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %49
  %51 = load i8, ptr %50, align 1, !tbaa !7, !range !12, !noundef !13
  %52 = add nuw nsw i32 %34, %47
  %53 = zext nneg i32 %52 to i64
  %54 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %53
  %55 = load i8, ptr %54, align 1, !tbaa !7, !range !12, !noundef !13
  %56 = add nuw nsw i32 %37, %47
  %57 = zext nneg i32 %56 to i64
  %58 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %57
  %59 = load i8, ptr %58, align 1, !tbaa !7, !range !12, !noundef !13
  %60 = add nuw i8 %44, 80
  %61 = urem i8 %60, 80
  %62 = zext nneg i8 %61 to i32
  %63 = add nuw nsw i32 %31, %62
  %64 = zext nneg i32 %63 to i64
  %65 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %64
  %66 = load i8, ptr %65, align 1, !tbaa !7, !range !12, !noundef !13
  %67 = add nuw nsw i32 %37, %62
  %68 = zext nneg i32 %67 to i64
  %69 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %68
  %70 = load i8, ptr %69, align 1, !tbaa !7, !range !12, !noundef !13
  %71 = add nuw i8 %44, 81
  %72 = urem i8 %71, 80
  %73 = zext nneg i8 %72 to i32
  %74 = add nuw nsw i32 %31, %73
  %75 = zext nneg i32 %74 to i64
  %76 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %75
  %77 = load i8, ptr %76, align 1, !tbaa !7, !range !12, !noundef !13
  %78 = add nuw nsw i32 %34, %73
  %79 = zext nneg i32 %78 to i64
  %80 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %79
  %81 = load i8, ptr %80, align 1, !tbaa !7, !range !12, !noundef !13
  %82 = add nuw nsw i8 %55, %51
  %83 = add nuw nsw i8 %82, %59
  %84 = add nuw nsw i8 %83, %66
  %85 = add nuw nsw i8 %84, %70
  %86 = add nuw nsw i8 %85, %77
  %87 = add nuw nsw i8 %86, %81
  %88 = zext nneg i8 %87 to i32
  %89 = add nuw nsw i32 %37, %73
  %90 = zext nneg i32 %89 to i64
  %91 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %90
  %92 = load i8, ptr %91, align 1, !tbaa !7, !range !12, !noundef !13
  %93 = zext nneg i8 %92 to i32
  %94 = add nuw nsw i32 %88, %93
  %95 = add nuw nsw i64 %43, %38
  %96 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %95
  %97 = load i8, ptr %96, align 1, !tbaa !7, !range !12, !noundef !13
  %98 = trunc nuw i8 %97 to i1
  %99 = icmp ne i32 %94, 3
  %100 = or i1 %99, %98
  br i1 %100, label %103, label %101

101:                                              ; preds = %42
  %102 = getelementptr inbounds nuw [9600 x i8], ptr %1, i64 0, i64 %95
  store i8 1, ptr %102, align 1, !tbaa !7
  br label %110

103:                                              ; preds = %42
  %104 = add nsw i32 %94, -4
  %105 = icmp ult i32 %104, -2
  %106 = and i1 %105, %98
  %107 = getelementptr inbounds nuw [9600 x i8], ptr %1, i64 0, i64 %95
  br i1 %106, label %108, label %109

108:                                              ; preds = %103
  store i8 0, ptr %107, align 1, !tbaa !7
  br label %110

109:                                              ; preds = %103
  store i8 %97, ptr %107, align 1, !tbaa !7
  br label %110

110:                                              ; preds = %109, %108, %101
  %111 = add nuw nsw i64 %43, 1
  %112 = icmp eq i64 %111, 120
  br i1 %112, label %39, label %42, !llvm.loop !15

113:                                              ; preds = %39
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(9600) %2, ptr noundef nonnull align 16 dereferenceable(9600) %1, i64 9600, i1 false), !tbaa !7
  call void @llvm.lifetime.end.p0(i64 9600, ptr nonnull %1) #10
  br label %114

114:                                              ; preds = %113, %118
  %115 = phi i64 [ 0, %113 ], [ %119, %118 ]
  %116 = trunc nuw nsw i64 %115 to i32
  br label %121

117:                                              ; preds = %118
  tail call void @_Z14Graphics_flushv()
  br label %25, !llvm.loop !16

118:                                              ; preds = %121
  %119 = add nuw nsw i64 %115, 1
  %120 = icmp eq i64 %119, 120
  br i1 %120, label %117, label %114, !llvm.loop !17

121:                                              ; preds = %114, %121
  %122 = phi i64 [ 0, %114 ], [ %130, %121 ]
  %123 = mul nuw nsw i64 %122, 120
  %124 = add nuw nsw i64 %123, %115
  %125 = getelementptr inbounds nuw [9600 x i8], ptr %2, i64 0, i64 %124
  %126 = load i8, ptr %125, align 1, !tbaa !7, !range !12, !noundef !13
  %127 = zext nneg i8 %126 to i32
  %128 = sub nsw i32 0, %127
  %129 = trunc nuw nsw i64 %122 to i32
  tail call void @_Z18Graphics_put_pixeliiij(i32 noundef %116, i32 noundef %129, i32 noundef 10, i32 noundef %128)
  %130 = add nuw nsw i64 %122, 1
  %131 = icmp eq i64 %130, 80
  br i1 %131, label %118, label %121, !llvm.loop !18
}

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #6

declare void @_Z18Graphics_put_pixeliiij(i32 noundef, i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #7

declare void @_Z14Graphics_flushv() local_unnamed_addr #7

; Function Attrs: mustprogress norecurse noreturn uwtable
define dso_local noundef i32 @main() local_unnamed_addr #8 {
  %1 = tail call noundef i32 @_Z3appv()
  unreachable
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #9

attributes #0 = { mustprogress nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #3 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { mustprogress nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { mustprogress noreturn uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #7 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #8 = { mustprogress norecurse noreturn uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #9 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #10 = { nounwind }

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
!16 = distinct !{!16, !6}
!17 = distinct !{!17, !6}
!18 = distinct !{!18, !6}
