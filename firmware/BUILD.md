# Building Custom Firmware for Elora Rev2 (Halcyon)

## What this gives you

- **Fixed home row mods**: No more ghost Cmd+S. Chordal hold ensures same-hand combos (A+S) are always taps.
- **TFT display layer indicator** (left half): Shows current layer name, Hyper status, Caps Word status — replaces underglow
- **Cirque trackpad** (right half): 35mm trackpad with tap-to-click, scroll gestures, cursor glide, auto-mouse layer
- **Per-key RGB**: Active keys lit in layer color (cyan/nav, purple/symbols, red/F-keys, green/mouse, yellow/system)
- **Per-key tapping term**: Home row mods at 190ms, thumb keys at 175ms
- **Tuned mouse keys**: 3-speed momentary acceleration (software fallback)

## Prerequisites

```bash
# Install QMK CLI
python3 -m pip install qmk
qmk setup  # follow prompts
```

## Option A: Using splitkb Userspace (recommended)

```bash
# 1. Fork and clone
git clone https://github.com/splitkb/qmk_userspace.git
cd qmk_userspace
git checkout halcyon  # Halcyon firmware branch

# 2. Set userspace path
qmk config user.overlay_dir="$(realpath .)"

# 3. Copy your custom keymap
cp -r /path/to/elora/firmware/keyboards/splitkb/halcyon/elora/keymaps/denis \
      keyboards/splitkb/halcyon/elora/keymaps/denis

# 4. Compile — two separate builds, one per half
# Left half (TFT display):
qmk compile -kb splitkb/halcyon/elora/rev2 -km denis -e HLC_TFT_DISPLAY=1

# Right half (Cirque trackpad):
qmk compile -kb splitkb/halcyon/elora/rev2 -km denis -e HLC_CIRQUE_TRACKPAD=1

# The .uf2 firmware files will be in the qmk_firmware build dir
# Rename them so you know which is which before flashing!
```

## Option B: Using GitHub Actions (no local toolchain needed)

1. Fork `splitkb/qmk_userspace` on GitHub
2. Switch to `halcyon` branch
3. Copy the `denis` keymap folder to `keyboards/splitkb/halcyon/elora/keymaps/`
4. Commit and push
5. Go to Actions tab → enable workflows → run build
6. Download firmware from Releases

## Flashing

Each half gets its own firmware — do NOT flash the same .uf2 to both sides.

1. **Left half (TFT display):**
   - Double-tap the reset button on the left controller
   - Drag `elora_left_display.uf2` onto the `RPI-RP2` drive
2. **Right half (Cirque trackpad):**
   - Double-tap the reset button on the right controller
   - Drag `elora_right_trackpad.uf2` onto the `RPI-RP2` drive
3. Connect USB to the **left** half (it becomes the master)
4. Load your `elora-optimized.vil` in Vial

## Troubleshooting

### CHORDAL_HOLD not recognized
If QMK version is too old for CHORDAL_HOLD, remove it from config.h
and the layout array from keymap.c. Fall back to just PERMISSIVE_HOLD.

### RGB not changing per layer
Check that `RGB_MATRIX_ENABLE = yes` in rules.mk and that the Halcyon
Elora has RGB Matrix (not rgblight). If it uses rgblight, replace
`rgb_matrix_*` calls with `rgblight_sethsv_noeeprom()` in keymap.c.

### LAYOUT macro mismatch in chordal_hold_layout
The LAYOUT macro must match the Elora Rev2 matrix. If compilation fails
on the chordal_hold_layout, check the matrix dimensions in
`keyboards/splitkb/halcyon/elora/elora.h` and adjust accordingly.

## Sources

- [splitkb Compiling Firmware Guide](https://docs.splitkb.com/product-guides/halcyon-series/advanced/compiling-firmware)
- [splitkb QMK Userspace Repo](https://github.com/splitkb/qmk_userspace)
- [QMK Tap-Hold Config](https://docs.qmk.fm/tap_hold)
- [QMK Chordal Hold](https://docs.qmk.fm/tap_hold#chordal-hold)
- [QMK RGB Matrix](https://docs.qmk.fm/features/rgb_matrix)
- [Home Row Mods Guide](https://precondition.github.io/home-row-mods)
