# README Elora Layout Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Replace the README's abbreviated layer rows with accurate, aligned Elora Rev2 keyboard diagrams.

**Architecture:** Use one fixed-width Unicode box-drawing silhouette for every accessible layer. Populate each physical position directly from the five physical argument groups in the corresponding `LAYOUT(...)` definition, with concise prose below each diagram for actions that cannot fit inside a key cell.

**Tech Stack:** Markdown, monospace Unicode box drawing, QMK C keymap definitions

## Global Constraints

- Show two 6-key main halves across four rows.
- Show four inner keys and two 5-key thumb clusters; do not draw nonphysical legacy module-button slots.
- Use `·` only for `KC_TRNS` and `×` only for `KC_NO`.
- Document complete diagrams for QWERTY, Navigation, Symbols, and Function.
- Treat `firmware/keyboards/splitkb/halcyon/elora/keymaps/denis/keymap.c` as authoritative.

---

### Task 1: Draw and Validate the Accessible Layers

**Files:**
- Modify: `README.md`
- Reference: `firmware/keyboards/splitkb/halcyon/elora/keymaps/denis/keymap.c:69`
- Test: Markdown code-block and key-position validation commands

**Interfaces:**
- Consumes: The five physical `LAYOUT(...)` argument groups for layers 0, 3, 4, and 5.
- Produces: Four complete diagrams sharing the same physical outline and legend.

- [x] **Step 1: Record the existing abbreviated diagrams as the failing documentation check**

Run:

```bash
rg -n '^· · ·|^× × ×|Module keys:' README.md
```

Expected: matches proving that Navigation, Symbols, and Function are abbreviated rather than full Elora drawings.

- [x] **Step 2: Replace all four diagrams with the approved silhouette**

For every layer, draw:

```text
6 left keys                         6 right keys
6 left keys                         6 right keys
6 left keys                         6 right keys
6 left + 2 inner keys   2 inner + 6 right keys
             5 left thumbs   5 right thumbs
```

Use fixed seven-character key cells and populate positions in source order. Keep long explanations such as Control+Globe and Hyper+arrow below the Function diagram.

- [x] **Step 3: Verify the abbreviations are gone and all four diagrams are present**

Run:

```bash
rg -n '^### Layer (0|3|4|5)|^· · ·|^× × ×|Module keys:' README.md
```

Expected: four layer headings; no abbreviated row or `Module keys:` matches.

- [x] **Step 4: Compare labels against the QMK source**

Run:

```bash
sed -n '69,132p' firmware/keyboards/splitkb/halcyon/elora/keymaps/denis/keymap.c
sed -n '80,260p' README.md
```

Expected: each diagram contains 12, 12, 12, 16, and 10 physical key positions corresponding to the five QMK argument groups; transparent and disabled positions use the correct legend symbol.

- [x] **Step 5: Review the final diff**

Run:

```bash
git diff --check
git diff -- README.md
```

Expected: no whitespace errors; README mapping and prose match current firmware without references to the removed Leader/System mapping.
