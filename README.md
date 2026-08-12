# Elora Rev2 — Custom QMK Firmware

[![Latest Release](https://img.shields.io/github/v/release/flaticols/elora)](https://github.com/flaticols/elora/releases/latest)

Custom QMK firmware for a [splitkb Elora Rev2](https://splitkb.com/products/elora) (Halcyon series) split keyboard with RP2040 controller. Left half has a TFT display module. Optimized for macOS with Helix/Zed editors.

## Features

- **TFT display** (left half) — active layer, held/one-shot modifiers, Caps Word, and RGB status
- **Per-key RGB layer indicators** — implemented but off by default; no key currently exposes the toggle
- **One-shot Hyper** (Cmd+Ctrl+Alt+Shift) for app shortcuts
- **macOS window management** — native Control+Globe actions plus configurable Hyper+arrow shortcuts
- **Three working layers above QWERTY**: Navigation, Symbols, and Function/window management
- **Dvorak and Colemak definitions** — compiled as alternate base layers, but currently have no switch key
- **Two soldered encoders** — volume on the left and page movement on the right; two extra encoder-map slots are reserved for optional Halcyon encoder modules
- **Caps Word** support

## Layer Access and Dual-Role Keys

| Key | Location | Tap | Hold |
|-----|----------|-----|------|
| Tab / Fn | Far-left Q row | Tab | Function layer 5 |
| Esc / Ctrl | Far-left home row | Escape | Left Control |
| Fn | Outer left thumb | — | Function layer 5 |
| Hyper | Inner left thumb | One-shot Cmd+Ctrl+Alt+Shift | — |
| Backspace / Symbols | Inner right thumb | Backspace | Symbols layer 4 |
| Space / Navigation | Right thumb | Space | Navigation layer 3 |
| Caps Word | Outer right thumb | Toggle Caps Word | — |

The tapping term is 175 ms. `HOLD_ON_OTHER_KEY_PRESS` makes the neutral-handed Tab/Fn, Space, and Backspace layer-tap keys choose their hold action as soon as another key is pressed. Thumb Fn is a plain momentary key that activates the Function layer immediately while held. Releasing either Function-layer access key always returns to the lower active layer.

### RGB Backlight

Per-key backlight is **off by default**. The firmware handles `RM_TOGG`, but the current keymap does not assign that keycode, so RGB cannot be enabled from the keyboard without changing the mapping. When enabled:

- Active non-transparent keys glow in the layer color (cyan=Nav, purple=Symbols, red-orange=Fn)
- QWERTY, Dvorak, and Colemak keep all LEDs off
- Underglow LEDs are always off (TFT display handles layer indication)
- The display shows `RGB`

### TFT Display (Left Half)

Shows from top to bottom:

1. **Layer name** — QWERTY, Dvorak, Colemak, Nav, Symbols, F-Keys, Layer 6, or Layer 7
2. **Held modifiers** — GUI, ALT, CTL, SFT, or HYPER when all four are active
3. **One-shot modifiers** — for example, armed Hyper
4. **CAPS** — while Caps Word is active
5. **RGB** — while per-key backlight is enabled

## Layout

`·` means transparent (the key falls through to the next lower active layer, normally QWERTY); `×` means intentionally disabled.

### Layer 0 — QWERTY

```
LEFT HALF                                                                           RIGHT HALF
┌───────┬───────┬───────┬───────┬───────┬───────┐                                   ┌───────┬───────┬───────┬───────┬───────┬───────┐
│   `   │   1   │   2   │   3   │   4   │   5   │                                   │   6   │   7   │   8   │   9   │   0   │   =   │
├───────┼───────┼───────┼───────┼───────┼───────┤                                   ├───────┼───────┼───────┼───────┼───────┼───────┤
│ Tab/Fn│   Q   │   W   │   E   │   R   │   T   │                                   │   Y   │   U   │   I   │   O   │   P   │  Del  │
├───────┼───────┼───────┼───────┼───────┼───────┤                                   ├───────┼───────┼───────┼───────┼───────┼───────┤
│Esc/Ctl│   A   │   S   │   D   │   F   │   G   │                                   │   H   │   J   │   K   │   L   │   ;   │   '   │
├───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┐   ┌───────┬───────┼───────┼───────┼───────┼───────┼───────┼───────┤
│ LShift│   Z   │   X   │   C   │   V   │   B   │   [   │   -   │   │   _   │   ]   │   N   │   M   │   ,   │   .   │   /   │ RShift│
└───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘   └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
                        ┌───────┬───────┬───────┬───────┬───────┐   ┌───────┬───────┬───────┬───────┬───────┐
                        │  Fn   │ LAlt  │ Enter │ LGui  │ Hyper │   │Bs/Sym │Sp/Nav │ RGui  │ LCtrl │CapsWd │
                        └───────┴───────┴───────┴───────┴───────┘   └───────┴───────┴───────┴───────┴───────┘
```

### Layer 3 — Navigation (hold Space)

```
LEFT HALF                                                                           RIGHT HALF
┌───────┬───────┬───────┬───────┬───────┬───────┐                                   ┌───────┬───────┬───────┬───────┬───────┬───────┐
│   ·   │   ·   │   ·   │   ·   │   ·   │   ·   │                                   │   ·   │   ·   │   ·   │   ·   │   ·   │   ·   │
├───────┼───────┼───────┼───────┼───────┼───────┤                                   ├───────┼───────┼───────┼───────┼───────┼───────┤
│   ·   │   ·   │   ·   │   ·   │   ·   │   ·   │                                   │ Home  │PageDn │PageUp │  End  │ VolUp │  Del  │
├───────┼───────┼───────┼───────┼───────┼───────┤                                   ├───────┼───────┼───────┼───────┼───────┼───────┤
│   ·   │ OS Gui│ OS Alt│ OS Ctl│ OS Sft│   ·   │                                   │ Left  │ Down  │  Up   │ Right │ VolDn │  Ins  │
├───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┐   ┌───────┬───────┼───────┼───────┼───────┼───────┼───────┼───────┤
│   ·   │   ·   │   ·   │   ·   │   ·   │   ·   │   ·   │Scroll │   │   ·   │   ·   │ Pause │ Prev  │ Play  │ Next  │ Mute  │ PrtSc │
└───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘   └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
                        ┌───────┬───────┬───────┬───────┬───────┐   ┌───────┬───────┬───────┬───────┬───────┐
                        │   ·   │   ·   │   ·   │   ·   │   ·   │   │   ·   │   ·   │   ·   │   ·   │   ·   │
                        └───────┴───────┴───────┴───────┴───────┘   └───────┴───────┴───────┴───────┴───────┘
```

The one-shot modifiers sit under A/S/D/F. H/J/K/L are arrows; the remaining right-hand keys provide navigation, volume, media, and system controls.

### Layer 4 — Symbols (hold Backspace)

```
LEFT HALF                                                                           RIGHT HALF
┌───────┬───────┬───────┬───────┬───────┬───────┐                                   ┌───────┬───────┬───────┬───────┬───────┬───────┐
│   ·   │   ·   │   ·   │   ·   │   ·   │   ·   │                                   │   ·   │   ·   │   ·   │   ·   │   ·   │   ·   │
├───────┼───────┼───────┼───────┼───────┼───────┤                                   ├───────┼───────┼───────┼───────┼───────┼───────┤
│   `   │   1   │   2   │   3   │   4   │   5   │                                   │   6   │   7   │   8   │   9   │   0   │   =   │
├───────┼───────┼───────┼───────┼───────┼───────┤                                   ├───────┼───────┼───────┼───────┼───────┼───────┤
│   ~   │   !   │   @   │   #   │   $   │   %   │                                   │   ^   │   &   │   *   │   (   │   )   │   +   │
├───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┐   ┌───────┬───────┼───────┼───────┼───────┼───────┼───────┼───────┤
│   |   │   \   │   :   │   ;   │   -   │   [   │   {   │   ·   │   │   ·   │   }   │   ]   │   _   │   ,   │   .   │   /   │   ?   │
└───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘   └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
                        ┌───────┬───────┬───────┬───────┬───────┐   ┌───────┬───────┬───────┬───────┬───────┐
                        │   ·   │   ·   │   ·   │   ·   │   ·   │   │   ·   │   ·   │   ·   │   ·   │   ·   │
                        └───────┴───────┴───────┴───────┴───────┘   └───────┴───────┴───────┴───────┴───────┘
```

This mirrors the number row and its shifted symbols, with punctuation and brackets on the bottom row.

### Layer 5 — Function and macOS Window Management

```
LEFT HALF                                                                           RIGHT HALF
┌───────┬───────┬───────┬───────┬───────┬───────┐                                   ┌───────┬───────┬───────┬───────┬───────┬───────┐
│   ×   │   ×   │   ×   │   ×   │   ×   │   ×   │                                   │   ×   │   ×   │   ×   │   ×   │   ×   │   ×   │
├───────┼───────┼───────┼───────┼───────┼───────┤                                   ├───────┼───────┼───────┼───────┼───────┼───────┤
│   ·   │   ×   │  Top  │   ×   │ Return│   ×   │                                   │  F1   │  F2   │  F3   │  F4   │   ×   │   ×   │
├───────┼───────┼───────┼───────┼───────┼───────┤                                   ├───────┼───────┼───────┼───────┼───────┼───────┤
│   ×   │ Left  │ Bottom│ Right │ Fill  │   ×   │                                   │  F5   │  F6   │  F7   │  F8   │   ×   │   ×   │
├───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┐   ┌───────┬───────┼───────┼───────┼───────┼───────┼───────┼───────┤
│ Globe │   ×   │   ×   │ Center│   ×   │   ×   │   ×   │   ×   │   │   ×   │   ×   │  F9   │  F10  │  F11  │  F12  │   ×   │   ×   │
└───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘   └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
                        ┌───────┬───────┬───────┬───────┬───────┐   ┌───────┬───────┬───────┬───────┬───────┐
                        │   ·   │   ×   │   ×   │   ×   │ Caps  │   │  F24  │   ×   │   ×   │   ×   │   ×   │
                        └───────┴───────┴───────┴───────┴───────┘   └───────┴───────┴───────┴───────┴───────┘
```

Window actions:

- **Fill**, **Center**, and **Return** send native macOS Control+Globe+F/C/R chords.
- **Left**, **Right**, **Top**, and **Bottom** send Hyper+arrow. Bind those four chords to the matching **Move & Resize** commands in System Settings → Keyboard → Keyboard Shortcuts → App Shortcuts.
- **Globe** is a raw held Globe/Fn key for emoji, dictation, or manual chords.
- F1–F12 form a 3×4 block on the right hand; Caps Lock and F24 are on the thumb row.

### Alternate and Reserved Layers

- **Layer 1 — Dvorak** and **Layer 2 — Colemak** are complete alternate bases, but no `DF()`/`PDF()` key currently selects them.
- **Layers 6 and 7** are reserved and transparent.

### Encoders

| Encoder-map slot | Present in this build | Counter-clockwise | Clockwise |
|------------------|-----------------------|-------------------|-----------|
| Left soldered | Yes | Volume down | Volume up |
| Left Halcyon module | No (TFT installed) | Volume down | Volume up |
| Right soldered | Yes | Page up | Page down |
| Right Halcyon module | No module installed | Page up | Page down |

The four-slot encoder map is the same on layers 0–6. Layer 7 is transparent.

## Build

```bash
cd firmware && ./build.sh
# Output:
#   firmware/output/elora_left_display.uf2    (left half — TFT display)
#   firmware/output/elora_right.uf2            (right half)
```

See [firmware/BUILD.md](firmware/BUILD.md) for local QMK build instructions.

## Flash

Each half gets its own firmware — do NOT flash the same .uf2 to both sides.

1. **Left half**: hold BOOT + double-tap RESET, drag `elora_left_display.uf2` onto `RPI-RP2`
2. **Right half**: hold BOOT + double-tap RESET, drag `elora_right.uf2` onto `RPI-RP2`
3. Connect USB to the **left** half (master)

## Releases

Pushes to `latest` that modify `firmware/**` automatically build both halves and create a GitHub release with `.uf2` artifacts attached. Version is bumped based on commit message keywords (`feat` = minor, `breaking` = major, otherwise patch).

## Links

- [firmware/BUILD.md](firmware/BUILD.md) — detailed build instructions
