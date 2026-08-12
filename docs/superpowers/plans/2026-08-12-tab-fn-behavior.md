# Predictable Tab/Fn Behavior Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Preserve the existing keycap positions while making Tab/Fn and thumb Fn predictable hold-only layer access, and restore builds against the current Halcyon userspace.

**Architecture:** Keep all behavior in the existing QMK keymap, port each layer from the removed `LAYOUT_elora_hlc` compatibility macro to the current 62-switch `LAYOUT` macro, and parse the declarative mapping into physical positions for an offline behavior contract test. Align every build and documentation surface around the actual hardware: TFT module on the left and no module on the right, with real QMK compiles as the build proof.

**Tech Stack:** QMK C keymap, Python 3 standard-library `unittest`, Bash, Docker, GitHub Actions, Markdown.

## Global Constraints

- Do not move any physical key or change any ordinary keycap legend.
- Far-left `Tab/Fn` remains Tab on tap and Function layer 5 on hold.
- Thumb `Fn` becomes momentary Function layer 5 access; repeated taps never latch it.
- Left module is `HLC_TFT_DISPLAY=1`; right module is `HLC_NONE=1`.
- Preserve all four encoder-map slots, including the two reserved module slots.
- Do not publish or document a Cirque firmware artifact.

---

### Task 1: Add the keymap behavior-contract regression tests

**Files:**
- Create: `firmware/tests/test_firmware_contract.py`

**Interfaces:**
- Consumes: the declarative layers and `chordal_hold_layout` in `keymap.c`.
- Produces: a `unittest` suite that parses top-level `LAYOUT(...)` arguments into physical key positions and checks the Fn behavior contract without a QMK checkout.

- [x] **Step 1: Write the failing keymap contract tests**

Create a standard-library test module with balanced-parentheses `extract_layout()` and `split_arguments()` helpers. Parse each layer into its 62 physical positions and assert:

```python
self.assertEqual(qwerty[12], "LT(_FN, KC_TAB)")
self.assertEqual(qwerty[52], "MO(_FN)")
self.assertEqual(function[12], "KC_TRNS")
self.assertEqual(function[52], "KC_TRNS")
self.assertEqual(chordal[12], "'*'")
for name, arguments in layers.items():
    self.assertEqual(len(arguments), 62, name)
self.assertEqual(len(chordal), 62)
```

- [x] **Step 2: Run the tests to verify RED**

Run: `python3 -m unittest discover -s firmware/tests -v`

Expected: failures report that current `LAYOUT(...)` mappings cannot be found because the removed legacy macro is still used. After temporarily allowing that macro in the parser, the assertions also expose `TT(5)`, masked Function-layer entry positions, and the left-handed Tab/Fn chordal assignment; revert that diagnostic allowance before implementation.

---

### Task 2: Port the keymap and implement momentary Fn access

**Files:**
- Modify: `firmware/keyboards/splitkb/halcyon/elora/keymaps/denis/keymap.c`
- Modify: `firmware/keyboards/splitkb/halcyon/elora/keymaps/denis/rules.mk`
- Test: `firmware/tests/test_firmware_contract.py`

**Interfaces:**
- Consumes: QMK's current `LAYOUT(...)`, `_FN`, `LT`, `MO`, `KC_TRNS`, and `CHORDAL_HOLD` APIs.
- Produces: eight 62-key layers and one 62-position handedness map compatible with current Halcyon userspace.

- [x] **Step 1: Replace the removed layout macro**

Change every `LAYOUT_elora_hlc(` invocation to `LAYOUT(`. Remove the final ten legacy module-button arguments from all eight keymap layers and from `chordal_hold_layout`; preserve the first 62 arguments in their existing order.

- [x] **Step 2: Implement the approved Tab/Fn behavior**

Make these exact keymap changes:

```c
LT(_FN, KC_TAB) // QWERTY argument 12
MO(_FN)         // QWERTY argument 52
KC_TRNS         // _FN argument 12
KC_TRNS         // _FN argument 52
'*'             // chordal_hold_layout argument 12
```

Update the file header from `LT5/TT5` language to `LT5/MO5`, and update `rules.mk` comments so they describe current module selection rather than claiming it defines the removed macro.

- [x] **Step 3: Run the focused tests to verify GREEN for the keymap**

Run: `python3 -m unittest firmware.tests.test_firmware_contract.KeymapContractTests -v`

Expected: all keymap behavior-contract cases pass.

---

### Task 3: Align local and CI builds with TFT-left/no-module-right hardware

**Files:**
- Modify: `firmware/build.sh`
- Modify: `firmware/Dockerfile`
- Modify: `.github/workflows/firmware.yml`
- Modify: `firmware/BUILD.md`

**Interfaces:**
- Consumes: QMK module environment flags and the existing Docker build flow.
- Produces: `elora_left_display.uf2` and `elora_right.uf2` from both local and GitHub Actions builds.

- [x] **Step 1: Fix the right-half build commands and artifacts**

Use this command for every right-half compile:

```bash
qmk compile -kb splitkb/halcyon/elora/rev2 -km denis -e HLC_NONE=1
```

Copy and release the artifact as `elora_right.uf2`. Remove every `HLC_CIRQUE_TRACKPAD` and `elora_right_trackpad.uf2` reference. Keep the left build on `HLC_TFT_DISPLAY=1`.

- [x] **Step 2: Rewrite BUILD.md to match the repository**

Document the current features and the two exact compile commands. Flash `elora_left_display.uf2` on the left and `elora_right.uf2` on the right; remove stale Cirque, mouse-layer, obsolete Vial-file, and old layer-color claims.

- [x] **Step 3: Check build-script syntax**

Run: `bash -n firmware/build.sh`

Expected: the shell parser exits 0. The real left and right QMK builds in Task 4 are the behavioral verification for module selection.

---

### Task 4: Update the README mapping and verify the complete firmware

**Files:**
- Modify: `README.md`
- Modify: `docs/superpowers/plans/2026-08-12-tab-fn-behavior.md`
- Test: `firmware/tests/test_firmware_contract.py`

**Interfaces:**
- Consumes: the implemented 62-switch mapping and build artifact names.
- Produces: a layout reference matching the firmware and a checked implementation plan.

- [x] **Step 1: Update Fn documentation without moving legends**

Change `Fn tap-toggle` to `Fn`, document it as hold-only, and remove all five-tap language. Rename `Fn TT` in the QWERTY thumb row to `Fn`. In the Function-layer drawing, show the Tab/Fn and thumb Fn positions as `·` because they are transparent on `_FN`.

- [x] **Step 2: Remove legacy module-button rows from every layer drawing**

Delete the explanatory legacy-slot paragraph and the separate ten-slot box below QWERTY, Navigation, Symbols, and Function. Retain the four-slot encoder table and its explicit physical/reserved status.

- [x] **Step 3: Run all offline checks**

Run:

```bash
python3 -m unittest discover -s firmware/tests -v
git diff --check
```

Expected: all tests pass and `git diff --check` exits with no output.

- [x] **Step 4: Build both firmware halves from a fresh image**

Run:

```bash
docker build -t elora-firmware-review firmware
docker run --rm elora-firmware-review qmk compile -kb splitkb/halcyon/elora/rev2 -km denis -e HLC_TFT_DISPLAY=1
docker run --rm elora-firmware-review qmk compile -kb splitkb/halcyon/elora/rev2 -km denis -e HLC_NONE=1
```

Expected: both QMK commands exit 0 and report a successful firmware size check.

- [ ] **Step 5: Review, commit, and push**

Confirm only intended files are staged, set `user.email` locally to `gh@flaticols.dev`, preserve the repository's existing local `user.name` or current commit author name, then commit:

```bash
git config --local user.email gh@flaticols.dev
git add .gitignore README.md .github/workflows/firmware.yml firmware docs/superpowers/plans
git commit -m "fix: make Elora Fn access predictable"
git push
```

Before pushing, inspect `git diff --cached --check`, `git diff --cached --stat`, `git status --short`, and the outgoing commit range. After pushing, verify the local branch matches its upstream.

Manual post-flash checks remain: Tab sends one Tab; Tab/Fn plus W invokes Top; thumb Fn exposes F-keys/window actions only while held; neither Fn entry key leaves layer 5 latched.
