# Elora Rev2 — Custom QMK Firmware

[![Latest Release](https://img.shields.io/github/v/release/flaticols/elora)](https://github.com/flaticols/elora/releases/latest)

Custom QMK firmware for a [splitkb Elora Rev2](https://splitkb.com/products/elora) (Halcyon series) split keyboard with RP2040 controller. Left half has a TFT display module. Optimized for macOS with Helix/Zed editors.

## Features

- **TFT display** (left half) — layer name, held modifiers, one-shot modifiers, LOCK, CAPS, RGB
- **Per-key RGB** — optional, off by default, toggle with RM_TOGG; active keys glow in layer color
- **Leader key** (both halves) for layer locking
- **One-shot Hyper** (Cmd+Ctrl+Alt+Shift) for app shortcuts via Raycast/Kitty/Zed
- **5 layers**: Base, Navigation, Symbols, F-keys+Media, System
- **Caps Word** support

## Special Keys

| Key | Location | Tap | Hold |
|-----|----------|-----|------|
| Space | Left thumb | Space | Nav layer |
| Backspace | Right thumb | Backspace | Symbols layer |
| Tab | Top-left | Tab | System layer |
| Escape | Left home row | Escape | Left Ctrl |
| Del | Top-right | Forward delete | — |
| ' " | Right home row | Quote | — |
| LShift | Bottom-left | Left Shift | — |
| RShift | Bottom-right | Right Shift | — |
| CapsWord | Left thumb (outer) | Toggle Caps Word | — |
| LOpt | Left thumb | Left Option | — |
| LCmd | Left thumb | Left Cmd | — |
| Hyper | Left thumb (inner) | One-shot Hyper | — |
| Enter | Right thumb | Enter/Return | — |
| RCmd | Right thumb | Right Cmd | — |
| ROpt | Right thumb | Right Option | — |
| RCtl | Right thumb | Right Ctrl | — |
| Leader | Left/Right inner | Start leader sequence | — |
| MO3 | Left inner | — | F-Keys layer |

### Leader Key Sequences

| Sequence | Action |
|----------|--------|
| Leader → Space | Toggle Nav layer lock |
| Leader → Backspace | Toggle Symbols layer lock |
| Leader → F | Toggle F-Keys layer lock |
| Leader → Tab | Toggle System layer lock |

Locked layers stay active until toggled off with the same sequence. The TFT display shows "LOCK" when a layer is locked.

### RGB Backlight

Per-key backlight is **off by default**. Press `RM_TOGG` to toggle. When enabled:
- Active keys glow in layer color (cyan=Nav, purple=Symbols, red=F-keys, green=System)
- Base layer keeps all LEDs off
- Underglow LEDs are always off (TFT display handles layer indication)
- Display shows "RGB" when backlight is on

### TFT Display (Left Half)

Shows from top to bottom:
1. **Layer name** — current active layer (Base, Nav, Symbols, F-Keys, System)
2. **LEAD** — shown while leader sequence is active
3. **LOCK** — shown when the current layer is locked via Leader sequence
4. **Held modifiers** — shows active modifiers (GUI, ALT, CTL, SFT, or HYPER when all four)
5. **One-shot modifiers** — shows armed one-shot modifier state (e.g. after tapping Hyper)
6. **CAPS** — shown when Caps Word is active
7. **RGB** — shown when per-key backlight is enabled

## Layout

### Layer 0 — Base (QWERTY)

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│  `  │  1  │  2  │  3  │  4  │  5  │                              │  6  │  7  │  8  │  9  │  0  │  =  │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│Tb/Sy│  Q  │  W  │  E  │  R  │  T  │                              │  Y  │  U  │  I  │  O  │  P  │ Del │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│C/Esc│  A  │  S  │  D  │  F  │  G  │                              │  H  │  J  │  K  │  L  │  ;  │  '  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│L⇧   │  Z  │  X  │  C  │  V  │  B  │Lead │ MO3 │  │OSL1 │Lead │  N  │  M  │  ,  │  .  │  /  │  R⇧ │
└─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
                  │CapsW│LOpt │LCmd │Sp/Nv│Hyper│  │Bs/Sm│Enter│RCmd │ROpt │RCtl │
                  └─────┴─────┴─────┴─────┴─────┘  └─────┴─────┴─────┴─────┴─────┘
┌─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┐
│LAlt │     │     │     │     │  MODULE ROW                   │OSL2 │     │     │     │     │
└─────┴─────┴─────┴─────┴─────┘                              └─────┴─────┴─────┴─────┴─────┘
```

| Area | Key | Tap | Hold |
|------|-----|-----|------|
| Top left | Tb/Sy | Tab | System layer (4) |
| Top right | Del | Forward delete | — |
| Home row L | C/Esc | Escape | Left Ctrl |
| Home row R | ' | Quote | — |
| Bottom-left | L⇧ | Left Shift | — |
| Bottom-right | R⇧ | Right Shift | — |
| Inner L | Lead | Start leader sequence | — |
| Inner L | MO3 | — | F-Keys layer (3) |
| Inner R | OSL1 | One-shot Nav layer | — |
| Inner R | Lead | Start leader sequence | — |
| Thumb L | CapsW | Toggle Caps Word | — |
| Thumb L | LOpt | Left Option | — |
| Thumb L | LCmd | Left Cmd | — |
| Thumb L | Sp/Nv | Space | Nav layer (1) |
| Thumb L | Hyper | One-shot Hyper (⌘⌃⌥⇧) | — |
| Thumb R | Bs/Sm | Backspace | Symbols layer (2) |
| Thumb R | Enter | Enter/Return | — |
| Thumb R | RCmd | Right Cmd | — |
| Thumb R | ROpt | Right Option | — |
| Thumb R | RCtl | Right Ctrl | — |
| Module L | LAlt | Left Alt/Option | — |
| Module R | OSL2 | One-shot Symbols layer | — |

### Layer 1 — Navigation (hold Space)

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ ⌘`  │ ^←  │ ^→  │ ^↑  │ ^↓  │                              │Home │PgDn │PgUp │ End │ Ins │ Bsp │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │                              │  ←  │  ↓  │  ↑  │  →  │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │ ⌘N  │ ⌘T  │ ⌘W  │ ⌘[  │ ⌘]  │     │     │  │     │     │ ⌥←  │ ⌥↓  │ ⌥↑  │ ⌥→  │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │     │█████│     │  │     │     │     │     │     │
                  └─────┴─────┴─────┴─────┴─────┘  └─────┴─────┴─────┴─────┴─────┘
```

Left: ⌘` app switch, ^←/→ Spaces, ^↑/↓ Mission Control. ⌘N/T/W new/tab/close, ⌘[/] back/forward.

Right: HJKL arrows, Home/End/PgUp/PgDn. ⌥arrows = word/paragraph movement.

### Layer 2 — Symbols (hold Backspace)

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  !  │  @  │  #  │  $  │  %  │                              │  ^  │  &  │  *  │  +  │  =  │ Bsp │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  `  │  <  │  {  │  [  │  (  │                              │  _  │  -  │  /  │  \  │  |  │  "  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │  ~  │  >  │  }  │  ]  │  )  │     │     │  │     │     │  :  │  ;  │  ?  │     │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │     │     │     │  │█████│     │     │     │     │
                  └─────┴─────┴─────┴─────┴─────┘  └─────┴─────┴─────┴─────┴─────┘
```

Left hand = brackets (open on home row, close below). Right hand = operators. No shift needed for any symbol.

### Layer 3 — F-Keys + Media (hold MO3)

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ F11 │ F1  │ F2  │ F3  │ F4  │ F5  │                              │ F6  │ F7  │ F8  │ F9  │ F10 │ F12 │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │ Bri↑│ Bri↓│     │     │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │  ⏭  │  ⏯  │  ⏮  │     │                              │     │ Vol↓│ Vol↑│Mute │ RGB │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │█████│  │     │     │     │     │     │     │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │     │     │     │  │     │     │     │     │     │
                  └─────┴─────┴─────┴─────┴─────┘  └─────┴─────┴─────┴─────┴─────┘
```

RGB = `RM_TOGG` (toggle per-key backlight on/off). F-keys row mirrors number row positions.

### Layer 4 — System (hold Tab)

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │ ⌘⇧3 │ ⌘⇧4 │ ⌘⇧5 │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │                              │ ^←  │ ^↓  │ ^↑  │ ^→  │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │  │     │     │ ⌘H  │ ⌘M  │ ⌘Q  │     │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │█████│     │     │  │     │     │     │     │     │
                  └─────┴─────┴─────┴─────┴─────┘  └─────┴─────┴─────┴─────┴─────┘
```

Screenshots: ⌘⇧3 full screen, ⌘⇧4 area select, ⌘⇧5 screenshot panel. Spaces: ^← /→ switch, ^↓/↑ Mission Control/App Expose. Window: ⌘H hide, ⌘M minimize, ⌘Q quit.

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
