//===--- BackendUtil.h - LLVM Backend Utilities -----------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_CODEGEN_BACKENDUTIL_H
#define LLVM_CLANG_CODEGEN_BACKENDUTIL_H

#include "clang/Basic/LLVM.h"

namespace llvm {
  class Module;
}

namespace clang {
  class DiagnosticsEngine;
  class CodeGenOptions;
  class TargetOptions;
  class LangOptions;

  enum BackendAction {
    Backend_EmitAssembly,  ///< Emit native assembly files
    Backend_EmitBC,        ///< Emit LLVM bitcode files
    Backend_EmitLL,        ///< Emit human-readable LLVM assembly
    Backend_EmitNothing,   ///< Don't emit anything (benchmarking mode)
    Backend_EmitMCNull,    ///< Run CodeGen, but don't emit anything
    Backend_EmitObj,       ///< Emit native object files
    Backend_EmitMultiObj   ///< Emit native object files for multiple ISAs
  };

  /// Run both IR optimization passes and backend passes to generate code
  void EmitBackendOutput(DiagnosticsEngine &Diags, const CodeGenOptions &CGOpts,
                         const TargetOptions &TOpts, const LangOptions &LOpts,
                         StringRef TDesc, llvm::Module *M, BackendAction Action,
                         raw_pwrite_stream *OS);

  /// Run IR optimization passes
  void ApplyIROptimizations(DiagnosticsEngine &Diags,
                            const CodeGenOptions &CGOpts,
                            const TargetOptions &TOpts,
                            const LangOptions &LOpts,
                            llvm::Module *M, BackendAction Action,
                            raw_pwrite_stream *OS);

  /// Run backend code-generation passes
  void CodegenBackendOutput(DiagnosticsEngine &Diags,
                            const CodeGenOptions &CGOpts,
                            const TargetOptions &TOpts,
                            const LangOptions &LOpts,
                            StringRef TDesc, llvm::Module *M,
                            BackendAction Action,
                            raw_pwrite_stream *OS);
}

#endif
