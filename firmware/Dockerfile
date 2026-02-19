FROM qmkfm/qmk_cli

WORKDIR /build

# Clone splitkb userspace (halcyon branch) and set up QMK
RUN git clone --depth 1 -b halcyon https://github.com/splitkb/qmk_userspace.git . \
    && qmk config user.overlay_dir="/build" \
    && qmk setup -y

# Copy custom keymap
COPY keyboards/splitkb/halcyon/elora/keymaps/denis/ \
     keyboards/splitkb/halcyon/elora/keymaps/denis/

# Module flag passed at runtime via build.sh:
#   -e HLC_TFT_DISPLAY=1      (left half — TFT display)
#   -e HLC_CIRQUE_TRACKPAD=1   (right half — Cirque trackpad)
CMD ["qmk", "compile", "-kb", "splitkb/halcyon/elora/rev2", "-km", "denis"]
