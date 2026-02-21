# Elora Rev2 — Custom QMK Firmware

[![Latest Release](https://img.shields.io/github/v/release/flaticols/elora)](https://github.com/flaticols/elora/releases/latest)

Custom QMK firmware for a [splitkb Elora Rev2](https://splitkb.com/products/elora) (Halcyon series) split keyboard with RP2040 controller. Left half has a TFT display module, right half has a Cirque trackpad. Optimized for macOS with Helix/Zed editors.

## Features

- **Home row mods** (GACS order) with chordal hold to prevent same-hand misfires
- **TFT display** (left half) — layer name, held modifiers, one-shot modifiers, LOCK, CAPS, RGB
- **Cirque trackpad** (right half) — tap-to-click, scroll gestures, cursor glide, auto-mouse layer
- **Per-key RGB** — optional, off by default, toggle with RM_TOGG; active keys glow in layer color
- **Leader key** for layer locking (Leader+Space=Nav, Leader+Bksp=Symbols, Leader+Tab=System)
- **One-shot Hyper** (Cmd+Ctrl+Alt+Shift) for app shortcuts via Raycast/Kitty/Zed
- **6 layers**: Base, Navigation, Symbols, F-keys+Media, Mouse, System
- **Caps Word** support

## Special Keys

| Key | Location | Tap | Hold |
|-----|----------|-----|------|
| Space | Left thumb | Space | Nav layer |
| Backspace | Right thumb | Backspace | Symbols layer |
| Tab | Left thumb | Tab | System layer |
| Escape | Left home row | Escape | Left Ctrl |
| Escape | Top-right corner | Escape (dedicated, instant) | — |
| ' " | Right home row | Quote | Right Ctrl |
| Home row A/S/D/F | Left home row | Letter | GUI/Alt/Ctrl/Shift |
| Home row J/K/L/; | Right home row | Letter | Shift/Ctrl/Alt/GUI |
| ⌥⌫ | Left thumb | Word delete (Option+Backspace) | — |
| Undo | Right thumb | ⌘Z | — |
| Redo | Bottom-left | ⌘⇧Z | — |
| Del | Bottom-right | Forward delete | — |
| MO3 | Left thumb | — | F-keys + Media layer |
| MO4 | Right thumb | — | Mouse layer |
| OSL3 | Right thumb | One-shot F-Keys layer | — |
| OSL5 | Right thumb | One-shot System layer | — |
| CapsWord | Left inner | Toggle Caps Word | — |
| Hyper | Left inner | One-shot Hyper | — |
| Leader | Left thumb | Start leader sequence | — |

### Leader Key Sequences

| Sequence | Action |
|----------|--------|
| Leader → Space | Toggle Nav layer lock |
| Leader → Backspace | Toggle Symbols layer lock |
| Leader → Tab | Toggle System layer lock |

Locked layers stay active until toggled off with the same sequence. The TFT display shows "LOCK" when a layer is locked.

### RGB Backlight

Per-key backlight is **off by default**. Press `RM_TOGG` to toggle. When enabled:
- Active keys glow in layer color (cyan=Nav, purple=Symbols, red=F-keys, green=Mouse, yellow=System)
- Base layer keeps all LEDs off
- Underglow LEDs are always off (TFT display handles layer indication)
- Display shows "RGB" when backlight is on

### TFT Display (Left Half)

Shows from top to bottom:
1. **Layer name** — current active layer (Base, Nav, Symbols, F-Keys, Mouse, System)
2. **LOCK** — shown when the current layer is locked via Leader sequence
3. **Held modifiers** — shows active modifiers when holding home row mod keys (GUI, ALT, CTL, SFT, or HYPER when all four)
4. **One-shot modifiers** — shows armed one-shot modifier state (e.g. after tapping OS⇧ or Hyper)
5. **CAPS** — shown when Caps Word is active
6. **RGB** — shown when per-key backlight is enabled

## Layout

### Layer 0 — Base (QWERTY + Home Row Mods)

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│  `  │  1  │  2  │  3  │  4  │  5  │                              │  6  │  7  │  8  │  9  │  0  │  =  │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│OS⇧  │  Q  │  W  │  E  │  R  │  T  │                              │  Y  │  U  │  I  │  O  │  P  │ Esc │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│C/Esc│ G/A │ A/S │ C/D │ S/F │  G  │                              │  H  │ S/J │ C/K │ A/L │ G/; │ C/' │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│Redo │  Z  │  X  │  C  │  V  │  B  │CapsW│Hyper│  │OSL1 │Enter│  N  │  M  │  ,  │  .  │  /  │ Del │
└─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
                  │Lead │ ⌥⌫  │Tb/Sy│Sp/Nv│ MO3 │  │Bs/Sm│ MO4 │Undo │OSL3 │OSL5 │
                  └─────┴─────┴─────┴─────┴─────┘  └─────┴─────┴─────┴─────┴─────┘
┌─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┐
│LAlt │     │     │     │     │  MODULE ROW                   │OSL2 │     │     │     │     │
└─────┴─────┴─────┴─────┴─────┘                              └─────┴─────┴─────┴─────┴─────┘
```

| Area | Key | Tap | Hold |
|------|-----|-----|------|
| Home row | G/A, A/S, C/D, S/F | Letter | GUI, Alt, Ctrl, Shift |
| Home row | S/J, C/K, A/L, G/; | Letter | Shift, Ctrl, Alt, GUI |
| Home row | C/Esc | Escape | Left Ctrl |
| Home row | C/' | Quote | Right Ctrl |
| Top left | OS⇧ | — | One-shot Left Shift |
| Top right | Esc | Escape (dedicated, instant) | — |
| Bottom-left | Redo | ⌘⇧Z Redo | — |
| Bottom-right | Del | Forward delete | — |
| Thumb L | Lead | Start leader sequence | — |
| Thumb L | ⌥⌫ | Word delete (Option+Backspace) | — |
| Thumb L | Tb/Sy | Tab | System layer (5) |
| Thumb L | Sp/Nv | Space | Nav layer (1) |
| Thumb L | MO3 | — | F-Keys layer (3) |
| Thumb R | Bs/Sm | Backspace | Symbols layer (2) |
| Thumb R | MO4 | — | Mouse layer (4) |
| Thumb R | Undo | ⌘Z Undo | — |
| Thumb R | OSL3 | One-shot F-Keys layer | — |
| Thumb R | OSL5 | One-shot System layer | — |
| Inner L | CapsW | Toggle Caps Word | — |
| Inner L | Hyper | One-shot Hyper (⌘⌃⌥⇧) | — |
| Inner R | OSL1 | One-shot Nav layer | — |
| Inner R | Enter | Enter/Return | — |
| Module L | LAlt | Left Alt/Option | — |
| Module R | OSL2 | One-shot Symbols layer | — |

### Layer 1 — Navigation (hold Space)

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ ⌘`  │ ^←  │ ^→  │ ^↑  │ ^↓  │                              │Home │PgDn │PgUp │ End │ Ins │ Bsp │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ ▪   │ ▪   │ ▪   │ ▪   │     │                              │  ←  │  ↓  │  ↑  │  →  │ ▪   │ ▪   │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │ ⌘N  │ ⌘T  │ ⌘W  │ ⌘[  │ ⌘]  │     │     │  │     │     │ ⌥←  │ ⌥↓  │ ⌥↑  │ ⌥→  │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │     │█████│     │  │     │     │     │     │     │
                  └─────┴─────┴─────┴─────┴─────┘  └─────┴─────┴─────┴─────┴─────┘
```

▪ = transparent (home row mods pass through). Compose left HRM with right arrows (e.g. hold G/A + → = ⌘→ end of line, hold S/F + → = ⇧→ select right).

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
│     │     │     │     │     │     │     │     │  │     │     │     │     │     │     │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │     │     │█████│  │     │     │     │     │     │
                  └─────┴─────┴─────┴─────┴─────┘  └─────┴─────┴─────┴─────┴─────┘
```

RGB = `RM_TOGG` (toggle per-key backlight on/off). F-keys row mirrors number row positions.

### Layer 4 — Mouse (hold MO4 / trackpad auto-activate)

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │Scr← │Scr↓ │Scr↑ │Scr→ │     │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │Btn1 │Btn2 │Btn3 │     │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │Acl0 │Acl1 │Acl2 │     │     │     │  │     │     │     │     │     │     │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │     │     │     │  │     │█████│     │     │     │
                  └─────┴─────┴─────┴─────┴─────┘  └─────┴─────┴─────┴─────┴─────┘
```

Left hand controls: scroll wheel (QWER row), mouse buttons (home row), acceleration (bottom row, Acl0=slow, Acl1=medium, Acl2=fast). Right hand is on the Cirque trackpad for cursor movement.

Auto-activates on trackpad movement (650ms timeout to deactivate).

### Layer 5 — System (hold Tab)

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
#   firmware/output/elora_right_trackpad.uf2   (right half — Cirque trackpad)
```

See [firmware/BUILD.md](firmware/BUILD.md) for local QMK build instructions.

## Flash

Each half gets its own firmware — do NOT flash the same .uf2 to both sides.

1. **Left half**: double-tap reset, drag `elora_left_display.uf2` onto `RPI-RP2`
2. **Right half**: double-tap reset, drag `elora_right_trackpad.uf2` onto `RPI-RP2`
3. Connect USB to the **left** half (master)

## Releases

Pushes to `latest` that modify `firmware/**` automatically build both halves and create a GitHub release with `.uf2` artifacts attached. Version is bumped based on commit message keywords (`feat` = minor, `breaking` = major, otherwise patch).

## Links

- [REQUIREMENTS.md](REQUIREMENTS.md) — full design spec
- [firmware/BUILD.md](firmware/BUILD.md) — detailed build instructions
- [elora-cheatsheet.md](elora-cheatsheet.md) — printable layout reference
