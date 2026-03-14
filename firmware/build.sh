#!/bin/bash
set -e

cd "$(dirname "$0")"
mkdir -p output

docker build -t elora-firmware .

echo "=== Building both halves ==="
docker run --rm -v "$(pwd)/output:/output" elora-firmware \
    sh -c '
        echo "--- LEFT half (TFT display) ---" &&
        qmk compile -kb splitkb/halcyon/elora/rev2 -km denis -e HLC_TFT_DISPLAY=1 &&
        echo "--- Searching for .uf2 output ---" &&
        find / -name "*.uf2" -not -path "/proc/*" -not -path "/sys/*" 2>/dev/null &&
        UF2=$(find / -name "*.uf2" -not -path "/proc/*" -not -path "/sys/*" -not -path "/output/*" 2>/dev/null | head -1) &&
        echo "Found: $UF2" &&
        cp "$UF2" /output/elora_left_display.uf2 &&
        rm "$UF2" &&

        echo "--- RIGHT half ---" &&
        qmk compile -kb splitkb/halcyon/elora/rev2 -km denis &&
        UF2=$(find / -name "*.uf2" -not -path "/proc/*" -not -path "/sys/*" -not -path "/output/*" 2>/dev/null | head -1) &&
        echo "Found: $UF2" &&
        cp "$UF2" /output/elora_right.uf2
    '

echo ""
echo "Done! Firmware files:"
ls -lh output/elora_left_display.uf2 output/elora_right.uf2
