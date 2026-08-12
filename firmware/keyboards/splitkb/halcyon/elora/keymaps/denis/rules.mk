# Elora Rev2 — Denis's build rules

RGB_MATRIX_ENABLE = yes
CAPS_WORD_ENABLE = yes
EXTRAKEY_ENABLE = yes   # consumer endpoint — required for the Globe key
ENCODER_MAP_ENABLE = yes

# Globe key (consumer 0x29D) used together with Ctrl + key for macOS window
# tiling — share the USB endpoint so consumer + keyboard reports coexist.
KEYBOARD_SHARED_EP = yes

# Halcyon module selection is supplied per half at compile time:
#   left:  -e HLC_TFT_DISPLAY=1
#   right: -e HLC_NONE=1
USER_NAME := halcyon_modules
