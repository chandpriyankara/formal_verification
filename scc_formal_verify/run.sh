#!/bin/bash

set -e

echo "Building and testing Kosaraju SCC implementation..."

# Build and test C++
make clean
make test

# Install TLA+ if not found
if ! command -v java >/dev/null 2>&1; then
    echo "⚠ TLA+ verification skipped (Java not found)"
elif [ ! -f "toolbox/tla2tools.jar" ]; then
    echo "Installing TLA+ Toolbox..."
    if [ ! -f "TLAToolbox-1.8.0-linux.gtk.x86_64.zip" ]; then
        wget -q https://github.com/tlaplus/tlaplus/releases/download/v1.8.0/TLAToolbox-1.8.0-linux.gtk.x86_64.zip
    fi
    if [ ! -d "toolbox" ]; then
        unzip -q TLAToolbox-1.8.0-linux.gtk.x86_64.zip
    fi
fi

# Run TLA+ verification
if [ -f "toolbox/tla2tools.jar" ]; then
    echo "Running TLA+ verification..."
    java -jar toolbox/tla2tools.jar Kosaraju
    echo "✓ TLA+ verification completed"
else
    echo "⚠ TLA+ verification skipped (TLA+ not installed)"
fi

echo "Done!"