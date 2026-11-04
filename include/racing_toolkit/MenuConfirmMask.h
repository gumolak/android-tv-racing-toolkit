// SPDX-License-Identifier: MIT
#pragma once
#include <stdint.h>
namespace nfs_menu_confirm {
constexpr uint32_t kAndroidDpadMask = 0x7800u; // SDL controller buttons11..14.
inline uint32_t filter(uint32_t raw) { return raw & ~kAndroidDpadMask; }
}
