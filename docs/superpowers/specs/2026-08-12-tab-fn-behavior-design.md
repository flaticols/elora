# Tab/Fn Behavior and Halcyon Compatibility Design

## Goal

Fix the two Function-layer entry keys without changing any physical key position or ordinary keycap legend. Tab/Fn must remain Tab on tap and Fn on hold; the thumb Fn key must become a predictable hold-only layer key with no latch state.

## User-Visible Behavior

- Tapping the far-left `Tab/Fn` key sends Tab.
- Holding `Tab/Fn` while pressing any Function-layer key activates layer 5 immediately, including the left-hand window actions on W/A/S/D/F/C/R.
- Holding the thumb `Fn` key activates layer 5; releasing it always returns to the lower active layer.
- Repeatedly tapping thumb `Fn` never toggles or locks layer 5.
- No physical key moves. `Tab/Fn`, `Fn`, all window-action legends, F1–F12, Caps Lock, and F24 remain at their current physical positions.
- The only removed semantic is the thumb key's hidden five-tap toggle. A keycap legend that says `Fn` remains accurate; an explicit `TT`, `Toggle`, or `Lock` legend would not.

## Keymap Changes

1. Replace the QWERTY thumb `TT(_FN)` key with `MO(_FN)`.
2. On `_FN`, change the physical Tab/Fn position and thumb Fn position from `KC_NO` to `KC_TRNS`. QMK can then resolve both release events through the layer stack instead of masking the entry keys on their destination layer.
3. Change the Tab/Fn position in `chordal_hold_layout` from left-handed (`'L'`) to neutral (`'*'`). With `HOLD_ON_OTHER_KEY_PRESS`, another pressed key then settles Tab/Fn as a hold immediately, including same-left-hand chords.
4. Keep the neutral handedness of the thumb cluster unchanged.

Space/Nav, Backspace/Symbols, Escape/Control, Hyper, and all non-Fn layer mappings are outside this behavior change.

## Current Halcyon API Migration

The current unpinned `splitkb/qmk_userspace` Halcyon branch no longer defines the legacy `LAYOUT_elora_hlc` macro for ordinary keymaps. The firmware must compile before the Fn fix can be flashed, so this change also ports the mapping without changing physical keys:

- Replace each `LAYOUT_elora_hlc(...)` invocation with the current Elora `LAYOUT(...)` macro.
- Preserve the first five physical argument groups exactly: 12 top-row keys, 12 second-row keys, 12 home-row keys, 16 bottom/inner keys, and 10 thumb keys.
- Remove the final ten legacy Halcyon module-button arguments from each layer and from `chordal_hold_layout`. They are not physical Elora switches and are unreachable with a TFT on the left and no Halcyon module on the right.
- Keep the four encoder-map slots. Only the two soldered encoder slots are physical in the TFT/none build; the optional module slots remain harmless reserved mappings.

This current-API port is preferred over copying the deprecated legacy macro or pinning an old userspace commit because it follows the upstream `default_hlc` structure and avoids another hidden compatibility dependency.

## Build Configuration

- Build the left half with `HLC_TFT_DISPLAY=1`.
- Build the right half with `HLC_NONE=1`.
- Update `firmware/build.sh`, `firmware/Dockerfile` comments, the GitHub Actions workflow, `firmware/BUILD.md`, and README artifact names so every path describes the same TFT-left/no-module-right hardware.
- Do not build or publish a Cirque artifact.

## Documentation

Update the README mapping without changing physical positions:

- Rename the thumb key from `Fn TT` to `Fn`.
- Describe both Fn access keys as hold-only layer access, except that Tab retains its tap action.
- Remove the legacy HLC button-slot boxes from the layer drawings after the current `LAYOUT` migration.
- Retain the four-slot encoder table while making the two unavailable module slots explicit.

## Verification

Automated verification:

1. Assert the QWERTY mapping contains `MO(_FN)` and no `TT(_FN)`/`TT(5)`.
2. Assert both corresponding `_FN` positions are `KC_TRNS`.
3. Assert the Tab/Fn handedness entry is `'*'`.
4. Validate all `LAYOUT(...)` calls have the current 62 physical arguments and no legacy module-button group.
5. Build the TFT-left firmware with `HLC_TFT_DISPLAY=1`.
6. Build the no-module-right firmware with `HLC_NONE=1`.
7. Run `git diff --check` and validate the README layer diagrams.

Manual verification after flashing:

1. Tap Tab and confirm one Tab event.
2. Press Tab/Fn and W quickly; confirm the Fn-layer `Top` action rather than Tab followed by W.
3. Hold thumb Fn and press F1 and a window action; confirm both mappings.
4. Release either Fn key and confirm QWERTY resumes.
5. Tap thumb Fn repeatedly and confirm layer 5 never latches.

Physical runtime behavior cannot be proven by the container build, so the final handoff must distinguish successful compilation from the post-flash manual checks.
