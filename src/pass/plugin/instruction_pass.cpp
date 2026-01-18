#include "llvm/IR/ModuleSlotTracker.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Pass.h>
#include <llvm/Passes/OptimizationLevel.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>

using namespace llvm;

struct InstructionPass : public PassInfoMixin<InstructionPass> {
  static constexpr auto kLogFuncName = "logInstruction2";

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    outs() << "[Module] " << M.getName() << '\n';

    LLVMContext &ctx = M.getContext();
    IRBuilder<> builder(ctx);

    Type *void_type = Type::getVoidTy(ctx);
    Type *i8_ptr_type = PointerType::get(ctx, 0);

    FunctionType *log_func_type =
        FunctionType::get(void_type, {i8_ptr_type, i8_ptr_type}, false);
    FunctionCallee log_func =
        M.getOrInsertFunction(kLogFuncName, log_func_type);

    ModuleSlotTracker MST(&M);

    for (auto &F : M) {
      if (F.getName() == kLogFuncName || F.isDeclaration()) {
        continue;
      }
      MST.incorporateFunction(F);
      for (auto &B : F) {
        for (auto &I : B) {
          if (auto i = dyn_cast<PHINode>(&I); i != nullptr) {
            continue;
          }

          auto *i_name = builder.CreateGlobalString(I.getOpcodeName(), "", 0, &M);

          SmallVector<Instruction *, 16> uses;
          for (auto &use : I.uses()) {
            if (auto i_use = dyn_cast<Instruction>(use.getUser()); i_use == nullptr) {
              continue;
            } else if (auto i_phi_node = dyn_cast<PHINode>(i_use); i_phi_node != nullptr) {
              continue;
            } else {
              uses.push_back(i_use);
            }
          }
          const auto kUsesCmp = [&](Instruction *left, Instruction *right) -> bool {
            if (left->getParent() != right->getParent()) {
              return MST.getLocalSlot(left->getParent()) < MST.getLocalSlot(right->getParent());
            }
            return left->comesBefore(right);
          };

          llvm::sort(uses, kUsesCmp);

          for (auto &use : uses) {
            builder.SetInsertPoint(use);
            auto *use_name = builder.CreateGlobalString(use->getOpcodeName(), "", 0, &M);
            Value *args[] = {use_name, i_name};
            builder.CreateCall(log_func, args);
          }
        }
      }
    }
    return PreservedAnalyses::none();
  };
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerOptimizerLastEPCallback([](ModulePassManager &MPM, OptimizationLevel, ThinOrFullLTOPhase) {
      MPM.addPass(InstructionPass{});
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "MyPlugin", "0.0.1", callback};
};

/* When a plugin is loaded by the driver, it will call this entry point to
obtain information about this plugin and about how to register its passes.
*/
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
