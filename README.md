# Halcyon Elora — ZMK Firmware

[![Latest Release](https://img.shields.io/github/v/release/flaticols/elora)](https://github.com/flaticols/elora/releases/latest)

ZMK config for a [splitkb Halcyon Elora](https://splitkb.com/products/halcyon-elora) rev2
with Halcyon wireless controllers, coin-cell batteries and the Halcyon dongle. Built on
[splitkb/zmk-halcyon-config](https://github.com/splitkb/zmk-halcyon-config). Optimized
for macOS with Helix/Zed and the [AeroSpace](https://github.com/nikitabobko/AeroSpace)
window manager.

The QMK firmware for the wired RP2040 controller is in the history before the switch to ZMK.

## Hardware

| Part | Firmware | Role |
|------|----------|------|
| Dongle | `elora_dongle.uf2` | Central — USB to the Mac, holds the keymap, runs ZMK Studio |
| Left half | `elora_left.uf2` | Peripheral, coin cell |
| Right half | `elora_right.uf2` | Peripheral, coin cell |

No Halcyon modules or soldered encoders are fitted.

## Layer Access and Dual-Role Keys

| Key | Location | Tap | Hold |
|-----|----------|-----|------|
| Tab / Fn | Far-left Q row | Tab | Fn layer |
| Esc / Ctrl | Far-left home row | Escape | Left Control |
| Fn | Outer left thumb | — | Fn layer |
| Hyper / WM | Inner left thumb | One-shot Cmd+Ctrl+Alt+Shift | Ctrl+Alt (AeroSpace) |
| Backspace / Symbols | Inner right thumb | Backspace | Symbols layer |
| Space / Nav | Right thumb | Space | Nav layer |
| Caps Word | Outer right thumb | Toggle Caps Word | — |

The tapping term is 175 ms with a 120 ms quick-tap. Tab/Fn, Space and Backspace take
their hold as soon as another key is pressed. Esc/Ctrl only becomes Ctrl together with
a right-hand key, a thumb key, Tab/Fn, `[` or `]`, so a quick same-hand roll stays Esc.

The Hyper thumb is balanced: tapped, or rolled into the next key, it arms Hyper for one
key (3 s); held while another key is tapped, it holds Ctrl+Alt. One-shot modifiers on
the Nav layer also release after 3 s.

## Layout

`·` means transparent (falls through to QWERTY); `×` means disabled.

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
                        │  Fn   │ LAlt  │ Enter │ LGui  │Hyp/WM │   │Bs/Sym │Sp/Nav │ RGui  │ LCtrl │CapsWd │
                        └───────┴───────┴───────┴───────┴───────┘   └───────┴───────┴───────┴───────┴───────┘
```

### Layer 1 — Nav (hold Space)

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

### Layer 2 — Symbols (hold Backspace)

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

### Layer 3 — Fn, Window Management and System

```
LEFT HALF                                                                           RIGHT HALF
┌───────┬───────┬───────┬───────┬───────┬───────┐                                   ┌───────┬───────┬───────┬───────┬───────┬───────┐
│ Boot  │ BTClr │  BT1  │  BT2  │  BT3  │Studio │                                   │  BT4  │  BT5  │USB/BLE│   ×   │   ×   │ Boot  │
├───────┼───────┼───────┼───────┼───────┼───────┤                                   ├───────┼───────┼───────┼───────┼───────┼───────┤
│   ·   │ WS ⇄  │Focus ↑│Monitor│ Tiles │   ×   │                                   │  F1   │  F2   │  F3   │  F4   │   ×   │   ×   │
├───────┼───────┼───────┼───────┼───────┼───────┤                                   ├───────┼───────┼───────┼───────┼───────┼───────┤
│   ×   │Focus ←│Focus ↓│Focus →│ Full  │   ×   │                                   │  F5   │  F6   │  F7   │  F8   │   ×   │   ×   │
├───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┐   ┌───────┬───────┼───────┼───────┼───────┼───────┼───────┼───────┤
│ Globe │   ×   │   ×   │ Accrd │   ×   │   ×   │   ×   │   ×   │   │   ×   │   ×   │  F9   │  F10  │  F11  │  F12  │   ×   │   ×   │
└───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘   └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
                        ┌───────┬───────┬───────┬───────┬───────┐   ┌───────┬───────┬───────┬───────┬───────┐
                        │   ·   │   ×   │   ×   │   ×   │ Caps  │   │  F24  │   ×   │   ×   │   ×   │   ×   │
                        └───────┴───────┴───────┴───────┴───────┘   └───────┴───────┴───────┴───────┴───────┘
```

- The window keys send AeroSpace's Ctrl+Alt chords. W/A/S/D move focus, Q returns to
  the previous workspace, E focuses the next monitor, R toggles tiles, C toggles
  accordion and F toggles fullscreen.
- **Boot** puts the half it sits on into the bootloader. The dongle has no key; double-tap
  its reset button.
- **BT1–BT5**, **BTClr** and **USB/BLE** control the dongle's connection to the host.
- **Studio** unlocks [ZMK Studio](https://zmk.studio) on the dongle.
- **Globe** is the raw macOS Globe/Fn key for emoji, dictation and manual chords.

## AeroSpace

Hold the Hyper/WM thumb and press any key to send it with Ctrl+Alt; add Shift to move
instead of focus. With AeroSpace's bindings from `~/.nix/aerospace.nix`:

| Hold WM thumb + | Action |
|-----------------|--------|
| `h` `j` `k` `l` | Focus (with Shift: move) in that direction |
| `t` `z` `b` `a` `c` `m` `n` `1`–`4` | Go to (with Shift: send the window to) that workspace |
| `Tab` | Previous workspace |
| `o` | Next monitor (with Shift: send the window there) |
| `/` `,` | Tiles or accordion layout |
| `f` | Fullscreen (with Shift: toggle floating) |
| `-` `=` | Shrink or grow the window |
| `r` / `;` | Resize mode / service mode |

## Build

GitHub Actions builds every target in `build.yaml` on each push. Pushes to `latest`
also create a release with all `.uf2` files; the version bump follows the commit message
(`feat` = minor, `breaking` = major, otherwise patch).

Build locally with Apple `container`:

```nu
nu scripts/build.nu
```

The `.uf2` files land in `firmware/`. The first run downloads the ZMK and Zephyr sources
into `.zmk-workspace/`; later runs reuse it.

## Flash

Double-tap a controller's reset button to mount it as `HALCYON`, then copy the `.uf2`
onto it.

**First flash, or after changing controllers or adding the dongle:**

1. Flash `settings_reset_dongle.uf2` to the dongle and `settings_reset_wireless.uf2` to
   each half.
2. Flash `elora_dongle.uf2`, `elora_left.uf2` and `elora_right.uf2`.
3. Press the reset button on each half once after flashing; skipping it drains the coin
   cell much faster.

**Keymap changes** only need `elora_dongle.uf2`. Edits made in ZMK Studio are stored on
the dongle and override the compiled keymap until you choose *Restore Stock Settings* in
Studio.
