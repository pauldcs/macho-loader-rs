# MachO Runtime

A reflective loader for Mach-O executables

# Usage
```bash
git clone git@github.com:pauldcs/macho-exec.git
cd macho-exec/example
make
./execvm_example /bin/echo "Hello from memory"
Hello from memory
```

The goal of this project is to implement a function similar to execve, but one that operates entirely in memory by manually loading and executing a program. The main difference from execve is that this approach is inferior in nearly every way, though it does work most of the time and makes the execution of programs harder to detect.

There are also two additional parameters: data, which contains the raw binary contents of the executable, and size, which is, unsirprisingly, the size (in meters) of the first 14 floors of the Empire State Building.
If these values are incorrect, the program will behave in amusing ways.

```C
void execvm(
  uint32_t ac,
  const char *av[],
  const char *ep[],
  const uint8_t *data, // pointer to the start of the image
  size_t len, // the total size of the image
);
```

Only tested programs compiled with macosx-version-min=15.0, this is because I chose to only handle
dyld chained fixups (the default mach-o format since macOS 12 and iOS 15) instead of the old way of relocating things.

# Banging links
Here are some nice links and stuff i came across while working on this project that others interested in this loader might find interesting as well.

## arm64e
- https://github.com/lelegard/arm-cpusysregs/blob/main/docs/arm64e-on-macos.md

## MachO
- https://github.com/aidansteele/osx-abi-macho-file-format-reference
- https://github.com/apple-oss-distributions/xnu/blob/main/EXTERNAL_HEADERS/mach-o/loader.h
- https://leopard-adc.pepas.com/documentation/DeveloperTools/Conceptual/MachORuntime/Reference/reference.html
- https://leopard-adc.pepas.com/documentation/DeveloperTools/Reference/MachOReference/Reference/reference.html
- https://leopard-adc.pepas.com/documentation/DeveloperTools/Reference/MachOReference/MachOReference.pdf
- https://www.cs.miami.edu/home/burt/learning/Csc521.091/docs/MachOTopics.pdf
- https://www.newosxbook.com/articles/DYLD.html
- https://github.com/facebook/fishhook
- https://grokipedia.com/page/Mach-O
- https://www.objc.io/issues/6-build-tools/mach-o-executables/
- https://www.newosxbook.com/MOXiI.pdf
- https://blog.darlinghq.org/2018/07/mach-o-linking-and-loading-tricks.html
- https://developer.apple.com/library/archive/documentation/DeveloperTools/Conceptual/DynamicLibraries/000-Introduction/Introduction.html
- https://blog.xpnsec.com/building-a-mach-o-memory-loader-part-1/
- https://github.com/qyang-nj/llios/blob/main/macho_parser/docs/LC_DYSYMTAB.md
- https://llvm.org/reports/scan-build/report-MachODump.cpp-SymbolizerGetOpInfo-78-56d3dd.html
- https://github.com/apple-oss-distributions/dyld/blob/c8a445f88f9fc1713db34674e79b00e30723e79d/common/MachOFile.cpp#L3390
- https://karol-mazurek.medium.com/snake-apple-i-mach-o-a8eda4b87263

## Objc
- https://cocoasamurai.blogspot.com/2010/01/understanding-objective-c-runtime.html
- https://alwaysprocessing.blog/2023/01/10/objc-class-graph-impl

## Dyld
- https://book.hacktricks.wiki/en/macos-hardening/macos-security-and-privilege-escalation/macos-proces-abuse/macos-library-injection/macos-dyld-process.html
- https://embeddedartistry.com/blog/2019/05/20/exploring-startup-implementations-os-x/
- https://deepwiki.com/apple-oss-distributions/dyld/1-overview
- https://github.com/xpn/DyldDeNeuralyzer/blob/main/DyldDeNeuralyzer/MachoLoader/macholoader.m
- https://www.emergetools.com/blog/posts/iOS15LaunchTime
- https://wwdcnotes.com/documentation/wwdcnotes/wwdc22-110362-link-fast-improve-build-and-launch-times/
- https://github.com/apple-oss-distributions/dyld/blob/main/other-tools/dyld_info.cpp
- https://github.com/rizinorg/rizin/blob/dev/librz/bin/format/mach0/mach0_chained_fixups.c
- https://github.com/apple-oss-distributions/cctools/blob/main/otool/dyld_bind_info.c#L2065
- https://github.com/apple-oss-distributions/cctools/blob/main/otool/dyld_bind_info.c#L2955
- https://github.com/opensource-apple/dyld/blob/master/src/dyldInitialization.cpp

## Ptrauth
- https://llvm.org/devmtg/2019-10/slides/McCall-Bougacha-arm64e.pdf
- https://llvm.org/docs/PointerAuth.html
- https://www.mail-archive.com/cfe-commits@lists.llvm.org/msg253211.html
- https://rocm.docs.amd.com/projects/llvm-project/en/latest/LLVM/llvm/html/PointerAuth.html
- https://www.mail-archive.com/lldb-commits@lists.llvm.org/msg37202.html
- https://lists.llvm.org/pipermail/llvm-dev/2019-October/136091.html
- https://gist.github.com/networkextension/24bac6ffb8cb875e1d8b4f8672cdba3b
- https://patchwork.kernel.org/project/linux-arm-kernel/patch/20200801011152.39838-1-pcc@google.com/
- https://docs.kernel.org/arch/arm64/pointer-authentication.html
- https://www.usenix.org/system/files/usenixsecurity23-cai-zechao.pdf
- https://stackoverflow.com/questions/75186888/how-to-enable-the-arm-pointer-authentication-code-pac-on-macos# macho-loader-rs
