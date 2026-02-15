# Elora Rev2 — Custom Firmware & Layout Requirements

## Hardware

pp

- Keyboard: splitkb Elora Rev2 (Halcyon series)
- Controller: RP2040
- No rotary encoders installed
- Two extra physical keys in thumb cluster area (where encoders would be)
- Per-key RGB + underglow LEDs
- Firmware: Vial (halcyon branch of splitkb/qmk_userspace)

## Layout Requirements

### Layer 0 — Base (QWERTY)

- Home row mods (GACS order for macOS): GUI on A/;, Alt on S/L, Ctrl on D/K, Shift on F/J
- Minus and equals accessible on layer 0 (minus on right thumb, equals on outer right number row)
- Tap dances on thumb keys:
  - Space: tap=Space, hold=Nav layer, double-tap=toggle Nav
  - Backspace: tap=Backspace, hold=Symbols layer, double-tap=toggle Symbols
  - Escape: tap=Esc, hold=Ctrl
  - Tab: tap=Tab, hold=System layer
- Extra thumb keys: Delete, Hyper (Cmd+Ctrl+Alt+Shift)
- Extra center buttons: Hyper (left), OSL(2) one-shot symbols (right)
- Inner bottom keys: KC_APPLICATION (left, placeholder for Hyper), KC_PAUSE (right, placeholder for OSL(1))

### Layer 1 — Navigation (hold Space)

- Right home row: arrow keys (HJKL)
- Right top row: Home, PgDn, PgUp, End, Ins, Del
- Right bottom row: word movement (Alt+arrows)
- Left home row: transparent (use base home row mods + right arrows for combos like Cmd+Right, Shift+Right)
- Left top row: macOS Spaces navigation (Ctrl+arrows), Cmd+` (cycle windows)
- Left bottom row: tab management (Cmd+N, Cmd+T, Cmd+W, Cmd+[, Cmd+])

### Layer 2 — Symbols (hold Backspace)

- Left top: ! @ # $ %
- Left home: ` < { [ (
- Left bottom: ~ > } ] )
- Right top: ^ & \* + = Del
- Right home: \_ - / \ | "
- Right bottom: : ; ?
- All symbols needed for software engineering accessible without Shift

### Layer 3 — F-Keys + Media (hold MO3)

- F1-F12 on number row positions
- Media controls: prev/play/next on left home, vol down/up/mute on right home
- Brightness up/down on left top row

### Layer 4 — Mouse (hold MO4)

- Right home row: mouse movement (HJKL pattern)
- Right top row: scroll wheel (left/down/up/right)
- Left home row: mouse buttons (left/right/middle click)
- Left bottom row: acceleration control (ACL0/1/2 for slow/medium/fast)

### Layer 5 — System (hold Tab)

- Left top: macOS screenshots (Cmd+Shift+3/4/5)
- Right home: Spaces navigation (Ctrl+arrows)
- Right bottom: Hide (Cmd+H), Minimize (Cmd+M), Quit (Cmd+Q)

### Layers 6-7

- Transparent (reserved for future use)

## Firmware Requirements

### Home Row Mods Fix

- Problem: accidental Cmd+S when typing "as" fast (ghost modifier activation)
- Solution: Chordal hold (bilateral combinations) — same hand = always tap, opposite hand = hold
- TAPPING_TERM 200ms global, 220ms for home row mods specifically
- QUICK_TAP_TERM 0 (disable quick tap to prevent accidental mod on fast double-tap)
- PERMISSIVE_HOLD for opposite-hand cases

### RGB Backlight

- **Must always be controlled by active layer — no user toggle, no manual RGB control**
- All RGB keycodes (TOG, MOD, HUI, etc.) must be blocked/swallowed
- RGB forced on at boot, re-enabled if somehow disabled
- Behavior: only keys that are ACTIVE on the current layer light up white
- KC_TRNS and KC_NO keys = LED off
- Base layer (0) = all LEDs off
- Non-base layers = active keys glow white, rest dark
- No per-layer color configuration needed — reads keymap dynamically
- If layout changes in Vial, LEDs automatically follow without firmware recompile

### Mouse Keys

- 3-speed momentary acceleration
- Tuned speed intervals for precise and fast movement

## Target Apps (macOS)

- Helix (terminal editor, modal editing)
- Zed (GUI editor, helix keybinding mode)
- Kitty (terminal emulator)
- Layout designed to complement Helix modal editing, not replace it

## Build

- Use splitkb/qmk_userspace repo, `halcyon` branch (Vial firmware)
- Custom keymap at `keyboards/splitkb/halcyon/elora/keymaps/denis/`
- No Halcyon modules needed (no encoders, no display, no trackpad)
- Flash via RP2040 bootloader (double-tap reset → drag .uf2)

## Files

- `elora.vil` — working Vial config (manually synced)
- `elora-optimized.vil` — generated optimized Vial config
- `elora-cheatsheet.md` — visual layout reference
- `firmware/keyboards/splitkb/halcyon/elora/keymaps/denis/config.h` — QMK config
- `firmware/keyboards/splitkb/halcyon/elora/keymaps/denis/keymap.c` — RGB + HRM + chordal hold
- `firmware/keyboards/splitkb/halcyon/elora/keymaps/denis/rules.mk` — build flags
- `firmware/BUILD.md` — compilation instructions
