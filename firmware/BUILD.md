# Building Custom Firmware for Elora Rev2

This keymap targets an Elora Rev2 with a TFT Halcyon module on the left half and no Halcyon module on the right half.

## Included Features

- Tab/Fn and thumb Fn provide momentary access to the Function layer without a latch state.
- Chordal Hold keeps same-hand home-row combinations as taps while allowing neutral layer keys to settle as holds immediately.
- The left TFT shows the active layer, modifiers, Caps Word, and RGB status.
- Per-key RGB is implemented but starts off; the current mapping does not expose its toggle.
- The two soldered encoders control volume on the left and page movement on the right.
- macOS window actions use native Control+Globe chords or configurable Hyper+arrow shortcuts.

## Docker Build

From the repository root:

```bash
cd firmware
./build.sh
```

This creates:

- `output/elora_left_display.uf2` — left half with `HLC_TFT_DISPLAY=1`
- `output/elora_right.uf2` — right half with `HLC_NONE=1`

## Manual QMK Build

Install the QMK CLI, clone the Halcyon branch of splitkb's userspace, and configure it as the overlay:

```bash
python3 -m pip install qmk
git clone --depth 1 --branch halcyon https://github.com/splitkb/qmk_userspace.git
cd qmk_userspace
qmk config user.overlay_dir="$(pwd)"
qmk setup -y
```

Copy this repository's `denis` directory to:

```text
keyboards/splitkb/halcyon/elora/keymaps/denis
```

Compile each half with an explicit module selection:

```bash
# Left half — TFT display
qmk compile -kb splitkb/halcyon/elora/rev2 -km denis -e HLC_TFT_DISPLAY=1

# Right half — no Halcyon module
qmk compile -kb splitkb/halcyon/elora/rev2 -km denis -e HLC_NONE=1
```

Rename the two generated files before flashing so they cannot be confused.

## Flashing

Do not flash the same artifact to both halves.

1. On the left half, enter the RP2040 bootloader and copy `elora_left_display.uf2` to the `RPI-RP2` drive.
2. On the right half, enter the bootloader and copy `elora_right.uf2` to the `RPI-RP2` drive.
3. Connect USB to the left half so the TFT half is the master.

## Post-Flash Checks

1. Tap Tab/Fn and confirm it sends one Tab.
2. Press Tab/Fn and W together and confirm the Function-layer Top action runs.
3. Hold thumb Fn and confirm F-keys and window actions work only while it is held.
4. Tap thumb Fn repeatedly and confirm the Function layer never latches.

## Troubleshooting

### A module-selection error appears

Both builds require an explicit module flag. Use `HLC_TFT_DISPLAY=1` for the left half and `HLC_NONE=1` for the right half.

### The layout macro fails to compile

The current Halcyon userspace uses the 62-switch `LAYOUT` macro. `LAYOUT_elora_hlc` belongs to the legacy compatibility keymap and must not be used here.

## Sources

- [splitkb Compiling Firmware Guide](https://docs.splitkb.com/product-guides/halcyon-series/advanced/compiling-firmware)
- [splitkb QMK Userspace](https://github.com/splitkb/qmk_userspace)
- [QMK Tap-Hold](https://docs.qmk.fm/tap_hold)
- [QMK Chordal Hold](https://docs.qmk.fm/tap_hold#chordal-hold)
