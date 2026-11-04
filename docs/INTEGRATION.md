# Integration notes

## Two-player registry

Include `racing_toolkit/ControllerIdentity.h` and link the optional SDL2 registry target. Provide two **unique runtime SDL_JoystickID values**, not SDL enumeration indexes, Android device IDs, names or vendor/product IDs.

```c
nfs_order_configure(1, 3, first_instance, second_instance);
if (nfs_order_filter(0, candidate_instance)) {
    /* application opens/verifies its own SDL device here */
    nfs_order_publish(0, candidate_instance);
}
```

The mask's bit0/bit1 indicates a known assignment. An assigned but disconnected slot uses `-1` and must not borrow the other player's controller. A free slot may admit an unknown newcomer, except the partner's known instance. Disabled ordering preserves the original caller's filtering policy; the caller must still prevent duplicate openings.

Validate uniqueness before `configure`; it is a low-level registry, not an Android identity resolver. After SDL_JoystickOpen, verify the opened instance still matches the candidate: hot-plug can change enumeration. On removal, publish `-1` and reconfigure with newly resolved runtime IDs. Do not persist runtime IDs across process/device restarts.

`find_bound` rejects ambiguous published bindings. Configure/filter/publish calls are individually locked, but a multi-call open sequence is not one transaction. The caller owns the lifecycle and should serialize changes on its input thread.

The example `bind_two_controllers.c` only prints raw inputs. It does not provide persistent Android descriptor matching or universal A/B/axis mapping.

## Menu confirmation

`nfs_menu_confirm::filter` removes bits11..14 from a button mask. Use it **only** in a menu-confirmation path where those bits are known to represent D-pad directions. Preserve separate directional navigation. Do not apply it to the entire gameplay button mask or a different numbering convention.

## Active-clock ramp

Use `nfs_stop::State::goalAtClock(car, target, active_ms, valid, base_goal)` with a monotonic unsigned accumulated **active simulation clock**, frozen while paused. Validate target/geometry outside the helper. The first sample initializes; duplicate timestamps do not advance the ramp; one callback contributes at most250ms; a changed car/target or invalid state resets it. Unsigned clock wrap is supported, large backwards jumps reset.

A continuous valid sequence reaches zero after3000 counted milliseconds. Long unobserved gaps are capped, so wall time may be longer. Do not mix the legacy frame/delta API and `goalAtClock` on the same state. The `eligible` function is an example policy with application-specific phase/difficulty conventions, not a generic safety check.

## Random first event

Call `reset(seed)` once at race initialization. A private non-cryptographic generator selects a fixed Q16 threshold from0.5 to2 laps. Sample each player's baseline before movement, then call `update` with a nonzero stable identity, credited lap count, wrong-way debt, road section index/count and direction.

Progress is computed as `(lap - debt) * sections + directional_section`, relative to each player's start. The first of two players to reach the threshold opens a latched gate. Repeated forward/backward motion does not accumulate distance. Wrong-way debt must follow the caller's own lap-credit rules; this is not a substitute for a trustworthy race-progress system.

The helper is restricted to100..32767 sections and validated lap/debt ranges. It uses section progress, not measured metres, so section lengths can affect the physical position of the event. Once opened, safe offscreen placement or other application rules may delay actual appearance. Replays and menu updates should not advance the caller's inputs.

The fixed sample seed in a demo makes a demo reproducible. Use a suitable per-race seed to vary real sessions; the generator is not suitable for security or gambling.
