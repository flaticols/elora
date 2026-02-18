#!/bin/bash
set -e

cd "$(dirname "$0")"
mkdir -p output

docker build -t elora-firmware .

echo "=== Building LEFT half (TFT display) ==="
docker run --rm -v "$(pwd)/output:/output" elora-firmware \
    sh -c 'qmk compile -kb splitkb/halcyon/elora/rev2 -km denis -e HLC_TFT_DISPLAY=1 && cp $(find / -name "*.uf2" -path "*/.build/*" 2>/dev/null | head -1) /output/elora_left_display.uf2'

echo ""
echo "=== Building RIGHT half (Cirque trackpad) ==="
docker run --rm -v "$(pwd)/output:/output" elora-firmware \
    sh -c 'qmk compile -kb splitkb/halcyon/elora/rev2 -km denis -e HLC_CIRQUE_TRACKPAD=1 && cp $(find / -name "*.uf2" -path "*/.build/*" 2>/dev/null | head -1) /output/elora_right_trackpad.uf2'

echo ""
echo "Done! Firmware files:"
ls -lh output/elora_left_display.uf2 output/elora_right_trackpad.uf2
