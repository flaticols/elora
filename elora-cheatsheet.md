# Elora Rev2 — Optimized Layout Cheatsheet

## Layer 0 — Base (QWERTY + Home Row Mods)

```
LEFT (outer → inner)                          RIGHT (inner → outer)
┌─────┬─────┬─────┬─────┬─────┬─────┐        ┌─────┬─────┬─────┬─────┬─────┬─────┐
│  `  │  1  │  2  │  3  │  4  │  5  │        │  6  │  7  │  8  │  9  │  0  │  =  │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│ Tab │  Q  │  W  │  E  │  R  │  T  │        │  Y  │  U  │  I  │  O  │  P  │ Bks │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│C/Esc│ G/A │ A/S │ C/D │ S/F │  G  │        │  H  │ S/J │ C/K │ A/L │ G/; │ C/' │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│LSft │  Z  │  X  │  C  │  V  │  B  │        │  N  │  M  │  ,  │  .  │  /  │RSft │
└─────┴─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┴─────┘
            │ MO3 │ Del │Hyper│TD:Tb│TD:Es│TD:Sp│  │TD:Bs│ RGui│ RCtl│ Ent │  -  │ MO4 │
            └─────┴─────┴─────┴─────┘─────┘─────┘  └─────┴─────┴─────┴─────┴─────┴─────┘
```

Home row mods (tap/hold): **G**UI, **A**lt, **C**trl, **S**hift (GACS for macOS)

**Del** = Forward delete. **Hyper** = Cmd+Ctrl+Alt+Shift (bind app shortcuts to Hyper+key in Kitty/Zed/Raycast)

### Tap Dances

| Key    | Tap       | Hold      | Double-tap   |
|--------|-----------|-----------|--------------|
| TD:Sp  | Space     | → Layer 1 | Toggle L1    |
| TD:Bs  | Backspace | → Layer 2 | Toggle L2    |
| TD:Es  | Escape    | Ctrl      | —            |
| TD:Tb  | Tab       | → Layer 5 | —            |

---

## Layer 1 — Navigation (hold Space)

```
LEFT                                          RIGHT
┌─────┬─────┬─────┬─────┬─────┬─────┐        ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │        │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ ⌘`  │ ^←  │ ^→  │ ^↑  │ ^↓  │        │Home │PgDn │PgUp │ End │ Ins │ Del │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │        │  ←  │  ↓  │  ↑  │  →  │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │⌘N  │⌘T  │⌘W  │⌘[  │⌘]  │        │ ⌥←  │ ⌥↓  │ ⌥↑  │ ⌥→  │     │     │
└─────┴─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┴─────┘
```

**Key insight**: Home row is transparent → use left home row mods WITH right arrows:
- Hold A (⌘) + → = **⌘→** (end of line)
- Hold S (⌥) + → = **⌥→** (next word)
- Hold F (⇧) + → = **⇧→** (select right)
- Hold A+F (⌘⇧) + → = **⌘⇧→** (select to end of line)

Left top row: macOS Spaces (^← ^→), Mission Control (^↑), App Exposé (^↓), Cycle Windows (⌘`)
Left bottom row: New Window (⌘N), New Tab (⌘T), Close Tab (⌘W), Back (⌘[), Forward (⌘])
Right bottom row: Word movement (⌥+arrows)

---

## Layer 2 — Symbols (hold Backspace)

```
LEFT                                          RIGHT
┌─────┬─────┬─────┬─────┬─────┬─────┐        ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │        │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  !  │  @  │  #  │  $  │  %  │        │  ^  │  &  │  *  │  +  │  =  │ Del │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  `  │  <  │  {  │  [  │  (  │        │  _  │  -  │  /  │  \  │  |  │  "  │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  ~  │  >  │  }  │  ]  │  )  │        │  :  │  ;  │  ?  │     │     │     │
└─────┴─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┴─────┘
```

**Pattern**: Left hand = brackets (open on home, close below). Right hand = operators.
Common combos for coding: `->` `=>` `!=` `==` `<=` `>=` `::` `|>` `&&` `||`

---

## Layer 3 — F-Keys + Media (hold MO3, outer left thumb)

```
LEFT                                          RIGHT
┌─────┬─────┬─────┬─────┬─────┬─────┐        ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ F11 │ F1  │ F2  │ F3  │ F4  │ F5  │        │ F6  │ F7  │ F8  │ F9  │ F10 │ F12 │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │ Bri↑│ Bri↓│     │     │        │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │ ⏮  │ ⏯  │ ⏭  │     │        │     │ Vol↓│ Vol↑│ Mute│     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │        │     │     │     │     │     │     │
└─────┴─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┴─────┘
```

---

## Layer 4 — Mouse (hold MO4, outer right thumb)

```
LEFT                                          RIGHT
┌─────┬─────┬─────┬─────┬─────┬─────┐        ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │        │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │        │Scr← │Scr↓ │Scr↑ │Scr→ │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │ Mid │Right│Left │     │        │ Ms← │ Ms↓ │ Ms↑ │ Ms→ │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │Acl2 │Acl1 │Acl0 │     │        │     │     │     │     │     │     │
└─────┴─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┴─────┘
```

Acl0/1/2 = mouse acceleration: slow/medium/fast

---

## Layer 5 — System (hold Tab via TD3)

```
LEFT                                          RIGHT
┌─────┬─────┬─────┬─────┬─────┬─────┐        ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │        │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │⌘⇧3 │⌘⇧4 │⌘⇧5 │        │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │        │ ^←  │ ^↓  │ ^↑  │ ^→  │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │        │ ⌘H  │ ⌘M  │ ⌘Q  │     │     │     │
└─────┴─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┴─────┘
```

Left: Screenshots (⌘⇧3=full, ⌘⇧4=area, ⌘⇧5=panel)
Right home: Spaces navigation. Bottom: Hide(⌘H), Minimize(⌘M), Quit(⌘Q)

---

## Encoders

| Layer | Left Main  | Left 2nd   | Right Main | Right 2nd     |
|-------|------------|------------|------------|---------------|
| 0     | Volume     | Prev/Next  | Page ↑↓    | Prev/Next Tab |
| 1     | Brightness | —          | Arrow ↑↓   | Arrow ←→      |
| 4     | Scroll ←→  | —          | Scroll ↑↓  | Mouse ←→      |

---

## Helix/Zed Workflow Tips

The layout is designed to complement Helix modal editing:

- **Normal mode navigation**: use Helix's built-in `h/j/k/l`, `w/b`, `f/t`, `g` goto
- **System navigation (Layer 1)**: arrows + home row mods = full macOS movement with selection
- **Coding symbols (Layer 2)**: all brackets on left hand, operators on right
- **Quick escape**: TD(2) tap = Esc (return to normal mode), hold = Ctrl
- **Terminal (Kitty)**: use Layer 1 for tab management (⌘T, ⌘W, ⌘N)
- **Toggle layers**: double-tap Space (nav) or Backspace (symbols) to lock layer for extended use
