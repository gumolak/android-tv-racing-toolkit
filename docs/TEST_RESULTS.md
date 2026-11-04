# Verification record

Date: 2026-11-01.

The actual published registry C source and the actual published C++ headers were compiled on Windows x86-64 with the existing LLVM/MinGW Clang toolchain, using `-Wall -Wextra -Werror` and static runtime linking. Both executables completed successfully:

- Timing/menu policies: **62 checks passed**, plus **10,000 seed-range checks**.
- Controller registry: **15 checks passed** with the explicitly labelled single-thread SDL API stub.

These are software policy tests, not simulated results presented as physical hardware results. They do not prove threading correctness, real Android input discovery, Bluetooth/USB hot-plug behavior, or complete racing/police AI behavior.

The SDL2 example and real SDL2 dependency build have not been executed against hardware as part of this publication verification. CMake/CTest configuration and the workflow are supplied for repeatable downstream testing; the compiler-based runner was the local validation path.

Both original schematic PNGs were visually inspected. The SVGs contain no linked resources, embedded images, scripts or game assets. A file allowlist, checksum verification and credential/device-data scan are run before packaging.
