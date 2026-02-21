# Elora Rev2 — Denis's build rules

LEADER_ENABLE = yes
MOUSEKEY_ENABLE = yes
POINTING_DEVICE_AUTO_MOUSE_ENABLE = yes
RGB_MATRIX_ENABLE = yes
CAPS_WORD_ENABLE = yes

# Halcyon module support (defines LAYOUT_elora_hlc)
# Build left half:  -e HLC_TFT_DISPLAY=1     (TFT display module)
# Build right half: -e HLC_CIRQUE_TRACKPAD=1  (Cirque trackpad module)
USER_NAME := halcyon_modules
