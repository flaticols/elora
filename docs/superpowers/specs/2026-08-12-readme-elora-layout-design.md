# README Elora Layout Diagram Design

## Goal

Replace the README's compact key lists with readable monospace diagrams that accurately preserve the physical Elora Rev2 layout and the current QMK mapping.

## Diagram Structure

Each documented layer uses the same keyboard silhouette:

- two 6-key main halves across four rows;
- the four inner keys shown between the bottom main rows;
- two 5-key thumb clusters, separated by the split;
- two 5-key module rows below the thumb clusters.

Every cell has a fixed width so borders and corresponding physical positions align across layers. Labels favor familiar key names and macOS symbols while remaining short enough to fit.

## Layers

Draw complete diagrams for the layers users can access from QWERTY:

1. Layer 0 — QWERTY
2. Layer 3 — Navigation
3. Layer 4 — Symbols
4. Layer 5 — Function and macOS window management

Dvorak, Colemak, and reserved layers remain a concise note because the current QWERTY mapping cannot enter them.

## Legend and Accuracy

- `·` means `KC_TRNS`, so the key falls through to a lower layer.
- `×` means `KC_NO`, so the key is intentionally disabled.
- Dual-role base keys show both actions with short labels such as `Tab/Fn`, `Esc/Ctl`, `Bs/Sym`, and `Sp/Nav`.
- The diagram positions come directly from each `LAYOUT_elora_hlc(...)` argument in `keymap.c`; prose does not invent or reinterpret mappings.

## Validation

Check each diagram row against the corresponding QMK layer argument count: 12 top-row keys, 12 second-row keys, 12 home-row keys, 16 bottom-row/inner keys, 10 thumb keys, and 10 module keys. Render the Markdown as plain monospace text and verify that all border junctions align.
