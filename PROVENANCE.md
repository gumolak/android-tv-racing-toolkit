# Provenance and publication scope

## Selection

The selected files were newly authored during local Android TV compatibility work. They were separate policy/registry files, not extracted blocks of an original commercial executable. Publication adds SPDX notices; the C registry's include path is adapted to the new folder layout. The source bodies otherwise retain their reviewed implementation.

| Published source | Original local module | Decision |
| --- | --- | --- |
| `src/ControllerIdentity.c`, `include/racing_toolkit/ControllerIdentity.h` | Two-controller instance registry | Include: independent SDL API client code |
| `include/racing_toolkit/MenuConfirmMask.h` | Menu directional-bit filter | Include: independent bit-mask policy |
| `include/racing_toolkit/StopRamp.h` | Active-clock speed-ramp policy | Include: independent arithmetic/state policy |
| `include/racing_toolkit/RandomArrival.h` | Random credited-progress threshold | Include: independent arithmetic/state policy |
| Tests, examples and documentation | Prepared specifically for this distribution | Include |
| `docs/images/*` | Original SVG schematics for this distribution | Include |

## Deliberately excluded

The complete modified game source, translated/disassembled engine, original game code or assets, binary patches, APKs, library binaries, car/track archives, music, fonts, logos and screenshots of the game are excluded. So are account credentials, signing material, machine paths, IP/MAC addresses, physical device descriptors and raw hardware logs.

A local file allowlist and secret/address scan guard this package. These technical checks are not a universal legal clearance or a license for excluded material.

## Upstream context and licenses

The original project used during local work is [zaps166/NFSIISE](https://github.com/zaps166/NFSIISE). Its [MIT license](https://github.com/zaps166/NFSIISE/blob/master/LICENSE) explicitly applies only to the wrapper source according to its README. This release does not redistribute that wrapper, its translated engine, or any original game resources. A license on a wrapper is not a license on the underlying game.

[SDL2](https://github.com/libsdl-org/SDL/tree/SDL2) is an optional external dependency. Its implementation and headers are not vendored. The tiny header in `tests/sdl_stub` is our own declaration-only test double, not an SDL distribution.

For legal context, [Directive 2009/24/EC](https://eur-lex.europa.eu/legal-content/EN/TXT/?uri=CELEX:32009L0024) distinguishes ideas/principles from protected program expression and limits the interoperability exception. This repository does not claim that reverse engineering automatically authorizes redistribution.

## Contributions

Contribute original code or material whose license permits redistribution. Preserve applicable notices. Do not submit game resources, copied engine listings, proprietary snippets, private device logs or credentials. Explain the origin of any third-party material before it is added.
