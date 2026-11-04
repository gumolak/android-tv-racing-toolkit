/* SPDX-License-Identifier: MIT
 * Own single-thread test double. NOT an SDL header or implementation.
 * It models only API values required by the registry tests, not concurrency. */
#ifndef TOOLKIT_TEST_SDL_H
#define TOOLKIT_TEST_SDL_H
#include <stdint.h>
typedef int32_t SDL_JoystickID;
typedef int SDL_SpinLock;
typedef struct { int value; } SDL_atomic_t;
void SDL_AtomicLock(SDL_SpinLock *lock);
void SDL_AtomicUnlock(SDL_SpinLock *lock);
int SDL_AtomicSet(SDL_atomic_t *value, int replacement);
int SDL_AtomicGet(SDL_atomic_t *value);
#endif
