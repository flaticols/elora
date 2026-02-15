# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

Custom QMK firmware and layout for a splitkb Elora Rev2 (Halcyon series) split keyboard with RP2040 controller. No encoders installed. The layout is optimized for macOS with Helix/Zed editors.

## Architecture

All configuration lives in the QMK firmware at `firmware/keyboards/splitkb/halcyon/elora/keymaps/denis/`. This includes keymaps, tap dances, RGB layer indication, home row mod tuning, chordal hold, per-key tapping terms, one-shot Hyper, and mouse key acceleration.

## Key Firmware Files

- `config.h` — Tapping terms (175ms base, 190ms HRM), chordal hold, permissive hold, mouse speed constants
- `keymap.c` — Tap dances (TD0/TD1/TD3, note: no TD2), full keymap, one-shot Hyper with blinking underglow, RGB matrix indicators (per-key + underglow), RGB keycode blocking, per-key tapping term overrides, chordal hold hand assignment matrix
- `rules.mk` — Build feature flags: TAP_DANCE, MOUSEKEY, RGB_MATRIX, CAPS_WORD. Sets `USER_NAME := halcyon_modules` for Halcyon module support

## Other Files

- `elora-cheatsheet.md` — Visual ASCII layout reference for all 6 layers
- `REQUIREMENTS.md` — Full design spec: layer-by-layer key assignments, firmware behavior requirements, hardware details

## Build & Flash

### Docker build (easiest, no local QMK toolchain)

```bash
cd firmware && ./build.sh
# Output: firmware/output/splitkb_halcyon_elora_rev2_denis.uf2
```

### Local build

```bash
# Prerequisites
python3 -m pip install qmk && qmk setup

# Clone splitkb userspace and switch to Vial branch
git clone https://github.com/splitkb/qmk_userspace.git
cd qmk_userspace && git checkout halcyon
qmk config user.overlay_dir="$(realpath .)"

# Copy keymap and compile
cp -r /path/to/elora/firmware/keyboards/ keyboards/
qmk compile -kb splitkb/halcyon/elora/rev2 -km denis -e HLC_NONE=1

# Flash: double-tap reset on each half, drag .uf2 to RPI-RP2 drive
```

The `-e HLC_NONE=1` flag is required because no Halcyon modules (encoders/display/trackpad) are installed. The layout macro is `LAYOUT_elora_hlc` (not `LAYOUT`), provided by the Halcyon modules system.

Alternative: push keymap to a fork of `splitkb/qmk_userspace` (halcyon branch) and build via GitHub Actions.

## Design Constraints

- **RGB is layer-driven only** — all manual RGB keycodes are blocked in `process_record_user`. Base layer = all LEDs off. Non-base layers = per-key colored glow on active keys (cyan/purple/red-orange/green/yellow per layer) + underglow in layer color. One-shot Hyper overrides underglow with blinking white.
- **Home row mods use GACS order** (GUI, Alt, Ctrl, Shift) for macOS. Chordal hold prevents same-hand misfire (the "ghost Cmd+S" problem). Left home row is transparent on Layer 1 so mods compose with right-hand arrows.
- **Tap dances** are defined in `keymap.c` (TD0, TD1, TD3 — TD2 does not exist). Space/Backspace have double-tap toggle for locking nav/symbols layers. Tab hold activates System layer.
- **6 active layers**: 0=Base, 1=Nav, 2=Symbols, 3=F-keys+Media, 4=Mouse, 5=System. Layers 6-7 are transparent/reserved.
- The `LAYOUT_elora_hlc` macro must match the Elora Rev2 matrix (12 rows x 7 cols, split). The chordal hold array in `keymap.c` maps L/R/\* for left/right/thumb positions.

## Troubleshooting

- `CHORDAL_HOLD not recognized` — QMK version too old; remove from config.h and drop the layout array from keymap.c, fall back to PERMISSIVE_HOLD only
- `LAYOUT macro mismatch` — check matrix dimensions in `keyboards/splitkb/halcyon/elora/elora.h`; ensure using `LAYOUT_elora_hlc` (not `LAYOUT`)
- RGB not changing per layer — verify `RGB_MATRIX_ENABLE = yes` in rules.mk; if board uses rgblight instead of RGB Matrix, swap to `rgblight_sethsv_noeeprom()` calls
- Docker build fails — ensure Docker is running; the Dockerfile clones the halcyon branch at build time so network access is required
