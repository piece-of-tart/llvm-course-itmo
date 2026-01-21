#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <sim.h>

using namespace llvm;

#define WH_PROD (WIDTH * HEIGHT)

static constexpr auto kAppFuncName = "app";
static constexpr auto kNextFieldFuncName = "GameOfLifeNextField";

static constexpr auto kGraphicPutPixelFuncName = "Graphics_put_pixel";
static constexpr auto kGraphicFlushFuncName = "Graphics_flush";

FunctionType *getGraphicPutPixelTy(IRBuilder<> &builder) {
  return FunctionType::get(builder.getVoidTy(),
                           {builder.getInt32Ty(), builder.getInt32Ty(), builder.getInt32Ty(), builder.getInt32Ty()}, false);
}

Function *declareGraphicPutPixel(Module *module, IRBuilder<> &builder) {
  return Function::Create(
      getGraphicPutPixelTy(builder),
      Function::ExternalLinkage,
      kGraphicPutPixelFuncName, module);
}

FunctionType *getGraphicFlushTy(IRBuilder<> &builder) {
  return FunctionType::get(builder.getVoidTy(), false);
}

Function *declareGraphicFlush(Module *module, IRBuilder<> &builder) {
  return Function::Create(
      getGraphicFlushTy(builder),
      Function::ExternalLinkage,
      kGraphicFlushFuncName, module);
}

StructType *createGameOfLifeTy(LLVMContext &ctx) {
  static_assert(WH_PROD == 9600, "9600 in IR file");
  ArrayType *arr = ArrayType::get(Type::getInt8Ty(ctx), WH_PROD);
  StructType *game_of_life_type = StructType::create(ctx, "struct.GameOfLife");
  game_of_life_type->setBody({arr}, false);
  return game_of_life_type;
}

GlobalVariable *createRandInitNumber(Module *module) {
  LLVMContext &ctx = module->getContext();
  auto *init = ConstantInt::get(Type::getInt32Ty(ctx), -1831433054, true);
  auto *gv = new GlobalVariable(
      *module, Type::getInt32Ty(ctx), false, GlobalValue::PrivateLinkage, init, "GameOfLifeRand");
  gv->setUnnamedAddr(GlobalValue::UnnamedAddr::Global);
  gv->setAlignment(Align(4));
  return gv;
}

Function *defineAppFunction(Module *module, IRBuilder<> &builder, GlobalVariable *rand) {

  LLVMContext &ctx = module->getContext();
  StructType *game_of_life_type = createGameOfLifeTy(ctx);

  FunctionType *app_func_type = FunctionType::get(builder.getInt32Ty(), false);
  Function *app_func = Function::Create(app_func_type, Function::ExternalLinkage, kAppFuncName, module);

  auto *array_ty = ArrayType::get(builder.getInt8Ty(), WH_PROD);

  BasicBlock *bb_0 = BasicBlock::Create(ctx, "bb_0", app_func);
  BasicBlock *bb_4 = BasicBlock::Create(ctx, "bb_4", app_func);
  BasicBlock *bb_8 = BasicBlock::Create(ctx, "bb_8", app_func);
  BasicBlock *bb_11 = BasicBlock::Create(ctx, "bb_11", app_func);
  BasicBlock *bb_39 = BasicBlock::Create(ctx, "bb_39", app_func);
  BasicBlock *bb_40 = BasicBlock::Create(ctx, "bb_40", app_func);
  BasicBlock *bb_41 = BasicBlock::Create(ctx, "bb_41", app_func);
  BasicBlock *bb_54 = BasicBlock::Create(ctx, "bb_54", app_func);
  BasicBlock *bb_57 = BasicBlock::Create(ctx, "bb_57", app_func);
  BasicBlock *bb_116 = BasicBlock::Create(ctx, "bb_116", app_func);
  BasicBlock *bb_118 = BasicBlock::Create(ctx, "bb_118", app_func);
  BasicBlock *bb_123 = BasicBlock::Create(ctx, "bb_123", app_func);
  BasicBlock *bb_124 = BasicBlock::Create(ctx, "bb_124", app_func);
  BasicBlock *bb_125 = BasicBlock::Create(ctx, "bb_125", app_func);
  BasicBlock *bb_128 = BasicBlock::Create(ctx, "bb_128", app_func);
  BasicBlock *bb_129 = BasicBlock::Create(ctx, "bb_129", app_func);
  BasicBlock *bb_132 = BasicBlock::Create(ctx, "bb_132", app_func);
  BasicBlock *bb_133 = BasicBlock::Create(ctx, "bb_133", app_func);
  BasicBlock *bb_136 = BasicBlock::Create(ctx, "bb_136", app_func);

  // BB0
  builder.SetInsertPoint(bb_0);
  auto *alloca_1 = builder.CreateAlloca(ArrayType::get(Type::getInt8Ty(ctx), WH_PROD), nullptr, "");
  alloca_1->setAlignment(Align(16));
  auto *alloca_2 = builder.CreateAlloca(game_of_life_type, nullptr, "");
  builder.CreateLifetimeStart(alloca_2, builder.getInt64(WH_PROD));
  builder.CreateMemSet(alloca_2, builder.getInt8(0), builder.getInt64(WH_PROD), Align(1));
  auto *load_3 = builder.CreateLoad(rand->getValueType(), rand, "");// to avoid optimization out
  builder.CreateBr(bb_4);

  // BB4
  builder.SetInsertPoint(bb_4);
  auto *phi_5 = builder.CreatePHI(builder.getInt64Ty(), 2, "");
  auto *phi_6 = builder.CreatePHI(builder.getInt32Ty(), 2, "");
  auto *mul_7 = builder.CreateMul(phi_5, builder.getInt64(120), "", true, true);
  builder.CreateBr(bb_11);

  // BB8
  builder.SetInsertPoint(bb_8);
  auto *add_9 = builder.CreateAdd(phi_5, builder.getInt64(1), "", true, true);
  auto *icmp_10 = builder.CreateICmpEQ(add_9, builder.getInt64(80), "");
  builder.CreateCondBr(icmp_10, bb_39, bb_4);

  // BB11
  builder.SetInsertPoint(bb_11);
  auto *phi_12 = builder.CreatePHI(builder.getInt64Ty(), 2, "");
  auto *phi_13 = builder.CreatePHI(builder.getInt32Ty(), 2, "");
  auto *add_14 = builder.CreateAdd(phi_12, mul_7, "", true, true);
  auto *getelemntptr_15 = builder.CreateInBoundsGEP(array_ty, alloca_2, {builder.getInt64(0), add_14}, "");
  cast<GetElementPtrInst>(getelemntptr_15)->setIsInBounds(true);
  cast<GetElementPtrInst>(getelemntptr_15)->setNoWrapFlags(GEPNoWrapFlags::noUnsignedWrap());
  auto *trunc_16 = builder.CreateTrunc(phi_13, builder.getInt8Ty(), "");
  auto *and_17 = builder.CreateAnd(trunc_16, builder.getInt8(1), "");
  auto *xor_18 = builder.CreateXor(and_17, builder.getInt8(1), "");
  builder.CreateStore(xor_18, getelemntptr_15, false);
  auto *shl_19 = builder.CreateShl(phi_13, builder.getInt32(13), "", false, false);
  auto *xor_20 = builder.CreateXor(shl_19, phi_13, "");
  auto *ashr_21 = builder.CreateAShr(xor_20, builder.getInt32(17), "", false);
  auto *xor_22 = builder.CreateXor(ashr_21, xor_20, "");
  auto *shl_23 = builder.CreateShl(xor_22, builder.getInt32(5), "", false, false);
  auto *xor_24 = builder.CreateXor(shl_23, xor_22, "");
  auto *or_25 = builder.CreateOr(phi_12, builder.getInt64(1), "");
  cast<PossiblyDisjointInst>(or_25)->setIsDisjoint(true);
  auto *add_26 = builder.CreateAdd(or_25, mul_7, "", true, true);
  auto *getelementptr_27 = builder.CreateInBoundsGEP(array_ty, alloca_2, {builder.getInt64(0), add_26}, "");
  cast<GetElementPtrInst>(getelementptr_27)->setIsInBounds(true);
  cast<GetElementPtrInst>(getelementptr_27)->setNoWrapFlags(GEPNoWrapFlags::noUnsignedWrap());
  auto *trunc_28 = builder.CreateTrunc(xor_22, builder.getInt8Ty(), "");
  auto *and_29 = builder.CreateAnd(trunc_28, builder.getInt8(1), "");
  auto *xor_30 = builder.CreateXor(and_29, builder.getInt8(1), "");
  builder.CreateStore(xor_30, getelementptr_27, false);
  auto *shl_31 = builder.CreateShl(xor_24, builder.getInt32(13), "");
  auto *xor_32 = builder.CreateXor(shl_31, xor_24, "");
  auto *ashr_33 = builder.CreateAShr(xor_32, builder.getInt32(17), "");
  auto *xor_34 = builder.CreateXor(ashr_33, xor_32, "");
  auto *shl_35 = builder.CreateShl(xor_34, builder.getInt32(5), "");
  auto *xor_36 = builder.CreateXor(shl_35, xor_34, "");
  auto *add_37 = builder.CreateAdd(phi_12, builder.getInt64(2), "", true, true);
  auto *icmp_38 = builder.CreateICmpEQ(add_37, builder.getInt64(120), "");
  builder.CreateCondBr(icmp_38, bb_8, bb_11);

  // BB39
  builder.SetInsertPoint(bb_39);
  builder.CreateStore(xor_36, rand, false);
  FunctionType *game_of_life_next_field_type = FunctionType::get(builder.getVoidTy(), {PointerType::get(ctx, 0)}, false);
  FunctionCallee game_of_life_next_field_func = module->getOrInsertFunction(kNextFieldFuncName, game_of_life_next_field_type);
  builder.CreateCall(game_of_life_next_field_func, {alloca_2});
  builder.CreateBr(bb_40);

  // BB40
  builder.SetInsertPoint(bb_40);
  builder.CreateLifetimeStart(alloca_1, builder.getInt64(WH_PROD));
  builder.CreateBr(bb_41);

  // BB41
  builder.SetInsertPoint(bb_41);
  auto *phi_42 = builder.CreatePHI(builder.getInt64Ty(), 2, "");
  auto *trunc_43 = builder.CreateTrunc(phi_42, builder.getInt32Ty(), "");
  auto *add_44 = builder.CreateAdd(trunc_43, builder.getInt32(79), "");
  auto *urem_45 = builder.CreateURem(add_44, builder.getInt32(80), "");
  auto *mul_46 = builder.CreateMul(urem_45, builder.getInt32(120), "", true, true);
  auto *add_47 = builder.CreateAdd(trunc_43, builder.getInt32(80), "");
  auto *urem_48 = builder.CreateURem(add_47, builder.getInt32(80), "");
  auto *mul_49 = builder.CreateMul(urem_48, builder.getInt32(120), "", true, true);
  auto *add_50 = builder.CreateAdd(trunc_43, builder.getInt32(81), "");
  auto *urem_51 = builder.CreateURem(add_50, builder.getInt32(80), "");
  auto *mul_52 = builder.CreateMul(urem_51, builder.getInt32(120), "", true, true);
  auto *mul_53 = builder.CreateMul(phi_42, builder.getInt64(120), "", true, true);
  builder.CreateBr(bb_57);

  // BB54
  builder.SetInsertPoint(bb_54);
  auto *add_55 = builder.CreateAdd(phi_42, builder.getInt64(1), "", true, true);
  auto *icmp_56 = builder.CreateICmp(CmpInst::Predicate::ICMP_EQ, add_55, builder.getInt64(80));
  builder.CreateCondBr(icmp_56, bb_128, bb_41);

  // BB57
  builder.SetInsertPoint(bb_57);
  auto *phi_58 = builder.CreatePHI(builder.getInt64Ty(), 2, "");
  auto *trunc_59 = builder.CreateTrunc(phi_58, builder.getInt8Ty(), "");
  auto *add_60 = builder.CreateAdd(trunc_59, builder.getInt8(79), "");
  auto *urem_61 = builder.CreateURem(add_60, builder.getInt8(80), "");
  auto *zext_62 = builder.CreateZExt(urem_61, builder.getInt32Ty(), "", true);
  auto *add_63 = builder.CreateAdd(mul_46, zext_62, "", true, true);
  auto *zext_64 = builder.CreateZExt(add_63, builder.getInt64Ty(), "", true);
  auto *getelementptr_65 = builder.CreateInBoundsGEP(array_ty, alloca_2, {builder.getInt64(0), zext_64}, "");
  auto *load_66 = builder.CreateLoad(builder.getInt8Ty(), getelementptr_65, "");
  auto *add_67 = builder.CreateAdd(mul_49, zext_62, "", true, true);
  auto *zext_68 = builder.CreateZExt(add_67, builder.getInt64Ty(), "", true);
  auto *getelementptr_69 = builder.CreateInBoundsGEP(array_ty, alloca_2, {builder.getInt64(0), zext_68}, "");
  auto *load_70 = builder.CreateLoad(builder.getInt8Ty(), getelementptr_69, "");
  auto *add_71 = builder.CreateAdd(mul_52, zext_62, "", true, true);
  auto *zext_72 = builder.CreateZExt(add_71, builder.getInt64Ty(), "", true);
  auto *getelementptr_73 = builder.CreateInBoundsGEP(array_ty, alloca_2, {builder.getInt64(0), zext_72}, "");
  auto *load_74 = builder.CreateLoad(builder.getInt8Ty(), getelementptr_73, "");
  auto *add_75 = builder.CreateAdd(trunc_59, builder.getInt8(80), "", true, true);
  auto *urem_76 = builder.CreateURem(add_75, builder.getInt8(80));
  auto *zext_77 = builder.CreateZExt(urem_76, builder.getInt32Ty(), "", true);
  auto *add_78 = builder.CreateAdd(mul_46, zext_77, "", true, true);
  auto *zext_79 = builder.CreateZExt(add_78, builder.getInt64Ty(), "", true);
  auto *getelementptr_80 = builder.CreateInBoundsGEP(array_ty, alloca_2, {builder.getInt64(0), zext_79}, "");
  auto *load_81 = builder.CreateLoad(builder.getInt8Ty(), getelementptr_80, "");
  auto *add_82 = builder.CreateAdd(mul_52, zext_77, "", true, true);
  auto *zext_83 = builder.CreateZExt(add_82, builder.getInt64Ty(), "", true);
  auto *getelementptr_84 = builder.CreateInBoundsGEP(array_ty, alloca_2, {builder.getInt64(0), zext_83}, "");
  auto *load_85 = builder.CreateLoad(builder.getInt8Ty(), getelementptr_84);
  auto *add_86 = builder.CreateAdd(trunc_59, builder.getInt8(81), "", true);
  auto *urem_87 = builder.CreateURem(add_86, builder.getInt8(80));
  auto *zext_88 = builder.CreateZExt(urem_87, builder.getInt32Ty(), "", true);
  auto *add_89 = builder.CreateAdd(mul_46, zext_88, "", true, true);
  auto *zext_90 = builder.CreateZExt(add_89, builder.getInt64Ty(), "", true);
  auto *getelementptr_91 = builder.CreateInBoundsGEP(array_ty, alloca_2, {builder.getInt64(0), zext_90});
  auto *load_92 = builder.CreateLoad(builder.getInt8Ty(), getelementptr_91);
  auto *add_93 = builder.CreateAdd(mul_49, zext_88, "", true, true);
  auto *zext_94 = builder.CreateZExt(add_93, builder.getInt64Ty(), "", true);
  auto *getelementptr_95 = builder.CreateInBoundsGEP(array_ty, alloca_2, {builder.getInt64(0), zext_94});
  auto *load_96 = builder.CreateLoad(builder.getInt8Ty(), getelementptr_95);
  auto *add_97 = builder.CreateAdd(load_70, load_66, "", true, true);
  auto *add_98 = builder.CreateAdd(add_97, load_74, "", true, true);
  auto *add_99 = builder.CreateAdd(add_98, load_81, "", true, true);
  auto *add_100 = builder.CreateAdd(add_99, load_85, "", true, true);
  auto *add_101 = builder.CreateAdd(add_100, load_92, "", true, true);
  auto *add_102 = builder.CreateAdd(add_101, load_96, "", true, true);
  auto *zext_103 = builder.CreateZExt(add_102, builder.getInt32Ty(), "", true);
  auto *add_104 = builder.CreateAdd(mul_52, zext_88, "", true, true);
  auto *zext_105 = builder.CreateZExt(add_104, builder.getInt64Ty(), "", true);
  auto *getelementptr_106 = builder.CreateInBoundsGEP(array_ty, alloca_2, {builder.getInt64(0), zext_105});
  auto *load_107 = builder.CreateLoad(builder.getInt8Ty(), getelementptr_106);
  auto *zext_108 = builder.CreateZExt(load_107, builder.getInt32Ty(), "", true);
  auto *add_109 = builder.CreateAdd(zext_103, zext_108, "", true, true);
  auto *add_110 = builder.CreateAdd(phi_58, mul_53, "", true, true);
  auto *getelementptr_111 = builder.CreateInBoundsGEP(array_ty, alloca_2, {builder.getInt64(0), add_110});
  auto *load_112 = builder.CreateLoad(builder.getInt8Ty(), getelementptr_111);
  auto *trunc_113 = builder.CreateTrunc(load_112, builder.getInt1Ty(), "", true);
  auto *icmp_114 = builder.CreateICmp(CmpInst::Predicate::ICMP_NE, add_109, builder.getInt32(3));
  auto *or_115 = builder.CreateOr(icmp_114, trunc_113);
  builder.CreateCondBr(or_115, bb_118, bb_116);

  // BB116
  builder.SetInsertPoint(bb_116);
  auto *getelementptr_117 = builder.CreateInBoundsGEP(array_ty, alloca_1, {builder.getInt64(0), add_110});
  builder.CreateStore(builder.getInt8(1), getelementptr_117);
  builder.CreateBr(bb_125);

  // BB118
  builder.SetInsertPoint(bb_118);
  auto *add_119 = builder.CreateAdd(add_109, builder.getInt32(-4), "", false, true);
  auto *icmp_120 = builder.CreateICmp(CmpInst::Predicate::ICMP_ULT, add_119, builder.getInt32(-2));
  auto *and_121 = builder.CreateAnd(icmp_120, trunc_113);
  auto *getelementptr_122 = builder.CreateInBoundsGEP(array_ty, alloca_1, {builder.getInt64(0), add_110});
  builder.CreateCondBr(and_121, bb_123, bb_124);

  // BB123
  builder.SetInsertPoint(bb_123);
  builder.CreateStore(builder.getInt8(0), getelementptr_122);
  builder.CreateBr(bb_125);

  // BB124
  builder.SetInsertPoint(bb_124);
  builder.CreateStore(load_112, getelementptr_122);
  builder.CreateBr(bb_125);

  // BB125
  builder.SetInsertPoint(bb_125);
  auto *add_126 = builder.CreateAdd(phi_58, builder.getInt64(1), "", true, true);
  auto *icmp_127 = builder.CreateICmp(CmpInst::Predicate::ICMP_EQ, add_126, builder.getInt64(120));
  builder.CreateCondBr(icmp_127, bb_54, bb_57);

  // BB128
  builder.SetInsertPoint(bb_128);
  builder.CreateMemCpy(alloca_2, Align(1), alloca_1, Align(16), builder.getInt64(WH_PROD), false);
  builder.CreateLifetimeEnd(alloca_1, builder.getInt64(WH_PROD));
  builder.CreateBr(bb_129);

  // BB129
  builder.SetInsertPoint(bb_129);
  auto *phi_130 = builder.CreatePHI(builder.getInt64Ty(), 2);
  auto *trunc_131 = builder.CreateTrunc(phi_130, builder.getInt32Ty(), "", true, true);
  builder.CreateBr(bb_136);

  // BB132
  builder.SetInsertPoint(bb_132);
  builder.CreateCall(module->getOrInsertFunction(kGraphicFlushFuncName, getGraphicFlushTy(builder)));
  builder.CreateBr(bb_40);

  // BB133
  builder.SetInsertPoint(bb_133);
  auto *add_134 = builder.CreateAdd(phi_130, builder.getInt64(1), "", true, true);
  auto *icmp_135 = builder.CreateICmp(CmpInst::Predicate::ICMP_EQ, add_134, builder.getInt64(120));
  builder.CreateCondBr(icmp_135, bb_132, bb_129);

  // BB136
  builder.SetInsertPoint(bb_136);
  auto *phi_137 = builder.CreatePHI(builder.getInt64Ty(), 2);
  auto *mul_138 = builder.CreateMul(phi_137, builder.getInt64(120), "", true, true);
  auto *add_139 = builder.CreateAdd(mul_138, phi_130, "", true, true);
  auto *getelementptr_140 = builder.CreateInBoundsGEP(array_ty, alloca_2, {builder.getInt64(0), add_139});
  auto *load_141 = builder.CreateLoad(builder.getInt8Ty(), getelementptr_140);
  auto *zext_142 = builder.CreateZExt(load_141, builder.getInt32Ty(), "", true);
  auto *sub_143 = builder.CreateSub(builder.getInt32(0), zext_142, "", false, true);
  auto *trunc_144 = builder.CreateTrunc(phi_137, builder.getInt32Ty(), "", true, true);
  // TODO: add tail to 'call'
  builder.CreateCall(module->getOrInsertFunction(kGraphicPutPixelFuncName, getGraphicPutPixelTy(builder)), {trunc_131, trunc_144, builder.getInt32(10), sub_143});
  auto *add_145 = builder.CreateAdd(phi_137, builder.getInt64(1), "", true, true);
  auto *icmp_146 = builder.CreateICmp(CmpInst::Predicate::ICMP_EQ, add_145, builder.getInt64(80));
  builder.CreateCondBr(icmp_146, bb_133, bb_136);

  // Link PHI instructions
  phi_5->addIncoming(builder.getInt64(0), bb_0);
  phi_5->addIncoming(add_9, bb_8);
  phi_6->addIncoming(load_3, bb_0);
  phi_6->addIncoming(xor_36, bb_8);
  phi_12->addIncoming(builder.getInt64(0), bb_4);
  phi_12->addIncoming(add_37, bb_11);
  phi_13->addIncoming(phi_6, bb_4);
  phi_13->addIncoming(xor_36, bb_11);
  phi_42->addIncoming(builder.getInt64(0), bb_40);
  phi_42->addIncoming(add_55, bb_54);
  phi_58->addIncoming(builder.getInt64(0), bb_41);
  phi_58->addIncoming(add_126, bb_125);
  phi_130->addIncoming(builder.getInt64(0), bb_128);
  phi_130->addIncoming(add_134, bb_133);
  phi_137->addIncoming(builder.getInt64(0), bb_129);
  phi_137->addIncoming(add_145, bb_136);

  return app_func;
}

Function *defineNextFieldFunction(Module *module, IRBuilder<> &builder) {
  LLVMContext &ctx = module->getContext();

  FunctionType *func_type = FunctionType::get(builder.getVoidTy(), {PointerType::get(ctx, 0)}, false);
  Function *func = Function::Create(func_type, Function::InternalLinkage, kNextFieldFuncName, module);

  auto *array_ty = ArrayType::get(builder.getInt8Ty(), WH_PROD);

  BasicBlock *bb_1 = BasicBlock::Create(ctx, "bb_1", func);
  BasicBlock *bb_3 = BasicBlock::Create(ctx, "bb_3", func);
  BasicBlock *bb_18 = BasicBlock::Create(ctx, "bb_18", func);
  BasicBlock *bb_21 = BasicBlock::Create(ctx, "bb_21", func);
  BasicBlock *bb_22 = BasicBlock::Create(ctx, "bb_22", func);
  BasicBlock *bb_81 = BasicBlock::Create(ctx, "bb_81", func);
  BasicBlock *bb_83 = BasicBlock::Create(ctx, "bb_83", func);
  BasicBlock *bb_88 = BasicBlock::Create(ctx, "bb_88", func);
  BasicBlock *bb_89 = BasicBlock::Create(ctx, "bb_89", func);
  BasicBlock *bb_90 = BasicBlock::Create(ctx, "bb_90", func);

  Argument *reg_0 = func->getArg(0);

  // BB1
  builder.SetInsertPoint(bb_1);
  auto *reg_2 = builder.CreateAlloca(array_ty);
  reg_2->setAlignment(Align(16));
  builder.CreateLifetimeStart(reg_2, builder.getInt64(WH_PROD));
  builder.CreateBr(bb_3);

  // BB3
  builder.SetInsertPoint(bb_3);
  auto *reg_4 = builder.CreatePHI(builder.getInt64Ty(), 2);
  auto *reg_5 = builder.CreateTrunc(reg_4, builder.getInt32Ty());
  auto *reg_6 = builder.CreateAdd(reg_5, builder.getInt32(79));
  auto *reg_7 = builder.CreateURem(reg_6, builder.getInt32(80));
  auto *reg_8 = builder.CreateMul(reg_7, builder.getInt32(120), "", true, true);
  auto *reg_9 = builder.CreateTrunc(reg_4, builder.getInt32Ty());
  auto *reg_10 = builder.CreateAdd(reg_9, builder.getInt32(80));
  auto *reg_11 = builder.CreateURem(reg_10, builder.getInt32(80));
  auto *reg_12 = builder.CreateMul(reg_11, builder.getInt32(120), "", true, true);
  auto *reg_13 = builder.CreateTrunc(reg_4, builder.getInt32Ty());
  auto *reg_14 = builder.CreateAdd(reg_13, builder.getInt32(81));
  auto *reg_15 = builder.CreateURem(reg_14, builder.getInt32(80));
  auto *reg_16 = builder.CreateMul(reg_15, builder.getInt32(120), "", true, true);
  auto *reg_17 = builder.CreateMul(reg_4, builder.getInt64(120), "", true, true);
  builder.CreateBr(bb_22);

  // BB18
  builder.SetInsertPoint(bb_18);
  auto *reg_19 = builder.CreateAdd(reg_4, builder.getInt64(1), "", true, true);
  auto *reg_20 = builder.CreateICmpEQ(reg_19, builder.getInt64(80));
  builder.CreateCondBr(reg_20, bb_21, bb_3);

  // BB21
  builder.SetInsertPoint(bb_21);
  builder.CreateMemCpy(reg_0, Align(1), reg_2, Align(16), builder.getInt64(WH_PROD));
  builder.CreateLifetimeEnd(reg_2, builder.getInt64(WH_PROD));
  builder.CreateRetVoid();

  // BB22
  builder.SetInsertPoint(bb_22);
  auto *reg_23 = builder.CreatePHI(builder.getInt64Ty(), 2);
  auto *reg_24 = builder.CreateTrunc(reg_23, builder.getInt8Ty());
  auto *reg_25 = builder.CreateAdd(reg_24, builder.getInt8(80), "", true, false);
  auto *reg_26 = builder.CreateURem(reg_25, builder.getInt8(80));
  auto *reg_27 = builder.CreateZExt(reg_26, builder.getInt32Ty(), "", true);
  auto *reg_28 = builder.CreateAdd(reg_8, reg_27, "", true, true);
  auto *reg_29 = builder.CreateZExt(reg_28, builder.getInt64Ty(), "", true);
  auto *reg_30 = builder.CreateInBoundsGEP(array_ty, reg_0, {builder.getInt64(0), reg_29});
  auto *reg_31 = builder.CreateLoad(builder.getInt8Ty(), reg_30);
  auto *reg_32 = builder.CreateAdd(reg_12, reg_27, "", true, true);
  auto *reg_33 = builder.CreateZExt(reg_32, builder.getInt64Ty(), "", true);
  auto *reg_34 = builder.CreateInBoundsGEP(array_ty, reg_0, {builder.getInt64(0), reg_33});
  auto *reg_35 = builder.CreateLoad(builder.getInt8Ty(), reg_34);
  auto *reg_36 = builder.CreateAdd(reg_16, reg_27, "", true, true);
  auto *reg_37 = builder.CreateZExt(reg_36, builder.getInt64Ty(), "", true);
  auto *reg_38 = builder.CreateInBoundsGEP(array_ty, reg_0, {builder.getInt64(0), reg_37});
  auto *reg_39 = builder.CreateLoad(builder.getInt8Ty(), reg_38);
  auto *reg_40 = builder.CreateAdd(reg_24, builder.getInt8(80), "", true, false);
  auto *reg_41 = builder.CreateURem(reg_40, builder.getInt8(80));
  auto *reg_42 = builder.CreateZExt(reg_41, builder.getInt32Ty(), "", true);
  auto *reg_43 = builder.CreateAdd(reg_8, reg_42, "", true, true);
  auto *reg_44 = builder.CreateZExt(reg_43, builder.getInt64Ty(), "", true);
  auto *reg_45 = builder.CreateInBoundsGEP(array_ty, reg_0, {builder.getInt64(0), reg_44});
  auto *reg_46 = builder.CreateLoad(builder.getInt8Ty(), reg_45);
  auto *reg_47 = builder.CreateAdd(reg_16, reg_42, "", true, true);
  auto *reg_48 = builder.CreateZExt(reg_47, builder.getInt64Ty(), "", true);
  auto *reg_49 = builder.CreateInBoundsGEP(array_ty, reg_0, {builder.getInt64(0), reg_48});
  auto *reg_50 = builder.CreateLoad(builder.getInt8Ty(), reg_49);
  auto *reg_51 = builder.CreateAdd(reg_24, builder.getInt8(81));
  auto *reg_52 = builder.CreateURem(reg_51, builder.getInt8(80));
  auto *reg_53 = builder.CreateZExt(reg_52, builder.getInt32Ty(), "", true);
  auto *reg_54 = builder.CreateAdd(reg_8, reg_53, "", true, true);
  auto *reg_55 = builder.CreateZExt(reg_54, builder.getInt64Ty(), "", true);
  auto *reg_56 = builder.CreateInBoundsGEP(array_ty, reg_0, {builder.getInt64(0), reg_55});
  auto *reg_57 = builder.CreateLoad(builder.getInt8Ty(), reg_56);
  auto *reg_58 = builder.CreateAdd(reg_12, reg_53, "", true, true);
  auto *reg_59 = builder.CreateZExt(reg_58, builder.getInt64Ty(), "", true);
  auto *reg_60 = builder.CreateInBoundsGEP(array_ty, reg_0, {builder.getInt64(0), reg_59});
  auto *reg_61 = builder.CreateLoad(builder.getInt8Ty(), reg_60);
  auto *reg_62 = builder.CreateAdd(reg_35, reg_31, "", true, true);
  auto *reg_63 = builder.CreateAdd(reg_62, reg_39, "", true, true);
  auto *reg_64 = builder.CreateAdd(reg_63, reg_46, "", true, true);
  auto *reg_65 = builder.CreateAdd(reg_64, reg_50, "", true, true);
  auto *reg_66 = builder.CreateAdd(reg_65, reg_57, "", true, true);
  auto *reg_67 = builder.CreateAdd(reg_66, reg_61, "", true, true);
  auto *reg_68 = builder.CreateZExt(reg_67, builder.getInt32Ty(), "", true);
  auto *reg_69 = builder.CreateAdd(reg_16, reg_53, "", true, true);
  auto *reg_70 = builder.CreateZExt(reg_69, builder.getInt64Ty(), "", true);
  auto *reg_71 = builder.CreateInBoundsGEP(array_ty, reg_0, {builder.getInt64(0), reg_70});
  auto *reg_72 = builder.CreateLoad(builder.getInt8Ty(), reg_71);
  auto *reg_73 = builder.CreateZExt(reg_72, builder.getInt32Ty(), "", true);
  auto *reg_74 = builder.CreateAdd(reg_68, reg_73, "", true, true);
  auto *reg_75 = builder.CreateAdd(reg_23, reg_17, "", true, true);
  auto *reg_76 = builder.CreateInBoundsGEP(array_ty, reg_0, {builder.getInt64(0), reg_75});
  auto *reg_77 = builder.CreateLoad(builder.getInt8Ty(), reg_76);
  auto *reg_78 = builder.CreateTrunc(reg_77, builder.getInt8Ty(), "", true, false);
  auto *reg_79 = builder.CreateICmpNE(reg_74, builder.getInt32(3));
  auto *reg_80 = builder.CreateOr(reg_79, reg_78);
  builder.CreateCondBr(reg_80, bb_83, bb_81);

  // BB81
  builder.SetInsertPoint(bb_81);
  auto *reg_82 = builder.CreateInBoundsGEP(array_ty, reg_2, {builder.getInt64(0), reg_75});
  builder.CreateStore(builder.getInt8(1), reg_82);
  builder.CreateBr(bb_90);

  // BB83
  builder.SetInsertPoint(bb_83);
  auto *reg_84 = builder.CreateAdd(reg_74, builder.getInt32(-4), "", false, true);
  auto *reg_85 = builder.CreateICmpULT(reg_84, builder.getInt32(-2));
  auto *reg_86 = builder.CreateAnd(reg_85, reg_78);
  auto *reg_87 = builder.CreateInBoundsGEP(array_ty, reg_2, {builder.getInt64(0), reg_75});
  builder.CreateCondBr(reg_86, bb_88, bb_89);

  // BB88
  builder.SetInsertPoint(bb_88);
  builder.CreateStore(builder.getInt8(0), reg_87);
  builder.CreateBr(bb_90);

  // BB89
  builder.SetInsertPoint(bb_89);
  builder.CreateStore(reg_77, reg_87);
  builder.CreateBr(bb_90);

  // BB90
  builder.SetInsertPoint(bb_90);
  auto *reg_91 = builder.CreateAdd(reg_23, builder.getInt64(1), "", true, true);
  auto *reg_92 = builder.CreateICmpEQ(reg_91, builder.getInt64(120));
  builder.CreateCondBr(reg_92, bb_18, bb_22);

  // Link PHI instructions
  reg_4->addIncoming(builder.getInt64(0), bb_1);
  reg_4->addIncoming(reg_19, bb_18);
  reg_23->addIncoming(builder.getInt64(0), bb_3);
  reg_23->addIncoming(reg_91, bb_90);

  return func;
}

int main() {
  LLVMContext context;
  Module *module = new Module("app", context);
  IRBuilder<> builder(context);

  Function *graphic_put_pixel = declareGraphicPutPixel(module, builder);
  Function *graphic_flush = declareGraphicFlush(module, builder);
  [[maybe_unused]] StructType *game_of_life_type = createGameOfLifeTy(context);
  GlobalVariable *rand_init_number = createRandInitNumber(module);
  [[maybe_unused]] Function *next_field = defineNextFieldFunction(module, builder);
  Function *app = defineAppFunction(module, builder, rand_init_number);

  // Dump LLVM IR
  module->print(outs(), nullptr);
  outs() << '\n';
  bool verif = verifyFunction(*app, &outs());
  outs() << "[VERIFICATION] " << (verif ? "FAIL\n\n" : "OK\n\n");

  // LLVM IR Interpreter
  outs() << "[EE] Run\n";
  InitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();
  LLVMLinkInInterpreter();

  std::string err;
  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module))
                            .setErrorStr(&err)
                            .create();
  if (!ee) {
    errs() << "EngineBuilder::create() failed: " << err << "\n";
    return 1;
  }
  ee->addGlobalMapping(graphic_put_pixel, (void *) &Graphics_put_pixel);
  ee->addGlobalMapping(graphic_flush, (void *) &Graphics_flush);
  ee->finalizeObject();
  ArrayRef<GenericValue> noargs;
  ee->runFunction(app, noargs);
  return 0;
}
