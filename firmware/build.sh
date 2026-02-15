#!/bin/bash
set -e

cd "$(dirname "$0")"
mkdir -p output

docker build -t elora-firmware .
docker run --rm -v "$(pwd)/output:/output" elora-firmware \
    sh -c 'qmk compile -kb splitkb/halcyon/elora/rev2 -km denis -e HLC_NONE=1 && cp $(find / -name "*.uf2" -path "*/.build/*" 2>/dev/null | head -1) /output/'

echo ""
echo "Done! Firmware:"
ls -lh output/*.uf2
