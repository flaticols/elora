from pathlib import Path
import unittest


REPOSITORY_ROOT = Path(__file__).resolve().parents[2]
KEYMAP_PATH = (
    REPOSITORY_ROOT
    / "firmware/keyboards/splitkb/halcyon/elora/keymaps/denis/keymap.c"
)
LAYER_NAMES = (
    "_QWERTY",
    "_DVORAK",
    "_COLEMAK",
    "_NAV",
    "_SYM",
    "_FN",
    "_L6",
    "_L7",
)


def extract_parenthesized(source: str, opening_parenthesis: int) -> str:
    depth = 1
    for index in range(opening_parenthesis + 1, len(source)):
        character = source[index]
        if character == "(":
            depth += 1
        elif character == ")":
            depth -= 1
            if depth == 0:
                return source[opening_parenthesis + 1 : index]
    raise AssertionError("LAYOUT invocation has no closing parenthesis")


def split_arguments(arguments: str) -> list[str]:
    result = []
    start = 0
    depth = 0
    for index, character in enumerate(arguments):
        if character == "(":
            depth += 1
        elif character == ")":
            depth -= 1
        elif character == "," and depth == 0:
            result.append(arguments[start:index].strip())
            start = index + 1
    result.append(arguments[start:].strip())
    return result


def extract_layout_after(source: str, marker: str) -> tuple[str, list[str]]:
    marker_index = source.find(marker)
    if marker_index < 0:
        raise AssertionError(f"mapping marker not found: {marker}")

    current_macro = source.find("LAYOUT(", marker_index + len(marker))
    legacy_macro = source.find("LAYOUT_elora_hlc(", marker_index + len(marker))
    candidates = [
        (index, macro)
        for index, macro in (
            (current_macro, "LAYOUT"),
            (legacy_macro, "LAYOUT_elora_hlc"),
        )
        if index >= 0
    ]
    if not candidates:
        raise AssertionError(f"LAYOUT invocation not found after: {marker}")

    macro_index, macro = min(candidates)
    opening_parenthesis = source.find("(", macro_index)
    arguments = extract_parenthesized(source, opening_parenthesis)
    return macro, split_arguments(arguments)


class KeymapContractTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.keymap = KEYMAP_PATH.read_text()
        mappings = {
            name: extract_layout_after(cls.keymap, f"[{name}] = ")
            for name in LAYER_NAMES
        }
        cls.layer_macros = {name: mapping[0] for name, mapping in mappings.items()}
        cls.layers = {name: mapping[1] for name, mapping in mappings.items()}
        cls.chordal_macro, cls.chordal = extract_layout_after(
            cls.keymap, "chordal_hold_layout"
        )

    def test_layers_match_current_62_switch_layout(self) -> None:
        for name, arguments in self.layers.items():
            with self.subTest(layer=name):
                self.assertEqual(self.layer_macros[name], "LAYOUT")
                self.assertEqual(len(arguments), 62)
        self.assertEqual(self.chordal_macro, "LAYOUT")
        self.assertEqual(len(self.chordal), 62)

    def test_tab_fn_taps_tab_and_holds_function_layer(self) -> None:
        self.assertEqual(self.layers["_QWERTY"][12], "LT(_FN, KC_TAB)")

    def test_thumb_fn_is_momentary(self) -> None:
        self.assertEqual(self.layers["_QWERTY"][52], "MO(_FN)")

    def test_fn_entry_keys_are_transparent_on_function_layer(self) -> None:
        function = self.layers["_FN"]
        self.assertEqual(function[12], "KC_TRNS")
        self.assertEqual(function[52], "KC_TRNS")

    def test_tab_fn_is_neutral_for_same_hand_chords(self) -> None:
        self.assertEqual(self.chordal[12], "'*'")


if __name__ == "__main__":
    unittest.main()
