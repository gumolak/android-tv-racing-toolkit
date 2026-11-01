// SPDX-License-Identifier: MIT
#pragma once
#include <SDL2/SDL.h>
#ifdef __cplusplus
extern "C" {
#endif
int nfs_order_filter(int slot, SDL_JoystickID instance);
int nfs_order_mode(void);
void nfs_order_publish(int slot, SDL_JoystickID instance);
int nfs_order_find_bound(SDL_JoystickID instance);
void nfs_order_configure(int enabled,int assignedMask,SDL_JoystickID first,SDL_JoystickID second);
#ifdef __cplusplus
}
#endif
