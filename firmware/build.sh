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
        echo "--- .build contents after left half ---" &&
        ls -la .build/*.uf2 &&
        cp .build/*.uf2 /output/elora_left_display.uf2 &&
        rm .build/*.uf2 &&

        echo "--- RIGHT half (Cirque trackpad) ---" &&
        qmk compile -kb splitkb/halcyon/elora/rev2 -km denis -e HLC_CIRQUE_TRACKPAD=1 &&
        echo "--- .build contents after right half ---" &&
        ls -la .build/*.uf2 &&
        cp .build/*.uf2 /output/elora_right_trackpad.uf2
    '

echo ""
echo "Done! Firmware files:"
ls -lh output/elora_left_display.uf2 output/elora_right_trackpad.uf2
